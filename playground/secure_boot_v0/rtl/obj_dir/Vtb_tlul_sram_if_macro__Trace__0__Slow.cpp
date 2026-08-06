// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtb_tlul_sram_if_macro__Syms.h"


VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_mubi_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_ram_1p_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_secded_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__tlul_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__top_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("prim_mubi_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_mubi_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("prim_ram_1p_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_ram_1p_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("prim_secded_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_secded_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("tb_tlul_sram_if_macro", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_h2d", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_d2h", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+81,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+82,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+83,0,"d_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"a_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBus(c+140,0,"errors",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+17,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+18,0,"rerr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+277,0,"SramAw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+278,0,"BASE_ADDR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+279,0,"READ_ONLY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+81,0,"rsp_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+82,0,"data_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+83,0,"d_error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"a_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBus(c+280,0,"en_ifetch_i",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+281,0,"MacroAw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+61,0,"req",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+282,0,"gnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+113,0,"rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+19,0,"req_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+35,0,"addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+36,0,"wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+141,0,"rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+283,0,"rerror",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+37,0,"macro_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+34,0,"write_eff",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+114,0,"rvalid_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+142,0,"unused",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_adapt", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+284,0,"SramAw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"SramDw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+286,0,"Outstanding",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+287,0,"SramBusBankAW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+288,0,"ByteAccess",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"ErrOnWrite",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"ErrOnRead",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"CmdIntgCheck",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"EnableRspIntgGen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"EnableDataIntgGen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"EnableDataIntgPt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"SecFifoPtr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"EnableReadback",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"DataXorAddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+286,0,"WidthMult",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+289,0,"IntgWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"DataOutW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+81,0,"rsp_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+82,0,"data_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+83,0,"d_error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"a_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBus(c+280,0,"en_ifetch_i",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+61,0,"req_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+19,0,"req_type_o",2, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+282,0,"gnt_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"we_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+35,0,"addr_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+36,0,"wdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"wmask_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+115,0,"intg_error_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+20,0,"user_rsvd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+141,0,"rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+113,0,"rvalid_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+283,0,"rerror_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+290,0,"compound_txn_in_progress_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+280,0,"readback_en_i",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+290,0,"readback_error_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"wr_collision_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"write_pending_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+291,0,"SramByte",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+292,0,"DataBitWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+286,0,"WoffsetWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+38,0,"error_det",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"error_internal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"wr_attr_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"instr_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"wr_vld_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"rd_vld_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"rsp_fifo_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"sramreqfifo_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"reqfifo_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"intg_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+143,0,"tlul_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"readback_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"sram_byte_readback_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"readback_error_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+115,0,"intg_error_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_i_int", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_o_int", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+73,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+75,0,"d_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"a_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_out", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+73,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+75,0,"d_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"a_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBit(c+21,0,"unused_tl_i_int",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+293,0,"SramReqWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+293,0,"SramReqFifoWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+284,0,"ReqFifoWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+294,0,"RspFifoWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+62,0,"reqfifo_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+116,0,"reqfifo_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+117,0,"reqfifo_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+63,0,"reqfifo_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("reqfifo_wdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+22,0,"is_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+7,0,"size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("reqfifo_rdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+127,0,"is_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+128,0,"error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+129,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+130,0,"size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+131,0,"source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->declBit(c+64,0,"sramreqfifo_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+118,0,"sramreqfifo_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+119,0,"sramreqfifo_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("sram_req_wdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+10,0,"mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+295,0,"woffset",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->popPrefix();
    tracep->pushPrefix("sram_req_rdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+132,0,"mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+133,0,"woffset",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->popPrefix();
    tracep->declBus(c+23,0,"sram_addr_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+296,0,"sram_addr_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+24,0,"sramreqfifo_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+134,0,"sramreqfifo_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+119,0,"rspfifo_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+120,0,"rspfifo_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+121,0,"rspfifo_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+65,0,"rspfifo_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("rspfifo_wdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+85,0,"data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+297,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBit(c+290,0,"error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("rspfifo_rdata", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+86,0,"data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+87,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBit(c+88,0,"error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBit(c+62,0,"a_ack",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+63,0,"d_ack",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"sram_ack",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+77,0,"d_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+144,0,"vld_rd_rsp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+135,0,"error_blanking_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+278,0,"unused_instr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"unused_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+299,0,"error_instr_integ",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+299,0,"error_data_integ",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+299,0,"error_blanking_integ",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+78,0,"d_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+79,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBit(c+145,0,"missed_err_gnt_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+122,0,"missed_err_gnt_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+290,0,"woffset",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+285,0,"DataWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("wmask_combined", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+48,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("wdata_combined", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+36,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("wmask_int", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+48,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("wdata_int", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+36,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("wmask_intg", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+25,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->pushPrefix("wdata_intg", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+26,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->pushPrefix("rdata_reshaped", VerilatedTracePrefixType::ARRAY_PACKED);
    tracep->declBus(c+141,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->declBus(c+85,0,"rdata_tlword",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+290,0,"unused_rerror",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_no_data_xor_addr_fifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+27,0,"unused_sram_addresses",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("gen_no_readback_check", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+290,0,"unused_sram_byte_readback_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("gen_rmask", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+136,0,"rmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("gen_write_output[0]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("gen_ft_output", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+28,0,"unused_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_err", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBit(c+143,0,"err_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+300,0,"IW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+292,0,"SZW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"DW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+291,0,"MW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+292,0,"SubAW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+29,0,"opcode_allowed",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+146,0,"a_config_allowed",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+30,0,"op_full",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+31,0,"op_partial",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"op_get",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"instr_wr_err",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"instr_type_err",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+41,0,"addr_sz_chk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"mask_chk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"fulldata_chk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+301,0,"MaskOne",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1, 3,0);
    tracep->declBus(c+33,0,"mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_reqfifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+277,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+279,0,"Pass",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+302,0,"Depth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+288,0,"OutputZeroIfEmpty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+288,0,"NeverClears",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"Secure",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+286,0,"DepthW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"clr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+62,0,"wvalid_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+116,0,"wready_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+147,0,"wdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+117,0,"rvalid_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+63,0,"rready_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+137,0,"rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+117,0,"full_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+117,0,"depth_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBit(c+290,0,"err_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_singleton_fifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+148,0,"full_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+117,0,"full_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+105,0,"storage",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+105,0,"rdata_int",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_rsp_gen", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+279,0,"EnableRspIntgGen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"EnableDataIntgGen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"UserInIsZero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+288,0,"RspIntgInIsZero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->pushPrefix("tl_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+73,0,"rsp_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+75,0,"d_error",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"a_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+81,0,"rsp_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+82,0,"data_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+83,0,"d_error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"a_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBus(c+297,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+79,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBit(c+80,0,"unused_tl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_rspfifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+303,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+288,0,"Pass",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+302,0,"Depth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+288,0,"OutputZeroIfEmpty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+288,0,"NeverClears",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"Secure",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+286,0,"DepthW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"clr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+119,0,"wvalid_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+120,0,"wready_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+89,0,"wdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 39,0);
    tracep->declBit(c+121,0,"rvalid_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+65,0,"rready_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+91,0,"rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 39,0);
    tracep->declBit(c+123,0,"full_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+123,0,"depth_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBit(c+290,0,"err_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_singleton_fifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+149,0,"full_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"full_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+106,0,"storage",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 39,0);
    tracep->declQuad(c+150,0,"rdata_int",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 39,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_sram_byte", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+279,0,"EnableIntg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+286,0,"Outstanding",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+279,0,"EnableReadback",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("tl_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+73,0,"rsp_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"data_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+75,0,"d_error",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"a_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_sram_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+4,0,"a_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"a_opcode",1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+6,0,"a_param",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+7,0,"a_size",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+8,0,"a_source",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+9,0,"a_address",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"a_mask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+11,0,"a_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+12,0,"rsvd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+13,0,"instr_type",2, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+14,0,"cmd_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+15,0,"data_intg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+16,0,"d_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("tl_sram_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+125,0,"d_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+126,0,"d_opcode",3, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+68,0,"d_param",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+69,0,"d_size",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+70,0,"d_source",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"d_sink",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+72,0,"d_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+73,0,"rsp_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+74,0,"data_intg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+75,0,"d_error",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"a_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBit(c+38,0,"error_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"error_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"alert_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"compound_txn_in_progress_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+280,0,"readback_en_i",2, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+290,0,"wr_collision_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"write_pending_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+300,0,"StateWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+290,0,"unused_write_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"unused_wr_collision",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_no_integ_handling", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+280,0,"unused_readback_en",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_sramreqfifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+304,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+279,0,"Pass",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+302,0,"Depth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+288,0,"OutputZeroIfEmpty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+288,0,"NeverClears",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+279,0,"Secure",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBus(c+286,0,"DepthW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"clr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+64,0,"wvalid_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+118,0,"wready_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"wdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+124,0,"rvalid_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+119,0,"rready_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+134,0,"rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+124,0,"full_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+124,0,"depth_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBit(c+290,0,"err_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_singleton_fifo", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+152,0,"full_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+124,0,"full_q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+108,0,"storage",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+108,0,"rdata_int",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_tlul_data_integ_enc_data", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+298,0,"data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+305,0,"data_intg_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->pushPrefix("u_data_gen", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+298,0,"data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+305,0,"data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_tlul_data_integ_enc_instr", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+278,0,"data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+307,0,"data_intg_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->pushPrefix("u_data_gen", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+278,0,"data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+307,0,"data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_mem", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+285,0,"Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+309,0,"Depth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+300,0,"DataBitsPerMask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+310,0,"MemInitFile",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+300,0,"Aw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+138,0,"clk_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"rst_ni",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"req_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+37,0,"addr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+36,0,"wdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"wmask_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+141,0,"rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("cfg_i", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->pushPrefix("ram_cfg", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"test",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"cfg_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+311,0,"cfg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->pushPrefix("rf_cfg", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"test",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"cfg_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+311,0,"cfg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("cfg_rsp_o", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->declBit(c+139,0,"unused",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"cen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"gwen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gen_byte[0]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_macro", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"CEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"GWEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+49,0,"WEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+37,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+44,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+153,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+153,0,"qo_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+93,0,"cen_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+94,0,"write_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+95,0,"read_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+154,0,"ntf_Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+155,0,"ntf_Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"ntf_Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"ntf_tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+158,0,"ntf_tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+159,0,"ntf_tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+160,0,"ntf_tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+161,0,"ntf_twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"ntf_tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+163,0,"ntf_tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+164,0,"ntf_tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+165,0,"ntf_twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+166,0,"ntf_twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+167,0,"no_st_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+168,0,"no_hd_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+169,0,"no_ck_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+170,0,"clk_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+171,0,"write_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"read_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+173,0,"cen_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+174,0,"cen_fell",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+175,0,"cen_not_rst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+50,0,"we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+176,0,"cd2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+51,0,"cd4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+177,0,"cd5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"cdx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+178,0,"marked_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+0,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+179,0,"mem_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+180,0,"mem_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+181,0,"mem_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+182,0,"mem_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+183,0,"cen_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declDouble(c+312,0,"Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+320,0,"ta",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+322,0,"Tdly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("gen_byte[1]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_macro", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"CEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"GWEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+52,0,"WEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+37,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+45,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+184,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+184,0,"qo_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+96,0,"cen_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+97,0,"write_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+98,0,"read_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+185,0,"ntf_Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+186,0,"ntf_Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+187,0,"ntf_Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"ntf_tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"ntf_tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"ntf_tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"ntf_tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+192,0,"ntf_twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+193,0,"ntf_tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+194,0,"ntf_tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+195,0,"ntf_tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+196,0,"ntf_twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+197,0,"ntf_twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+198,0,"no_st_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+199,0,"no_hd_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+200,0,"no_ck_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+201,0,"clk_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+202,0,"write_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+203,0,"read_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+204,0,"cen_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+205,0,"cen_fell",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+206,0,"cen_not_rst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+53,0,"we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+207,0,"cd2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+54,0,"cd4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+208,0,"cd5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+110,0,"cdx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+209,0,"marked_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+1,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+210,0,"mem_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"mem_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"mem_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"mem_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+214,0,"cen_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declDouble(c+312,0,"Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+320,0,"ta",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+322,0,"Tdly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("gen_byte[2]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_macro", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"CEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"GWEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+55,0,"WEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+37,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+46,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+215,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+215,0,"qo_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+99,0,"cen_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+100,0,"write_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+101,0,"read_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+216,0,"ntf_Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+217,0,"ntf_Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+218,0,"ntf_Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+219,0,"ntf_tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+220,0,"ntf_tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+221,0,"ntf_tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+222,0,"ntf_tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+223,0,"ntf_twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+224,0,"ntf_tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+225,0,"ntf_tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+226,0,"ntf_tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+227,0,"ntf_twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+228,0,"ntf_twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+229,0,"no_st_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"no_hd_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+231,0,"no_ck_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"clk_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+233,0,"write_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+234,0,"read_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+235,0,"cen_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+236,0,"cen_fell",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+237,0,"cen_not_rst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+56,0,"we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+238,0,"cd2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+57,0,"cd4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+239,0,"cd5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+111,0,"cdx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+240,0,"marked_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+2,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+241,0,"mem_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+242,0,"mem_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+243,0,"mem_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+244,0,"mem_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+245,0,"cen_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declDouble(c+312,0,"Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+320,0,"ta",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+322,0,"Tdly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("gen_byte[3]", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("u_macro", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+138,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"CEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"GWEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+58,0,"WEN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+37,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+47,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+246,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+246,0,"qo_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+102,0,"cen_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+103,0,"write_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+104,0,"read_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+247,0,"ntf_Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+248,0,"ntf_Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+249,0,"ntf_Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+250,0,"ntf_tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+251,0,"ntf_tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+252,0,"ntf_tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+253,0,"ntf_tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+254,0,"ntf_twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+255,0,"ntf_tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+256,0,"ntf_tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+257,0,"ntf_tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+258,0,"ntf_twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+259,0,"ntf_twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+260,0,"no_st_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+261,0,"no_hd_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+262,0,"no_ck_viol",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+263,0,"clk_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+264,0,"write_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+265,0,"read_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+266,0,"cen_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+267,0,"cen_fell",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+268,0,"cen_not_rst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+59,0,"we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+269,0,"cd2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+60,0,"cd4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+270,0,"cd5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+112,0,"cdx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+271,0,"marked_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+3,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+272,0,"mem_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+273,0,"mem_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+274,0,"mem_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+275,0,"mem_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+276,0,"cen_flag_dly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declDouble(c+312,0,"Tcyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+314,0,"Tckl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tcs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tas",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tds",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"tws",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+316,0,"twis",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tah",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"tdh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+318,0,"twih",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+320,0,"ta",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->declDouble(c+322,0,"Tdly",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::DOUBLE, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("tlul_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__tlul_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("top_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__top_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_secded_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_secded_pkg__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->declBus(c+324,0,"Secded2216ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+325,0,"Secded2216ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 21,0);
    tracep->declBus(c+324,0,"Secded2822ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+326,0,"Secded2822ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 27,0);
    tracep->declBus(c+297,0,"Secded3932ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+327,0,"Secded3932ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->declBus(c+297,0,"Secded6457ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+329,0,"Secded6457ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+310,0,"Secded7264ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+331,0,"Secded7264ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 71,0);
    tracep->declBus(c+324,0,"SecdedHamming2216ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+325,0,"SecdedHamming2216ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 21,0);
    tracep->declBus(c+297,0,"SecdedHamming3932ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+327,0,"SecdedHamming3932ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->declBus(c+310,0,"SecdedHamming7264ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+331,0,"SecdedHamming7264ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 71,0);
    tracep->declBus(c+310,0,"SecdedHamming7668ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+334,0,"SecdedHamming7668ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 75,0);
    tracep->declBus(c+337,0,"SecdedInv2216ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+338,0,"SecdedInv2216ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 21,0);
    tracep->declBus(c+337,0,"SecdedInv2822ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+339,0,"SecdedInv2822ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 27,0);
    tracep->declBus(c+299,0,"SecdedInv3932ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+307,0,"SecdedInv3932ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->declBus(c+299,0,"SecdedInv6457ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+340,0,"SecdedInv6457ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+342,0,"SecdedInv7264ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+343,0,"SecdedInv7264ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 71,0);
    tracep->declBus(c+337,0,"SecdedInvHamming2216ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+338,0,"SecdedInvHamming2216ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 21,0);
    tracep->declBus(c+299,0,"SecdedInvHamming3932ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+307,0,"SecdedInvHamming3932ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 38,0);
    tracep->declBus(c+342,0,"SecdedInvHamming7264ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+343,0,"SecdedInvHamming7264ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 71,0);
    tracep->declBus(c+342,0,"SecdedInvHamming7668ZeroEcc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+346,0,"SecdedInvHamming7668ZeroWord",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 75,0);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__top_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__top_pkg__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->declBus(c+285,0,"TL_AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"TL_DW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+300,0,"TL_AIW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+286,0,"TL_DIW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+349,0,"TL_AUW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+350,0,"TL_DUW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+291,0,"TL_DBW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+292,0,"TL_SZW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+351,0,"AlertSkewCycles",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+286,0,"SecVolatileRawUnlockEn",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+352,0,"CtnSramSize",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+353,0,"CtnSramDepth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+354,0,"CtnSramAw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_ram_1p_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_ram_1p_pkg__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("RAM_1P_CFG_DEFAULT", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->pushPrefix("ram_cfg", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"test",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"cfg_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+311,0,"cfg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->pushPrefix("rf_cfg", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"test",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+290,0,"cfg_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+311,0,"cfg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_mubi_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__prim_mubi_pkg__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->declBus(c+291,0,"MuBi4Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+300,0,"MuBi8Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+287,0,"MuBi12Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+284,0,"MuBi16Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+355,0,"MuBi20Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+356,0,"MuBi24Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+349,0,"MuBi28Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"MuBi32Width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__tlul_pkg__0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__tlul_pkg__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->declBus(c+357,0,"ArbiterImpl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 23,0);
    tracep->declBus(c+358,0,"H2DCmdMaxWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+289,0,"H2DCmdIntgWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+359,0,"H2DCmdFullWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+358,0,"D2HRspMaxWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+289,0,"D2HRspIntgWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+359,0,"D2HRspFullWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+285,0,"DataMaxWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+289,0,"DataIntgWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+360,0,"DataFullWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+361,0,"RsvdWidth",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+278,0,"DataWhenInstrError",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"DataWhenError",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("TL_A_USER_DEFAULT", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+362,0,"rsvd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+363,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+364,0,"cmd_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+364,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBus(c+298,0,"BlankedAData",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("TL_H2D_DEFAULT", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"a_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+365,0,"a_opcode",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+366,0,"a_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+283,0,"a_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+310,0,"a_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+278,0,"a_address",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+311,0,"a_mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+298,0,"a_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("a_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+362,0,"rsvd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+363,0,"instr_type",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+364,0,"cmd_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+364,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+282,0,"d_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("TL_D_USER_DEFAULT", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+364,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+364,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->pushPrefix("TL_D2H_DEFAULT", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBit(c+290,0,"d_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+367,0,"d_opcode",3, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+366,0,"d_param",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+283,0,"d_size",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+310,0,"d_source",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+295,0,"d_sink",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 0,0);
    tracep->declBus(c+278,0,"d_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("d_user", VerilatedTracePrefixType::STRUCT_PACKED);
    tracep->declBus(c+364,0,"rsp_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+364,0,"data_intg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->popPrefix();
    tracep->declBit(c+290,0,"d_error",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+282,0,"a_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_init_top(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_init_top\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_tlul_sram_if_macro___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_tlul_sram_if_macro___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtb_tlul_sram_if_macro___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_register(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_register\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtb_tlul_sram_if_macro___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtb_tlul_sram_if_macro___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtb_tlul_sram_if_macro___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtb_tlul_sram_if_macro___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_const_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_const_0\n"); );
    // Body
    Vtb_tlul_sram_if_macro___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_tlul_sram_if_macro___024root*>(voidSelf);
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_tlul_sram_if_macro___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_const_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_const_0_sub_0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<3>/*95:0*/ __Vtemp_1;
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_4;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+277,(0x00000010U),32);
    bufp->fullIData(oldp+278,(0U),32);
    bufp->fullBit(oldp+279,(0U));
    bufp->fullCData(oldp+280,(9U),4);
    bufp->fullIData(oldp+281,(8U),32);
    bufp->fullBit(oldp+282,(1U));
    bufp->fullCData(oldp+283,(0U),2);
    bufp->fullIData(oldp+284,(0x00000010U),32);
    bufp->fullIData(oldp+285,(0x00000020U),32);
    bufp->fullIData(oldp+286,(1U),32);
    bufp->fullIData(oldp+287,(0x0000000cU),32);
    bufp->fullBit(oldp+288,(1U));
    bufp->fullIData(oldp+289,(7U),32);
    bufp->fullBit(oldp+290,(0U));
    bufp->fullIData(oldp+291,(4U),32);
    bufp->fullIData(oldp+292,(2U),32);
    bufp->fullIData(oldp+293,(5U),32);
    bufp->fullIData(oldp+294,(0x00000028U),32);
    bufp->fullBit(oldp+295,(0U));
    bufp->fullSData(oldp+296,(0U),12);
    bufp->fullCData(oldp+297,(0U),7);
    bufp->fullIData(oldp+298,(0xffffffffU),32);
    bufp->fullCData(oldp+299,(0x2aU),7);
    bufp->fullIData(oldp+300,(8U),32);
    bufp->fullCData(oldp+301,(1U),4);
    bufp->fullIData(oldp+302,(1U),32);
    bufp->fullIData(oldp+303,(0x00000028U),32);
    bufp->fullIData(oldp+304,(5U),32);
    bufp->fullQData(oldp+305,(0x0000002affffffffULL),39);
    bufp->fullQData(oldp+307,(0x0000002a00000000ULL),39);
    bufp->fullIData(oldp+309,(0x00000100U),32);
    bufp->fullCData(oldp+310,(0U),8);
    bufp->fullCData(oldp+311,(0U),4);
    bufp->fullDouble(oldp+312,(5.56000000000000000e+04));
    bufp->fullDouble(oldp+314,(2.50000000000000000e+04));
    bufp->fullDouble(oldp+316,(5.00000000000000000e+03));
    bufp->fullDouble(oldp+318,(1.00000000000000000e+04));
    bufp->fullDouble(oldp+320,(4.50000000000000000e+04));
    bufp->fullDouble(oldp+322,(100.0));
    bufp->fullCData(oldp+324,(0U),6);
    bufp->fullIData(oldp+325,(0U),22);
    bufp->fullIData(oldp+326,(0U),28);
    bufp->fullQData(oldp+327,(0ULL),39);
    bufp->fullQData(oldp+329,(0ULL),64);
    __Vtemp_1[0U] = 0U;
    __Vtemp_1[1U] = 0U;
    __Vtemp_1[2U] = 0U;
    bufp->fullWData(oldp+331,(__Vtemp_1),72);
    __Vtemp_2[0U] = 0U;
    __Vtemp_2[1U] = 0U;
    __Vtemp_2[2U] = 0U;
    bufp->fullWData(oldp+334,(__Vtemp_2),76);
    bufp->fullCData(oldp+337,(0x2aU),6);
    bufp->fullIData(oldp+338,(0x002a0000U),22);
    bufp->fullIData(oldp+339,(0x0a800000U),28);
    bufp->fullQData(oldp+340,(0x5400000000000000ULL),64);
    bufp->fullCData(oldp+342,(0xaaU),8);
    __Vtemp_3[0U] = 0U;
    __Vtemp_3[1U] = 0U;
    __Vtemp_3[2U] = 0x000000aaU;
    bufp->fullWData(oldp+343,(__Vtemp_3),72);
    __Vtemp_4[0U] = 0U;
    __Vtemp_4[1U] = 0U;
    __Vtemp_4[2U] = 0x00000aa0U;
    bufp->fullWData(oldp+346,(__Vtemp_4),76);
    bufp->fullIData(oldp+349,(0x0000001cU),32);
    bufp->fullIData(oldp+350,(0x0000000eU),32);
    bufp->fullIData(oldp+351,(3U),32);
    bufp->fullIData(oldp+352,(0x00100000U),32);
    bufp->fullIData(oldp+353,(0x00040000U),32);
    bufp->fullIData(oldp+354,(0x00000012U),32);
    bufp->fullIData(oldp+355,(0x00000014U),32);
    bufp->fullIData(oldp+356,(0x00000018U),32);
    bufp->fullIData(oldp+357,(0x00505043U),24);
    bufp->fullIData(oldp+358,(0x00000039U),32);
    bufp->fullIData(oldp+359,(0x00000040U),32);
    bufp->fullIData(oldp+360,(0x00000027U),32);
    bufp->fullIData(oldp+361,(0x0000000aU),32);
    bufp->fullSData(oldp+362,(0U),10);
    bufp->fullCData(oldp+363,(9U),4);
    bufp->fullCData(oldp+364,(0x7fU),7);
    bufp->fullCData(oldp+365,(0U),3);
    bufp->fullCData(oldp+366,(0U),3);
    bufp->fullCData(oldp+367,(0U),3);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_full_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_full_0\n"); );
    // Body
    Vtb_tlul_sram_if_macro___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_tlul_sram_if_macro___024root*>(voidSelf);
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtb_tlul_sram_if_macro___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_full_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_full_0_sub_0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+0,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i),32);
    bufp->fullIData(oldp+1,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i),32);
    bufp->fullIData(oldp+2,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i),32);
    bufp->fullIData(oldp+3,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i),32);
    bufp->fullBit(oldp+4,((1U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                 >> 0x00000011U))));
    bufp->fullCData(oldp+5,((7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                   >> 0x0000000eU))),3);
    bufp->fullCData(oldp+6,((7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                   >> 0x0000000bU))),3);
    bufp->fullCData(oldp+7,((3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                   >> 9U))),2);
    bufp->fullCData(oldp+8,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                            >> 1U))),8);
    bufp->fullIData(oldp+9,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                              << 0x0000001fU) | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                 >> 1U))),32);
    bufp->fullCData(oldp+10,((0x0000000fU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                              << 3U) 
                                             | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                >> 0x0000001dU)))),4);
    bufp->fullIData(oldp+11,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                               << 3U) | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                         >> 0x0000001dU))),32);
    bufp->fullSData(oldp+12,((0x000003ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                             >> 0x00000013U))),10);
    bufp->fullCData(oldp+13,((0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                             >> 0x0000000fU))),4);
    bufp->fullCData(oldp+14,((0x0000007fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                             >> 8U))),7);
    bufp->fullCData(oldp+15,((0x0000007fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                             >> 1U))),7);
    bufp->fullBit(oldp+16,((1U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U])));
    bufp->fullIData(oldp+17,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rd),32);
    bufp->fullBit(oldp+18,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rerr));
    bufp->fullCData(oldp+19,((0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                             >> 0x0000000fU))),4);
    bufp->fullSData(oldp+20,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                               ? (0x000003ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                 >> 0x00000013U))
                               : 0U)),10);
    bufp->fullBit(oldp+21,((1U & VL_REDXOR_32((((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                 ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U]) 
                                                ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U]) 
                                               ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])))));
    bufp->fullBit(oldp+22,((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                         >> 0x0000000eU)))));
    bufp->fullSData(oldp+23,((0x00000fffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                             >> 3U))),12);
    bufp->fullCData(oldp+24,((0x0000001eU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                              << 4U) 
                                             | (0x0000000eU 
                                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                   >> 0x0000001cU))))),5);
    bufp->fullCData(oldp+25,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                               ? 0x7fU : 0U)),7);
    bufp->fullCData(oldp+26,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                               ? (0x0000007fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                 >> 1U))
                               : 0U)),7);
    bufp->fullBit(oldp+27,((1U & VL_REDXOR_32((0x00000fffU 
                                               & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                  >> 3U))))));
    bufp->fullBit(oldp+28,((IData)(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                     >> 0x00000011U) 
                                    & (0U != (0x0000007fU 
                                              & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                 >> 1U)))))));
    bufp->fullBit(oldp+29,(((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                          >> 0x0000000eU))) 
                            | ((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                             >> 0x0000000eU))) 
                               | (4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 0x0000000eU)))))));
    bufp->fullBit(oldp+30,((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                         >> 0x0000000eU)))));
    bufp->fullBit(oldp+31,((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                         >> 0x0000000eU)))));
    bufp->fullBit(oldp+32,((1U & (~ ((6U == (0x0000000fU 
                                             & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 0x0000000fU))) 
                                     | (9U == (0x0000000fU 
                                               & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                  >> 0x0000000fU))))))));
    bufp->fullCData(oldp+33,((0x0000000fU & ((IData)(1U) 
                                             << (3U 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                    >> 1U))))),4);
    bufp->fullBit(oldp+34,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we));
    bufp->fullSData(oldp+35,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr),16);
    bufp->fullIData(oldp+36,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata),32);
    bufp->fullCData(oldp+37,((0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))),8);
    bufp->fullBit(oldp+38,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det));
    bufp->fullBit(oldp+39,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__instr_error));
    bufp->fullBit(oldp+40,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err));
    bufp->fullBit(oldp+41,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk));
    bufp->fullBit(oldp+42,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk));
    bufp->fullBit(oldp+43,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk));
    bufp->fullCData(oldp+44,((0x000000ffU & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata)),8);
    bufp->fullCData(oldp+45,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                                             >> 8U))),8);
    bufp->fullCData(oldp+46,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+47,((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                              >> 0x00000018U)),8);
    bufp->fullIData(oldp+48,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o),32);
    bufp->fullCData(oldp+49,((0x000000ffU & (~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o))),8);
    bufp->fullCData(oldp+50,((0x000000ffU & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o)),8);
    bufp->fullCData(oldp+51,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                             & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata))),8);
    bufp->fullCData(oldp+52,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                >> 8U)))),8);
    bufp->fullCData(oldp+53,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                             >> 8U))),8);
    bufp->fullCData(oldp+54,((0x000000ffU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                             >> 8U))),8);
    bufp->fullCData(oldp+55,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                >> 0x00000010U)))),8);
    bufp->fullCData(oldp+56,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+57,((0x000000ffU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                             >> 0x00000010U))),8);
    bufp->fullCData(oldp+58,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                >> 0x00000018U)))),8);
    bufp->fullCData(oldp+59,((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                              >> 0x00000018U)),8);
    bufp->fullCData(oldp+60,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                              >> 0x00000018U)),8);
    bufp->fullBit(oldp+61,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req));
    bufp->fullBit(oldp+62,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i));
    bufp->fullBit(oldp+63,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i));
    bufp->fullBit(oldp+64,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i));
    bufp->fullBit(oldp+65,((IData)(((0x8000U == (0xc000U 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))) 
                                    & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i)))));
    bufp->fullBit(oldp+66,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req)))));
    bufp->fullBit(oldp+67,((1U & (~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)))));
    bufp->fullCData(oldp+68,((7U & (IData)(((0x000000000000001fULL 
                                             & ((QData)((IData)(
                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                  ? 
                                                                 (3U 
                                                                  & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                     >> 8U))
                                                                  : 0U))) 
                                                >> 2U)) 
                                            | ((0x000000000000001fULL 
                                                & ((QData)((IData)(
                                                                   ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                     ? 
                                                                    (0x000000ffU 
                                                                     & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                     : 0U))) 
                                                   >> 0x0000000aU)) 
                                               | ((0x000000000000001fULL 
                                                   & ((QData)((IData)(
                                                                      (((~ 
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                          & ((0x00008000U 
                                                                              & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                              ? 
                                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                              | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                              : 
                                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                              >> 0x0000000eU)))) 
                                                                        & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                        ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                        : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                      >> 0x0000002bU)) 
                                                  | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                     >> 0x0000003bU))))))),3);
    bufp->fullCData(oldp+69,((3U & (IData)(((0x000000000000007fULL 
                                             & (QData)((IData)(
                                                               ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                 ? 
                                                                (3U 
                                                                 & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                    >> 8U))
                                                                 : 0U)))) 
                                            | ((0x000000000000007fULL 
                                                & ((QData)((IData)(
                                                                   ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                     ? 
                                                                    (0x000000ffU 
                                                                     & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                     : 0U))) 
                                                   >> 8U)) 
                                               | ((0x000000000000007fULL 
                                                   & ((QData)((IData)(
                                                                      (((~ 
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                          & ((0x00008000U 
                                                                              & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                              ? 
                                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                              | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                              : 
                                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                              >> 0x0000000eU)))) 
                                                                        & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                        ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                        : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                      >> 0x00000029U)) 
                                                  | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                     >> 0x00000039U))))))),2);
    bufp->fullCData(oldp+70,((0x000000ffU & (IData)(
                                                    ((0x0000000000007f00ULL 
                                                      & ((QData)((IData)(
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                           ? 
                                                                          (3U 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                              >> 8U))
                                                                           : 0U))) 
                                                         << 8U)) 
                                                     | ((0x0000000000007fffULL 
                                                         & (QData)((IData)(
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                             ? 
                                                                            (0x000000ffU 
                                                                             & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                             : 0U)))) 
                                                        | ((0x0000000000007fffULL 
                                                            & ((QData)((IData)(
                                                                               (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                               >> 0x00000021U)) 
                                                           | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                              >> 0x00000031U))))))),8);
    bufp->fullBit(oldp+71,((1U & (IData)(((0x000000000000fe00ULL 
                                           & ((QData)((IData)(
                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                ? 
                                                               (3U 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                   >> 8U))
                                                                : 0U))) 
                                              << 9U)) 
                                          | ((0x000000000000fffeULL 
                                              & ((QData)((IData)(
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                   ? 
                                                                  (0x000000ffU 
                                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                   : 0U))) 
                                                 << 1U)) 
                                             | ((0x000000000000ffffULL 
                                                 & ((QData)((IData)(
                                                                    (((~ 
                                                                       ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                        & ((0x00008000U 
                                                                            & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                            ? 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000eU))
                                                                            : 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                            >> 0x0000000eU)))) 
                                                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000fU))))
                                                                      ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                      : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                    >> 0x00000020U)) 
                                                | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                   >> 0x00000030U))))))));
    bufp->fullIData(oldp+72,((IData)(((0x0000fe0000000000ULL 
                                       & ((QData)((IData)(
                                                          ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                            ? 
                                                           (3U 
                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                               >> 8U))
                                                            : 0U))) 
                                          << 0x00000029U)) 
                                      | ((0x0000fffe00000000ULL 
                                          & ((QData)((IData)(
                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                               ? 
                                                              (0x000000ffU 
                                                               & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                               : 0U))) 
                                             << 0x00000021U)) 
                                         | ((0x0000ffffffffffffULL 
                                             & (QData)((IData)(
                                                               (((~ 
                                                                  ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                   & ((0x00008000U 
                                                                       & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                       ? 
                                                                      ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                          >> 0x0000000eU))
                                                                       : 
                                                                      ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                       >> 0x0000000eU)))) 
                                                                 & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                          >> 0x0000000fU))))
                                                                 ? (IData)(
                                                                           (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                            >> 8U))
                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)))) 
                                            | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                               >> 0x00000010U)))))),32);
    bufp->fullCData(oldp+73,((0x0000007fU & (IData)(
                                                    ((0x007f000000000000ULL 
                                                      & ((QData)((IData)(
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                           ? 
                                                                          (3U 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                              >> 8U))
                                                                           : 0U))) 
                                                         << 0x00000030U)) 
                                                     | ((0x007fff0000000000ULL 
                                                         & ((QData)((IData)(
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                              ? 
                                                                             (0x000000ffU 
                                                                              & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                              : 0U))) 
                                                            << 0x00000028U)) 
                                                        | ((0x007fffffffffff80ULL 
                                                            & ((QData)((IData)(
                                                                               (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                               << 7U)) 
                                                           | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                              >> 9U))))))),7);
    bufp->fullCData(oldp+74,((0x0000007fU & (IData)(
                                                    ((0x3f80000000000000ULL 
                                                      & ((QData)((IData)(
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                           ? 
                                                                          (3U 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                              >> 8U))
                                                                           : 0U))) 
                                                         << 0x00000037U)) 
                                                     | ((0x3fff800000000000ULL 
                                                         & ((QData)((IData)(
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                              ? 
                                                                             (0x000000ffU 
                                                                              & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                              : 0U))) 
                                                            << 0x0000002fU)) 
                                                        | ((0x3fffffffffffc000ULL 
                                                            & ((QData)((IData)(
                                                                               (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                               << 0x0000000eU)) 
                                                           | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                              >> 2U))))))),7);
    bufp->fullBit(oldp+75,((1U & (IData)(((0x7f00000000000000ULL 
                                           & ((QData)((IData)(
                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                ? 
                                                               (3U 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                   >> 8U))
                                                                : 0U))) 
                                              << 0x00000038U)) 
                                          | ((0x7fff000000000000ULL 
                                              & ((QData)((IData)(
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                   ? 
                                                                  (0x000000ffU 
                                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                   : 0U))) 
                                                 << 0x00000030U)) 
                                             | ((0x7fffffffffff8000ULL 
                                                 & ((QData)((IData)(
                                                                    (((~ 
                                                                       ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                        & ((0x00008000U 
                                                                            & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                            ? 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000eU))
                                                                            : 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                            >> 0x0000000eU)))) 
                                                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000fU))))
                                                                      ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                      : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                    << 0x0000000fU)) 
                                                | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                   >> 1U))))))));
    bufp->fullBit(oldp+76,((1U & (IData)((((QData)((IData)(
                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                             ? 
                                                            (3U 
                                                             & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                >> 8U))
                                                             : 0U))) 
                                           << 0x00000039U) 
                                          | (((QData)((IData)(
                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                ? 
                                                               (0x000000ffU 
                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                : 0U))) 
                                              << 0x00000031U) 
                                             | (((QData)((IData)(
                                                                 (((~ 
                                                                    ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                     & ((0x00008000U 
                                                                         & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                         ? 
                                                                        ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                         | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                            >> 0x0000000eU))
                                                                         : 
                                                                        ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                         >> 0x0000000eU)))) 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                            >> 0x0000000fU))))
                                                                   ? (IData)(
                                                                             (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                              >> 8U))
                                                                   : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                 << 0x00000010U) 
                                                | (QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)))))))));
    bufp->fullBit(oldp+77,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                            & ((0x00008000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                ? ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                   | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                      >> 0x0000000eU))
                                : ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                   >> 0x0000000eU)))));
    bufp->fullIData(oldp+78,((((~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                   & ((0x00008000U 
                                       & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                       ? ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                             >> 0x0000000eU))
                                       : ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                          >> 0x0000000eU)))) 
                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                  & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                     & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                        >> 0x0000000fU))))
                               ? (IData)((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                          >> 8U)) : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)),32);
    bufp->fullCData(oldp+79,(((0x00004000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                               ? 0x0000002aU : (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                 & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                       >> 0x0000000fU)))
                                                 ? 
                                                (0x0000007fU 
                                                 & (IData)(
                                                           (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                            >> 1U)))
                                                 : 0x0000002aU))),7);
    bufp->fullBit(oldp+80,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                  ^ (VL_REDXOR_32((
                                                   ((~ 
                                                     ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                      >> 0x0000000fU)) 
                                                    & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid))
                                                    ? 0U
                                                    : 1U)) 
                                     ^ (VL_REDXOR_32(
                                                     ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                       ? 
                                                      (3U 
                                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                          >> 8U))
                                                       : 0U)) 
                                        ^ (VL_REDXOR_32(
                                                        ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                          ? 
                                                         (0x000000ffU 
                                                          & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                          : 0U)) 
                                           ^ (VL_REDXOR_32(
                                                           (((~ 
                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                               & ((0x00008000U 
                                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                   ? 
                                                                  ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                   | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                      >> 0x0000000eU))
                                                                   : 
                                                                  ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                   >> 0x0000000eU)))) 
                                                             & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                      >> 0x0000000fU))))
                                                             ? (IData)(
                                                                       (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                        >> 8U))
                                                             : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)) 
                                              ^ VL_REDXOR_16(vlSelfRef.__VdfgRegularize_he50b618e_0_1)))))))));
    bufp->fullCData(oldp+81,((0x0000007fU & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                             >> 9U))),7);
    bufp->fullCData(oldp+82,((0x0000007fU & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                             >> 2U))),7);
    bufp->fullBit(oldp+83,((1U & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                  >> 1U))));
    bufp->fullBit(oldp+84,((1U & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1))));
    bufp->fullIData(oldp+85,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword),32);
    bufp->fullIData(oldp+86,((IData)((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                      >> 8U))),32);
    bufp->fullCData(oldp+87,((0x0000007fU & (IData)(
                                                    (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                     >> 1U)))),7);
    bufp->fullBit(oldp+88,((1U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o))));
    bufp->fullQData(oldp+89,(((QData)((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword)) 
                              << 8U)),40);
    bufp->fullQData(oldp+91,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o),40);
    bufp->fullBit(oldp+93,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag));
    bufp->fullBit(oldp+94,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag));
    bufp->fullBit(oldp+95,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag));
    bufp->fullBit(oldp+96,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag));
    bufp->fullBit(oldp+97,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag));
    bufp->fullBit(oldp+98,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag));
    bufp->fullBit(oldp+99,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag));
    bufp->fullBit(oldp+100,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag));
    bufp->fullBit(oldp+101,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag));
    bufp->fullBit(oldp+102,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag));
    bufp->fullBit(oldp+103,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag));
    bufp->fullBit(oldp+104,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag));
    bufp->fullSData(oldp+105,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__storage),16);
    bufp->fullQData(oldp+106,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage),40);
    bufp->fullCData(oldp+108,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__storage),5);
    bufp->fullCData(oldp+109,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cdx),8);
    bufp->fullCData(oldp+110,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cdx),8);
    bufp->fullCData(oldp+111,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cdx),8);
    bufp->fullCData(oldp+112,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cdx),8);
    bufp->fullBit(oldp+113,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid));
    bufp->fullBit(oldp+114,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid_q));
    bufp->fullBit(oldp+115,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__intg_error_q));
    bufp->fullBit(oldp+116,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
    bufp->fullBit(oldp+117,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q));
    bufp->fullBit(oldp+118,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
    bufp->fullBit(oldp+119,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i));
    bufp->fullBit(oldp+120,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
    bufp->fullBit(oldp+121,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o));
    bufp->fullBit(oldp+122,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__missed_err_gnt_q));
    bufp->fullBit(oldp+123,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q));
    bufp->fullBit(oldp+124,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q));
    bufp->fullBit(oldp+125,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid));
    bufp->fullCData(oldp+126,((((~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                    >> 0x0000000fU)) 
                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid))
                                ? 0U : 1U)),3);
    bufp->fullBit(oldp+127,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                   >> 0x0000000fU))));
    bufp->fullBit(oldp+128,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                   >> 0x0000000eU))));
    bufp->fullCData(oldp+129,((0x0000000fU & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                              >> 0x0000000aU))),4);
    bufp->fullCData(oldp+130,((3U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                     >> 8U))),2);
    bufp->fullCData(oldp+131,((0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))),8);
    bufp->fullCData(oldp+132,((0x0000000fU & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                              >> 1U))),4);
    bufp->fullBit(oldp+133,((1U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o))));
    bufp->fullCData(oldp+134,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o),5);
    bufp->fullIData(oldp+135,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data),32);
    bufp->fullIData(oldp+136,(((((0x0000ff00U & ((- (IData)(
                                                            (1U 
                                                             & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                >> 4U)))) 
                                                 << 8U)) 
                                 | (0x000000ffU & (- (IData)(
                                                             (1U 
                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                 >> 3U)))))) 
                                << 0x00000010U) | (
                                                   (0x0000ff00U 
                                                    & ((- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                      >> 2U)))) 
                                                       << 8U)) 
                                                   | (0x000000ffU 
                                                      & (- (IData)(
                                                                   (1U 
                                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                       >> 1U)))))))),32);
    bufp->fullSData(oldp+137,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o),16);
    bufp->fullBit(oldp+138,(vlSelfRef.tb_tlul_sram_if_macro__DOT__clk));
    bufp->fullBit(oldp+139,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rst_n));
    bufp->fullIData(oldp+140,(vlSelfRef.tb_tlul_sram_if_macro__DOT__errors),32);
    bufp->fullIData(oldp+141,(((((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg) 
                                 << 0x00000018U) | 
                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg) 
                                 << 0x00000010U)) | 
                               (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg) 
                                 << 8U) | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg)))),32);
    bufp->fullBit(oldp+142,((1U & (VL_REDXOR_32((0x00078000U 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U])) 
                                   ^ VL_REDXOR_16((0xff00U 
                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr)))))));
    bufp->fullBit(oldp+143,((1U & ((~ (((0U == (7U 
                                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                   >> 0x0000000eU))) 
                                        | ((1U == (7U 
                                                   & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                      >> 0x0000000eU))) 
                                           | (4U == 
                                              (7U & 
                                               (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                >> 0x0000000eU))))) 
                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk) 
                                          & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk) 
                                             & ((4U 
                                                 == 
                                                 (7U 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                     >> 0x0000000eU))) 
                                                | ((1U 
                                                    == 
                                                    (7U 
                                                     & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                        >> 0x0000000eU))) 
                                                   | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk))))))) 
                                   | ((~ ((6U == (0x0000000fU 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                     >> 0x0000000fU))) 
                                          | (9U == 
                                             (0x0000000fU 
                                              & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                 >> 0x0000000fU))))) 
                                      | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err))))));
    bufp->fullBit(oldp+144,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                             & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                   >> 0x0000000fU)))));
    bufp->fullBit(oldp+145,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det) 
                             & ((~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0)) 
                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                   >> 0x00000011U)))));
    bufp->fullBit(oldp+146,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk) 
                             & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk) 
                                & ((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                 >> 0x0000000eU))) 
                                   | ((1U == (7U & 
                                              (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 0x0000000eU))) 
                                      | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk)))))));
    bufp->fullSData(oldp+147,((((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                              >> 0x0000000eU))) 
                                << 0x0000000fU) | (
                                                   ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det) 
                                                    << 0x0000000eU) 
                                                   | ((0x00003c00U 
                                                       & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                          >> 5U)) 
                                                      | (0x000003ffU 
                                                         & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                            >> 1U)))))),16);
    bufp->fullBit(oldp+148,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                                    ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i))
                                    : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i)))));
    bufp->fullBit(oldp+149,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o)
                                    ? (~ (IData)(((0x8000U 
                                                   == 
                                                   (0xc000U 
                                                    & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))) 
                                                  & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i))))
                                    : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i)))));
    bufp->fullQData(oldp+150,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q)
                                ? vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage
                                : ((QData)((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword)) 
                                   << 8U))),40);
    bufp->fullBit(oldp+152,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                                    ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i))
                                    : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i)))));
    bufp->fullCData(oldp+153,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->fullBit(oldp+154,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->fullBit(oldp+155,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->fullBit(oldp+156,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->fullBit(oldp+157,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->fullBit(oldp+158,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->fullBit(oldp+159,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->fullBit(oldp+160,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->fullBit(oldp+161,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->fullBit(oldp+162,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->fullBit(oldp+163,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->fullBit(oldp+164,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->fullBit(oldp+165,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->fullBit(oldp+166,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->fullBit(oldp+167,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->fullBit(oldp+168,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah) 
                                         | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh) 
                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh) 
                                               | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->fullBit(oldp+169,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                         | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->fullBit(oldp+170,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly));
    bufp->fullBit(oldp+171,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->fullBit(oldp+172,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->fullBit(oldp+173,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_dly));
    bufp->fullBit(oldp+174,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell));
    bufp->fullBit(oldp+175,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->fullCData(oldp+176,(((~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o) 
                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem
                               [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->fullCData(oldp+177,((0x000000ffU & (((~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o) 
                                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem
                                               [(0x000000ffU 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                              | (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata)))),8);
    bufp->fullCData(oldp+178,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->fullCData(oldp+179,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->fullCData(oldp+180,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->fullCData(oldp+181,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->fullCData(oldp+182,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->fullBit(oldp+183,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->fullCData(oldp+184,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->fullBit(oldp+185,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->fullBit(oldp+186,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->fullBit(oldp+187,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->fullBit(oldp+188,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->fullBit(oldp+189,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->fullBit(oldp+190,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->fullBit(oldp+191,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->fullBit(oldp+192,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->fullBit(oldp+193,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->fullBit(oldp+194,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->fullBit(oldp+195,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->fullBit(oldp+196,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->fullBit(oldp+197,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->fullBit(oldp+198,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->fullBit(oldp+199,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah) 
                                         | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh) 
                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh) 
                                               | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->fullBit(oldp+200,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                         | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->fullBit(oldp+201,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly));
    bufp->fullBit(oldp+202,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->fullBit(oldp+203,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->fullBit(oldp+204,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_dly));
    bufp->fullBit(oldp+205,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell));
    bufp->fullBit(oldp+206,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->fullCData(oldp+207,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                   >> 8U)) & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem
                               [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->fullCData(oldp+208,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 8U)) 
                                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem
                                               [(0x000000ffU 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                              | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                 >> 8U)))),8);
    bufp->fullCData(oldp+209,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->fullCData(oldp+210,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->fullCData(oldp+211,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->fullCData(oldp+212,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->fullCData(oldp+213,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->fullBit(oldp+214,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->fullCData(oldp+215,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->fullBit(oldp+216,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->fullBit(oldp+217,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->fullBit(oldp+218,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->fullBit(oldp+219,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->fullBit(oldp+220,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->fullBit(oldp+221,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->fullBit(oldp+222,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->fullBit(oldp+223,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->fullBit(oldp+224,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->fullBit(oldp+225,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->fullBit(oldp+226,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->fullBit(oldp+227,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->fullBit(oldp+228,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->fullBit(oldp+229,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->fullBit(oldp+230,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah) 
                                         | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh) 
                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh) 
                                               | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->fullBit(oldp+231,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                         | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->fullBit(oldp+232,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly));
    bufp->fullBit(oldp+233,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->fullBit(oldp+234,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->fullBit(oldp+235,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_dly));
    bufp->fullBit(oldp+236,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell));
    bufp->fullBit(oldp+237,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->fullCData(oldp+238,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                   >> 0x00000010U)) 
                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem
                               [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->fullCData(oldp+239,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 0x00000010U)) 
                                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem
                                               [(0x000000ffU 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                              | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                 >> 0x00000010U)))),8);
    bufp->fullCData(oldp+240,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->fullCData(oldp+241,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->fullCData(oldp+242,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->fullCData(oldp+243,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->fullCData(oldp+244,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->fullBit(oldp+245,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->fullCData(oldp+246,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->fullBit(oldp+247,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->fullBit(oldp+248,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->fullBit(oldp+249,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->fullBit(oldp+250,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->fullBit(oldp+251,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->fullBit(oldp+252,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->fullBit(oldp+253,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->fullBit(oldp+254,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->fullBit(oldp+255,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->fullBit(oldp+256,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->fullBit(oldp+257,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->fullBit(oldp+258,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->fullBit(oldp+259,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->fullBit(oldp+260,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->fullBit(oldp+261,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah) 
                                         | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh) 
                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh) 
                                               | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->fullBit(oldp+262,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                         | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->fullBit(oldp+263,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly));
    bufp->fullBit(oldp+264,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->fullBit(oldp+265,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->fullBit(oldp+266,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_dly));
    bufp->fullBit(oldp+267,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell));
    bufp->fullBit(oldp+268,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->fullCData(oldp+269,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                   >> 0x00000018U)) 
                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem
                               [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->fullCData(oldp+270,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 0x00000018U)) 
                                               & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem
                                               [(0x000000ffU 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                              | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                 >> 0x00000018U)))),8);
    bufp->fullCData(oldp+271,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->fullCData(oldp+272,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->fullCData(oldp+273,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->fullCData(oldp+274,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->fullCData(oldp+275,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->fullBit(oldp+276,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag_dly));
}
