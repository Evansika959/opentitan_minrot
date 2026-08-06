// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tlul_sram_if_macro.h for the primary calling header

#include "Vtb_tlul_sram_if_macro__pch.h"

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024unit___ctor_var_reset(Vtb_tlul_sram_if_macro___024unit* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vtb_tlul_sram_if_macro___024unit___ctor_var_reset\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__VmonitorOff = 0;
}
