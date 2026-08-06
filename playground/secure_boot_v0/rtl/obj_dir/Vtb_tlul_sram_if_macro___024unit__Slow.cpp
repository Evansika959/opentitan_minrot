// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tlul_sram_if_macro.h for the primary calling header

#include "Vtb_tlul_sram_if_macro__pch.h"

void Vtb_tlul_sram_if_macro___024unit___ctor_var_reset(Vtb_tlul_sram_if_macro___024unit* vlSelf);

Vtb_tlul_sram_if_macro___024unit::Vtb_tlul_sram_if_macro___024unit() = default;
Vtb_tlul_sram_if_macro___024unit::~Vtb_tlul_sram_if_macro___024unit() = default;

void Vtb_tlul_sram_if_macro___024unit::ctor(Vtb_tlul_sram_if_macro__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_tlul_sram_if_macro___024unit___ctor_var_reset(this);
}

void Vtb_tlul_sram_if_macro___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_tlul_sram_if_macro___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
