// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdffrnq_iso_tb.h for the primary calling header

#include "Vdffrnq_iso_tb__pch.h"

VL_ATTR_COLD void Vdffrnq_iso_tb___024root___eval_initial__TOP(Vdffrnq_iso_tb___024root* vlSelf);
VlCoroutine Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__0(Vdffrnq_iso_tb___024root* vlSelf);
VlCoroutine Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__1(Vdffrnq_iso_tb___024root* vlSelf);

void Vdffrnq_iso_tb___024root___eval_initial(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_initial\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vdffrnq_iso_tb___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vdffrnq_iso_tb___024root____VbeforeTrig_h6d61be83__0(Vdffrnq_iso_tb___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__0(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    // Body
    vlSelfRef.dffrnq_iso_tb__DOT__d = 1U;
    vlSelfRef.dffrnq_iso_tb__DOT__rn = 0U;
    VL_WRITEF_NX("[ISO] t=%0t rn=0 d=1 q=1 (expect q=0, reset asserted)\n",0,
                 64,VL_TIME_UNITED_Q(1000),-9);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "dffrnq_iso_tb.sv", 
                                         13);
    VL_WRITEF_NX("[ISO] t=%0t rn=%b d=%b q=1 (expect q=0, still in reset)\n",0,
                 64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn),
                 1,vlSelfRef.dffrnq_iso_tb__DOT__d);
    dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 5U;
    while (VL_LTS_III(32, 0U, dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vdffrnq_iso_tb___024root____VbeforeTrig_h6d61be83__0(vlSelf, 
                                                             "@(posedge dffrnq_iso_tb.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h6d61be83__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge dffrnq_iso_tb.clk)", 
                                                             "dffrnq_iso_tb.sv", 
                                                             15);
        dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (dffrnq_iso_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    VL_WRITEF_NX("[ISO] t=%0t rn=%b d=%b q=1 (expect q=0, still in reset, after clock edges)\n",0,
                 64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn),
                 1,vlSelfRef.dffrnq_iso_tb__DOT__d);
    vlSelfRef.dffrnq_iso_tb__DOT__rn = 1U;
    Vdffrnq_iso_tb___024root____VbeforeTrig_h6d61be83__0(vlSelf, 
                                                         "@(posedge dffrnq_iso_tb.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h6d61be83__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge dffrnq_iso_tb.clk)", 
                                                         "dffrnq_iso_tb.sv", 
                                                         18);
    VL_WRITEF_NX("[ISO] t=%0t rn=%b d=%b q=1 (expect q=1 now: reset released, D=1 captured on edge)\n",0,
                 64,VL_TIME_UNITED_Q(1000),-9,1,(IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn),
                 1,vlSelfRef.dffrnq_iso_tb__DOT__d);
    VL_FINISH_MT("dffrnq_iso_tb.sv", 20, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

VlCoroutine Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__1(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000007530ULL, 
                                             nullptr, 
                                             "dffrnq_iso_tb.sv", 
                                             5);
        vlSelfRef.dffrnq_iso_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk)));
    }
    co_return;
}

void Vdffrnq_iso_tb___024root___eval_triggers_vec__act(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_triggers_vec__act\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk) 
                                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0))) 
                                                      << 1U) 
                                                     | vlSelfRef.__VdlySched.awaitingCurrentTime())));
    vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0 
        = vlSelfRef.dffrnq_iso_tb__DOT__clk;
}

bool Vdffrnq_iso_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vdffrnq_iso_tb___024root___timing_ready(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___timing_ready\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h6d61be83__0.ready("@(posedge dffrnq_iso_tb.clk)");
    }
}

void Vdffrnq_iso_tb___024root___timing_resume(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___timing_resume\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h6d61be83__0.moveToResumeQueue(
                                                          "@(posedge dffrnq_iso_tb.clk)");
    vlSelfRef.__VtrigSched_h6d61be83__0.resume("@(posedge dffrnq_iso_tb.clk)");
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vdffrnq_iso_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdffrnq_iso_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vdffrnq_iso_tb___024root___eval_phase__act(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_phase__act\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vdffrnq_iso_tb___024root___eval_triggers_vec__act(vlSelf);
    Vdffrnq_iso_tb___024root___timing_ready(vlSelf);
    Vdffrnq_iso_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdffrnq_iso_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vdffrnq_iso_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vdffrnq_iso_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vdffrnq_iso_tb___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vdffrnq_iso_tb___024root___eval_phase__inact(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_phase__inact\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("dffrnq_iso_tb.sv", 2, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vdffrnq_iso_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vdffrnq_iso_tb___024root___eval_phase__nba(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_phase__nba\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vdffrnq_iso_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vdffrnq_iso_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vdffrnq_iso_tb___024root___eval(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vdffrnq_iso_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("dffrnq_iso_tb.sv", 2, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("dffrnq_iso_tb.sv", 2, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vdffrnq_iso_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("dffrnq_iso_tb.sv", 2, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vdffrnq_iso_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vdffrnq_iso_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vdffrnq_iso_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vdffrnq_iso_tb___024root____VbeforeTrig_h6d61be83__0(Vdffrnq_iso_tb___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root____VbeforeTrig_h6d61be83__0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk) 
                                   & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0))) 
                                  << 1U)));
    vlSelfRef.__Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0 
        = vlSelfRef.dffrnq_iso_tb__DOT__clk;
    if ((2ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h6d61be83__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6d61be83__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vdffrnq_iso_tb___024root___eval_debug_assertions(Vdffrnq_iso_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root___eval_debug_assertions\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
