// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vdffrnq_iso_tb__Syms.h"


void Vdffrnq_iso_tb___024root__trace_chg_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vdffrnq_iso_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_chg_0\n"); );
    // Body
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vdffrnq_iso_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vdffrnq_iso_tb___024root__trace_chg_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_chg_0_sub_0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    bufp->chgBit(oldp+0,(vlSelfRef.dffrnq_iso_tb__DOT__clk));
    bufp->chgBit(oldp+1,(vlSelfRef.dffrnq_iso_tb__DOT__rn));
    bufp->chgBit(oldp+2,(vlSelfRef.dffrnq_iso_tb__DOT__d));
    bufp->chgBit(oldp+3,(vlSelfRef.dffrnq_iso_tb__DOT__q));
}

void Vdffrnq_iso_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
