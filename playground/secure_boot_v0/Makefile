# Simple Verilator build for pure_ibex_uart + tb
# Usage:
#   make run          # build and run
#   make build        # only build (same as run)
#   make waves        # run and keep FST (mini.fst)
#
# Requirements: fusesoc + verilator. Run from this dir.

.PHONY: all run build waves copy

all: run
run:
	fusesoc --cores-root ../.. run --target=sim --tool=verilator xinting:playground:secure_boot_v0

# waves: identical to run; keep target for compatibility
waves: run

xbar_gen:
	python ../../util/tlgen.py -t ./hjson/tlul_2to4.hjson --o ./rtl/autogen/

# Copy generated waveform to current dir
copy:
	cp build/xinting_playground_secure_boot_v0_0.1/sim-verilator/secure_boot_v0.fst ./

