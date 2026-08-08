// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdffrnq_iso_tb.h for the primary calling header

#include "Vdffrnq_iso_tb__pch.h"

void Vdffrnq_iso_tb___024root___ctor_var_reset(Vdffrnq_iso_tb___024root* vlSelf);

Vdffrnq_iso_tb___024root::Vdffrnq_iso_tb___024root(Vdffrnq_iso_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vdffrnq_iso_tb___024root___ctor_var_reset(this);
}

void Vdffrnq_iso_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vdffrnq_iso_tb___024root::~Vdffrnq_iso_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
