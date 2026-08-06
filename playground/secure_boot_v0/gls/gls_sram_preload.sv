// gls_sram_preload.sv
//
// Backdoor content loader for the post-PnR `tlul_sram_if_macro` gate netlist
// (pd/macros/tlul_sram_if_macro/tlul_sram_if_macro.nl.v) used inside top_pd.
//
// Why this exists: top_pd.sv's memories are the hardened SRAM hard macro
// (gf180mcu_ocd_ip_sram__sram256x8m8wm1, wrapped by prim_ram_1p_macro_OCD),
// which has NO $readmemh / MemInitFile support -- prim_ram_1p_macro_OCD.sv
// says so explicitly ("MemInitFile ... not supported by a hard macro;
// ignored") -- and the SRAM's own sim model
// (gf180mcu_ocd_ip_sram__sram256x8m8wm1_simpatch.v) always resets its content
// to zero. Real silicon would need an actual boot-loader path (debug port /
// boot ROM / flash) to shadow code into these SRAMs before releasing the
// core; that path doesn't exist in this project yet. This module is `bind`ed
// into EVERY instance of tlul_sram_if_macro inside top_pd (u_imem/u_esram/
// u_dmem) and pokes the four byte-lane SRAM `mem` arrays directly at time 0
// -- a stand-in for "assume the bring-up loader already ran" -- so the same
// test_sw boot image the RTL/macro sims use can be checked against the
// actual taped-out gate netlist.
//
// Note: the Verilog simulator here rejects the LRM `bind module :
// instance_list ...` targeted-instance form ("Unsupported: Bind with
// instance list"), so this binds unconditionally into every instance and
// self-selects which plusarg (if any) to load by matching its own
// instantiation name via %m -- the standard workaround for per-instance
// bind behavior under such tools.
//
// The four byte-lane SRAM macro instances inside tlul_sram_if_macro.nl.v are
// *flat* escaped Verilog identifiers (Yosys collapsed the RTL hierarchy
// u_mem/gen_byte[N]/u_macro into one flat instance name per lane), so they
// are referenced here as escaped identifiers, exactly as the netlist itself
// spells them.
module gls_sram_preload;
  logic [31:0] word_mem [0:255];
  string       inst_path;
  string       hex_path;
  int          i;

  // %m gives *this* bind-inserted instance's own path, e.g.
  // "...dut.u_imem.u_gls_preload" -- the parent instance name (u_imem/u_dmem)
  // is a substring in the middle, not a suffix, so a plain substring search
  // is used rather than a suffix compare.
  function automatic bit contains(string s, string pat);
    int n, m, k;
    bit found;
    n = s.len();
    m = pat.len();
    found = 0;
    if (m != 0 && m <= n) begin
      for (k = 0; k <= n - m; k++) begin
        if (!found && s.substr(k, k + m - 1) == pat) found = 1;
      end
    end
    contains = found;
  endfunction

  initial begin
    inst_path = $sformatf("%m");
    hex_path  = "";

    if (contains(inst_path, "u_imem")) void'($value$plusargs("gls_imem_hex=%s", hex_path));
    else if (contains(inst_path, "u_dmem")) void'($value$plusargs("gls_dmem_hex=%s", hex_path));

    if (hex_path != "") begin
      $readmemh(hex_path, word_mem);
      for (i = 0; i < 256; i++) begin
        \u_mem.gen_byte[0].u_macro .mem[i] = word_mem[i][7:0];
        \u_mem.gen_byte[1].u_macro .mem[i] = word_mem[i][15:8];
        \u_mem.gen_byte[2].u_macro .mem[i] = word_mem[i][23:16];
        \u_mem.gen_byte[3].u_macro .mem[i] = word_mem[i][31:24];
      end
      $display("[GLS_PRELOAD][%s] loaded 256 words from %s", inst_path, hex_path);
    end else begin
      $display("[GLS_PRELOAD][%s] no image given -- SRAM stays at reset (zero) content", inst_path);
    end
  end
endmodule

bind tlul_sram_if_macro gls_sram_preload u_gls_preload();
