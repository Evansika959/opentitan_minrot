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
    tracep->declBit(c+0,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"rn",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"q",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+0,0,"CLK",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"D",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+1,0,"RN",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"Q",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
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

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdffrnq_iso_tb___024root__trace_const_0\n"); );
    // Body
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
    bufp->fullBit(oldp+0,(vlSelfRef.dffrnq_iso_tb__DOT__clk));
    bufp->fullBit(oldp+1,(vlSelfRef.dffrnq_iso_tb__DOT__rn));
    bufp->fullBit(oldp+2,(vlSelfRef.dffrnq_iso_tb__DOT__d));
    bufp->fullBit(oldp+3,(vlSelfRef.dffrnq_iso_tb__DOT__q));
}
