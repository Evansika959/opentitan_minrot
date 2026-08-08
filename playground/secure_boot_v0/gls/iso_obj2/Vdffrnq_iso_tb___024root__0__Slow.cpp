// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdffrnq_iso_tb.h for the primary calling header

#include "Vdffrnq_iso_tb__pch.h"

void Vdffrnq_iso_tb___024root___timing_ready(Vdffrnq_iso_tb___024root* vlSelf);

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___eval_static(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_static\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0 
        = vlSelfRef.dffrnq_iso_tb__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__rn__0 
        = vlSelfRef.dffrnq_iso_tb__DOT__rn;
    Vdffrnq_iso_tb___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___eval_initial__TOP(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_initial__TOP\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.dffrnq_iso_tb__DOT__clk = 0U;
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___eval_final(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_final\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___eval_settle(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_settle\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vdffrnq_iso_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdffrnq_iso_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vdffrnq_iso_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge dffrnq_iso_tb.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge dffrnq_iso_tb.rn)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___ctor_var_reset(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___ctor_var_reset\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->dffrnq_iso_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2369379297667503232ull);
    vlSelf->dffrnq_iso_tb__DOT__rn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16894810071391063721ull);
    vlSelf->dffrnq_iso_tb__DOT__d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11757732246277827961ull);
    vlSelf->dffrnq_iso_tb__DOT__q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18252261578329691970ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__rn__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
