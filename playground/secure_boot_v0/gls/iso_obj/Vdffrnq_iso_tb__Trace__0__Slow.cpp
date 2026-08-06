// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vdffrnq_iso_tb__Syms.h"


VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_init_sub__TOP__0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_init_sub__TOP__0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("dffrnq_iso_tb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+6,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rn",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+6,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"RN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"notifier",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"MGM_W0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"ENABLE_NOT_D_AND_RN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"ENABLE_D_AND_RN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"ENABLE_RN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"MGM_W1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"MGM_W2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"ENABLE_NOT_CLK_AND_NOT_D",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"MGM_W3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"ENABLE_NOT_CLK_AND_D",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"MGM_W4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"ENABLE_CLK_AND_NOT_D",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"ENABLE_CLK_AND_D",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("gf180mcu_fd_sc_mcu7t5v0__dffrnq_inst", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+6,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"RN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"notifier",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+5,0,"MGM_P0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"MGM_D0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"IQ1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_init_top(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_init_top\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vdffrnq_iso_tb___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vdffrnq_iso_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vdffrnq_iso_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_register(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_register\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vdffrnq_iso_tb___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vdffrnq_iso_tb___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vdffrnq_iso_tb___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vdffrnq_iso_tb___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_const_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_const_0\n"); );
    // Body
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vdffrnq_iso_tb___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_const_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_const_0_sub_0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+12,(1U));
    bufp->fullBit(oldp+13,(vlSelfRef.dffrnq_iso_tb__DOT__dut__DOT__notifier));
    bufp->fullBit(oldp+14,(0U));
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_full_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_full_0\n"); );
    // Body
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vdffrnq_iso_tb___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_full_0_sub_0(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_full_0_sub_0\n"); );
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.dffrnq_iso_tb__DOT__rn));
    bufp->fullBit(oldp+1,(vlSelfRef.dffrnq_iso_tb__DOT__d));
    bufp->fullBit(oldp+2,((1U & (~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d)))));
    bufp->fullBit(oldp+3,(((~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d)) 
                           & (IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn))));
    bufp->fullBit(oldp+4,(((IData)(vlSelfRef.dffrnq_iso_tb__DOT__d) 
                           & (IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn))));
    bufp->fullBit(oldp+5,((1U & (~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__rn)))));
    bufp->fullBit(oldp+6,(vlSelfRef.dffrnq_iso_tb__DOT__clk));
    bufp->fullBit(oldp+7,((1U & (~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk)))));
    bufp->fullBit(oldp+8,((1U & ((~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d)) 
                                 & (~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk))))));
    bufp->fullBit(oldp+9,(((~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk)) 
                           & (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d))));
    bufp->fullBit(oldp+10,(((~ (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d)) 
                            & (IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk))));
    bufp->fullBit(oldp+11,(((IData)(vlSelfRef.dffrnq_iso_tb__DOT__clk) 
                            & (IData)(vlSelfRef.dffrnq_iso_tb__DOT__d))));
}
