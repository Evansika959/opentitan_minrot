// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdffrnq_iso_tb__pch.h"
#include "verilated_fst_c.h"

//============================================================
// Constructors

Vdffrnq_iso_tb::Vdffrnq_iso_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdffrnq_iso_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vdffrnq_iso_tb::Vdffrnq_iso_tb(const char* _vcname__)
    : Vdffrnq_iso_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdffrnq_iso_tb::~Vdffrnq_iso_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdffrnq_iso_tb___024root___eval_debug_assertions(Vdffrnq_iso_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vdffrnq_iso_tb___024root___eval_static(Vdffrnq_iso_tb___024root* vlSelf);
void Vdffrnq_iso_tb___024root___eval_initial(Vdffrnq_iso_tb___024root* vlSelf);
void Vdffrnq_iso_tb___024root___eval_settle(Vdffrnq_iso_tb___024root* vlSelf);
void Vdffrnq_iso_tb___024root___eval(Vdffrnq_iso_tb___024root* vlSelf);

void Vdffrnq_iso_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdffrnq_iso_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdffrnq_iso_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdffrnq_iso_tb___024root___eval_static(&(vlSymsp->TOP));
        Vdffrnq_iso_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vdffrnq_iso_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdffrnq_iso_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdffrnq_iso_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vdffrnq_iso_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vdffrnq_iso_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdffrnq_iso_tb___024root___eval_final(Vdffrnq_iso_tb___024root* vlSelf);

VL_ATTR_COLD void Vdffrnq_iso_tb::final() {
    Vdffrnq_iso_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdffrnq_iso_tb::hierName() const { return vlSymsp->name(); }
const char* Vdffrnq_iso_tb::modelName() const { return "Vdffrnq_iso_tb"; }
unsigned Vdffrnq_iso_tb::threads() const { return 1; }
void Vdffrnq_iso_tb::prepareClone() const { contextp()->prepareClone(); }
void Vdffrnq_iso_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vdffrnq_iso_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vdffrnq_iso_tb___024root__trace_decl_types(VerilatedFst* tracep);

void Vdffrnq_iso_tb___024root__trace_init_top(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedFst* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdffrnq_iso_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdffrnq_iso_tb___024root*>(voidSelf);
    Vdffrnq_iso_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vdffrnq_iso_tb___024root__trace_decl_types(tracep);
    Vdffrnq_iso_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vdffrnq_iso_tb___024root__trace_register(Vdffrnq_iso_tb___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vdffrnq_iso_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedFstC* const stfp = dynamic_cast<VerilatedFstC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vdffrnq_iso_tb::trace()' called on non-VerilatedFstC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 4);
    Vdffrnq_iso_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
