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
	fusesoc --cores-root ../.. run --target=sim --tool=verilator xinting:playground:pure_ibex_uart

# waves: identical to run; keep target for compatibility
waves: run

# Copy generated waveform to current dir
copy:
	cp build/xinting_playground_pure_ibex_uart_0.1/sim-verilator/mini.fst ./

