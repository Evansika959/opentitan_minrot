// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdffrnq_iso_tb.h for the primary calling header

#ifndef VERILATED_VDFFRNQ_ISO_TB___024ROOT_H_
#define VERILATED_VDFFRNQ_ISO_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vdffrnq_iso_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdffrnq_iso_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ dffrnq_iso_tb__DOT__clk;
    CData/*0:0*/ dffrnq_iso_tb__DOT__rn;
    CData/*0:0*/ dffrnq_iso_tb__DOT__d;
    CData/*0:0*/ dffrnq_iso_tb__DOT__dut__DOT__notifier;
    CData/*0:0*/ __Vtrigprevexpr___TOP__dffrnq_iso_tb__DOT__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h6d61be83__0;

    // INTERNAL VARIABLES
    Vdffrnq_iso_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vdffrnq_iso_tb___024root(Vdffrnq_iso_tb__Syms* symsp, const char* namep);
    ~Vdffrnq_iso_tb___024root();
    VL_UNCOPYABLE(Vdffrnq_iso_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
