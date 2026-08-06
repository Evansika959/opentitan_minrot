// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_tlul_sram_if_macro.h for the primary calling header

#ifndef VERILATED_VTB_TLUL_SRAM_IF_MACRO___024UNIT_H_
#define VERILATED_VTB_TLUL_SRAM_IF_MACRO___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_tlul_sram_if_macro__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_tlul_sram_if_macro___024unit final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VmonitorOff;

    // INTERNAL VARIABLES
    Vtb_tlul_sram_if_macro__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_tlul_sram_if_macro___024unit();
    ~Vtb_tlul_sram_if_macro___024unit();
    void ctor(Vtb_tlul_sram_if_macro__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_tlul_sram_if_macro___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
