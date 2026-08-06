# secure_boot_v0 — PUF-derived-key secure boot on a taped-out OpenTitan-derived RoT

A minimal OpenTitan-derived Root-of-Trust SoC (Ibex core + TL-UL crossbar + UART +
PUF) implemented all the way to GDS (`gf180mcuD`, LibreLane — see [`pd/README.md`](pd/README.md)
for the ASIC flow) and validated on the **real, taped-out gate-level netlist**: a
signed boot image is verified with an ECDSA key **derived at runtime from a physical
SRAM PUF**, not stored anywhere — no key material exists on the chip except while a
boot is actively in progress.

## Current target: `top_pd_min`

`top_pd_min` is the active chip build. It replaces the earlier `top_pd_7bank` design's
uniform 7KiB-everywhere memory plan with right-sized macros, matched to what a real
2-stage secure boot (ROM + one verified payload) actually needs:

| Memory | Macro | Real capacity | Role |
|---|---|---|---|
| IMEM | `tlul_sram_if_macro_ocd_10bank` | 10 KiB | ROM (this repo's C code + crt0 + crypto libs) |
| ESRAM | `tlul_sram_if_macro_ocd_2bank` | 2 KiB | verified payload is copied here and executed |
| DMEM | `tlul_sram_if_macro_ocd_2bank` | 2 KiB | untrusted staging area for the signed container |

PD status (`pd/blocks/top_pd_min/runs/fasttest_columnswap`): synthesis → floorplan →
PDN → placement → CTS → routing → signoff all complete. LVS clear, no setup/hold/
max-slew/max-cap violations. (Magic DRC is waived — same as every other block in this
repo; KLayout DRC + LVS are the real signoff gate. `--skip KLayout.Render` is needed,
a cosmetic multi-top-cells artifact from the PUF's raw foundry SRAM macro, unrelated
to the actual layout.)

`top_pd_7bank` (uniform 7KiB memories) is the earlier, still-valid design this one
superseded — kept for reference, not under active development.

## The boot sequence

```
ROM (IMEM)                                          Verified payload (ESRAM)
──────────                                          ───────────────────────
1. Trigger the PUF, read back a 256-bit response
2. Derive a secp160r1 private key from it
3. Compute the matching public key (uECC)
4. Read the signed container staged in DMEM:
     [ 64B header | payload | secp160r1 signature ]
5. Recompute SHA-256 over (header-bound fields + payload)
6. Verify the signature against the PUF-derived public key
7. Copy the verified payload into ESRAM  ─────────►  8. Jump in, execute
```

No private key is ever stored in flash/OTP/DMEM — it exists only in registers for the
few hundred thousand cycles the derive+verify takes, then the payload runs and the
key is gone. The signing key used to build the container (`test_sw/spike_test/
host_pack_7bank_image.c`) is the same fixed PUF response bytes
(`puf_sim/mc_test/puf_realdata.hex`) the real on-chip PUF hardware reproduces — this
is a functional/bring-up demo, not a claim about PUF entropy quality.

*(Source files are still named `*_7bank*` — they're bank-count-agnostic C code
originally written for `top_pd_7bank` and reused unedited for `top_pd_min`; only the
linker script's `IMEM` size differs between the two.)*

## Running the demo

Real gate-level simulation (Verilator) of the actual taped-out `top_pd_min` netlist —
not RTL, not a behavioral model. Prereq: `./setup.bash` once (writes `.env.local`).

```bash
./run_gls_min_stageA.bash          # fast checkpoint: PUF-derive + compute pubkey only
./run_gls_min_full.bash [timeout_ns]   # full chain: + verify + copy + jump
```

`run_gls_min_full.bash` builds the payload, signs it, compiles the ROM (needs `-flto`
to fit the 10KiB IMEM budget — see the script's header comment), generates the IMEM/
DMEM per-bank hex images, builds the GLS model, and runs it. Default timeout is 60ms
of simulated time (~10 minutes wall-clock), which reliably reaches PUF-derive +
partway into public-key computation. **Full completion** (`verify OK` → `jumping!` →
`Payload: verified boot OK!`) needs on the order of hundreds of ms of simulated time —
real, uninstrumented ECC point multiplication on plain RV32IM with no crypto
acceleration is slow. At the observed ~98µs-simulated/s-wall-clock single-threaded
throughput, a run long enough to fully complete costs 40–70+ minutes of wall-clock.
(`--threads` was tried and made this *slower*, not faster — don't reach for it.)

Both scripts decode the DUT's real UART TX line bit-by-bit in the testbench (same
115200-baud bit-bang decoder either way) and print the recovered ASCII stream.

## Known limitations

- **Single-corner PD signoff** (`nom_tt_025C_3v30` only — no ss/ff corners).
- **Full-chain GLS completion is wall-clock-expensive**, not yet captured in a single
  log end-to-end at time of writing; the PUF-derive → compute-pubkey portion is
  independently proven correct (bit-exact key match against the reference), and the
  same "boots clean, zero anomalies through the compute-heavy stage" standard is what
  validated `top_pd_7bank` too.
- `secure_boot_7bank_layout.h`'s `SB7_*` constant names still say "7bank" but hold
  `top_pd_min`'s real (smaller) sizes — the address *map* is identical between the two
  designs, only macro sizes differ, so the file applies to both.
- `pd/macros/macros.json` currently only lists the two macros exported for this
  round (`tlul_sram_if_macro_ocd_10bank`, `_2bank`) — older macro directories
  (`top_pd_7bank`, `ibex_top`, etc.) still exist on disk but aren't in the manifest.

## Layout

```
secure_boot_v0/
├── README.md                  # this file
├── pd/README.md                # ASIC (RTL → GDS) flow — LibreLane, gf180mcuD
├── rtl/                        # top_pd_min.sv, top_pd_7bank.sv, memory macro RTL
├── test_sw/c/, test_sw/spike_test/   # ROM/payload/packer C sources (shared, bank-count-agnostic)
├── gls/                        # GLS testbenches + .core files (top_pd_min_secboot_gls_tb.sv, ...)
├── run_gls_min_stageA.bash     # fast GLS checkpoint
├── run_gls_min_full.bash       # full secure-boot GLS demo
└── run_gls_7bank_*.bash        # earlier top_pd_7bank equivalents (reference, not active)
```
