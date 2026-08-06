// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_tlul_sram_if_macro__pch.h"
#include "verilated_fst_c.h"

//============================================================
// Constructors

Vtb_tlul_sram_if_macro::Vtb_tlul_sram_if_macro(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_tlul_sram_if_macro__Syms(contextp(), _vcname__, this)}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vtb_tlul_sram_if_macro::Vtb_tlul_sram_if_macro(const char* _vcname__)
    : Vtb_tlul_sram_if_macro(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_tlul_sram_if_macro::~Vtb_tlul_sram_if_macro() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_tlul_sram_if_macro___024root___eval_debug_assertions(Vtb_tlul_sram_if_macro___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_tlul_sram_if_macro___024root___eval_static(Vtb_tlul_sram_if_macro___024root* vlSelf);
void Vtb_tlul_sram_if_macro___024root___eval_initial(Vtb_tlul_sram_if_macro___024root* vlSelf);
void Vtb_tlul_sram_if_macro___024root___eval_settle(Vtb_tlul_sram_if_macro___024root* vlSelf);
void Vtb_tlul_sram_if_macro___024root___eval(Vtb_tlul_sram_if_macro___024root* vlSelf);

void Vtb_tlul_sram_if_macro::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_tlul_sram_if_macro::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_tlul_sram_if_macro___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_tlul_sram_if_macro___024root___eval_static(&(vlSymsp->TOP));
        Vtb_tlul_sram_if_macro___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_tlul_sram_if_macro___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_tlul_sram_if_macro___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vtb_tlul_sram_if_macro::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vtb_tlul_sram_if_macro::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool Vtb_tlul_sram_if_macro::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_tlul_sram_if_macro::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_tlul_sram_if_macro::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_tlul_sram_if_macro___024root___eval_final(Vtb_tlul_sram_if_macro___024root* vlSelf);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro::final() {
    Vtb_tlul_sram_if_macro___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_tlul_sram_if_macro::hierName() const { return vlSymsp->name(); }
const char* Vtb_tlul_sram_if_macro::modelName() const { return "Vtb_tlul_sram_if_macro"; }
unsigned Vtb_tlul_sram_if_macro::threads() const { return 1; }
void Vtb_tlul_sram_if_macro::prepareClone() const { contextp()->prepareClone(); }
void Vtb_tlul_sram_if_macro::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vtb_tlul_sram_if_macro::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vtb_tlul_sram_if_macro___024root__trace_decl_types(VerilatedFst* tracep);

void Vtb_tlul_sram_if_macro___024root__trace_init_top(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedFst* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtb_tlul_sram_if_macro___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_tlul_sram_if_macro___024root*>(voidSelf);
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_tlul_sram_if_macro___024root__trace_decl_types(tracep);
    Vtb_tlul_sram_if_macro___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root__trace_register(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedFstC* const stfp = dynamic_cast<VerilatedFstC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtb_tlul_sram_if_macro::trace()' called on non-VerilatedFstC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 368);
    Vtb_tlul_sram_if_macro___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
