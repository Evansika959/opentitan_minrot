// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtb_tlul_sram_if_macro__Syms.h"


void Vtb_tlul_sram_if_macro___024root__trace_chg_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtb_tlul_sram_if_macro___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_chg_0\n"); );
    // Body
    Vtb_tlul_sram_if_macro___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_tlul_sram_if_macro___024root*>(voidSelf);
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtb_tlul_sram_if_macro___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtb_tlul_sram_if_macro___024root__trace_chg_0_sub_0(Vtb_tlul_sram_if_macro___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_chg_0_sub_0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i),32);
        bufp->chgIData(oldp+1,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i),32);
        bufp->chgIData(oldp+2,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i),32);
        bufp->chgIData(oldp+3,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i),32);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+4,((1U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                    >> 0x00000011U))));
        bufp->chgCData(oldp+5,((7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                      >> 0x0000000eU))),3);
        bufp->chgCData(oldp+6,((7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                      >> 0x0000000bU))),3);
        bufp->chgCData(oldp+7,((3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                      >> 9U))),2);
        bufp->chgCData(oldp+8,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 1U))),8);
        bufp->chgIData(oldp+9,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                 << 0x0000001fU) | 
                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                 >> 1U))),32);
        bufp->chgCData(oldp+10,((0x0000000fU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                 << 3U) 
                                                | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                   >> 0x0000001dU)))),4);
        bufp->chgIData(oldp+11,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                  << 3U) | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                            >> 0x0000001dU))),32);
        bufp->chgSData(oldp+12,((0x000003ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 0x00000013U))),10);
        bufp->chgCData(oldp+13,((0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 0x0000000fU))),4);
        bufp->chgCData(oldp+14,((0x0000007fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 8U))),7);
        bufp->chgCData(oldp+15,((0x0000007fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 1U))),7);
        bufp->chgBit(oldp+16,((1U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U])));
        bufp->chgIData(oldp+17,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rd),32);
        bufp->chgBit(oldp+18,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rerr));
        bufp->chgCData(oldp+19,((0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                >> 0x0000000fU))),4);
        bufp->chgSData(oldp+20,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                                  ? (0x000003ffU & 
                                     (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 0x00000013U))
                                  : 0U)),10);
        bufp->chgBit(oldp+21,((1U & VL_REDXOR_32(((
                                                   (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                    ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U]) 
                                                   ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U]) 
                                                  ^ vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])))));
        bufp->chgBit(oldp+22,((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                            >> 0x0000000eU)))));
        bufp->chgSData(oldp+23,((0x00000fffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                >> 3U))),12);
        bufp->chgCData(oldp+24,((0x0000001eU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                 << 4U) 
                                                | (0x0000000eU 
                                                   & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                      >> 0x0000001cU))))),5);
        bufp->chgCData(oldp+25,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                                  ? 0x7fU : 0U)),7);
        bufp->chgCData(oldp+26,(((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
                                  ? (0x0000007fU & 
                                     (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 1U)) : 0U)),7);
        bufp->chgBit(oldp+27,((1U & VL_REDXOR_32((0x00000fffU 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                     >> 3U))))));
        bufp->chgBit(oldp+28,((IData)(((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                        >> 0x00000011U) 
                                       & (0U != (0x0000007fU 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                    >> 1U)))))));
        bufp->chgBit(oldp+29,(((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                             >> 0x0000000eU))) 
                               | ((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                >> 0x0000000eU))) 
                                  | (4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                  >> 0x0000000eU)))))));
        bufp->chgBit(oldp+30,((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                            >> 0x0000000eU)))));
        bufp->chgBit(oldp+31,((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                            >> 0x0000000eU)))));
        bufp->chgBit(oldp+32,((1U & (~ ((6U == (0x0000000fU 
                                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                   >> 0x0000000fU))) 
                                        | (9U == (0x0000000fU 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                     >> 0x0000000fU))))))));
        bufp->chgCData(oldp+33,((0x0000000fU & ((IData)(1U) 
                                                << 
                                                (3U 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                    >> 1U))))),4);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgBit(oldp+34,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we));
        bufp->chgSData(oldp+35,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr),16);
        bufp->chgIData(oldp+36,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata),32);
        bufp->chgCData(oldp+37,((0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))),8);
        bufp->chgBit(oldp+38,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det));
        bufp->chgBit(oldp+39,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__instr_error));
        bufp->chgBit(oldp+40,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err));
        bufp->chgBit(oldp+41,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk));
        bufp->chgBit(oldp+42,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk));
        bufp->chgBit(oldp+43,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk));
        bufp->chgCData(oldp+44,((0x000000ffU & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata)),8);
        bufp->chgCData(oldp+45,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                                                >> 8U))),8);
        bufp->chgCData(oldp+46,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+47,((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
                                 >> 0x00000018U)),8);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[3U] 
                      | vlSelfRef.__Vm_traceActivity[6U])))) {
        bufp->chgIData(oldp+48,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o),32);
        bufp->chgCData(oldp+49,((0x000000ffU & (~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o))),8);
        bufp->chgCData(oldp+50,((0x000000ffU & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o)),8);
        bufp->chgCData(oldp+51,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata))),8);
        bufp->chgCData(oldp+52,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 8U)))),8);
        bufp->chgCData(oldp+53,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                >> 8U))),8);
        bufp->chgCData(oldp+54,((0x000000ffU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                >> 8U))),8);
        bufp->chgCData(oldp+55,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 0x00000010U)))),8);
        bufp->chgCData(oldp+56,((0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+57,((0x000000ffU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                >> 0x00000010U))),8);
        bufp->chgCData(oldp+58,((0x000000ffU & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                   >> 0x00000018U)))),8);
        bufp->chgCData(oldp+59,((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                 >> 0x00000018U)),8);
        bufp->chgCData(oldp+60,(((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                  & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                 >> 0x00000018U)),8);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[3U] 
                      | vlSelfRef.__Vm_traceActivity[8U])))) {
        bufp->chgBit(oldp+61,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req));
        bufp->chgBit(oldp+62,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i));
        bufp->chgBit(oldp+63,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i));
        bufp->chgBit(oldp+64,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i));
        bufp->chgBit(oldp+65,((IData)(((0x8000U == 
                                        (0xc000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))) 
                                       & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i)))));
        bufp->chgBit(oldp+66,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req)))));
        bufp->chgBit(oldp+67,((1U & (~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)))));
    }
    if (VL_UNLIKELY(((((vlSelfRef.__Vm_traceActivity[4U] 
                        | vlSelfRef.__Vm_traceActivity[7U]) 
                       | vlSelfRef.__Vm_traceActivity[8U]) 
                      | vlSelfRef.__Vm_traceActivity[9U])))) {
        bufp->chgCData(oldp+68,((7U & (IData)(((0x000000000000001fULL 
                                                & ((QData)((IData)(
                                                                   ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                     ? 
                                                                    (3U 
                                                                     & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                        >> 8U))
                                                                     : 0U))) 
                                                   >> 2U)) 
                                               | ((0x000000000000001fULL 
                                                   & ((QData)((IData)(
                                                                      ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                        ? 
                                                                       (0x000000ffU 
                                                                        & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                        : 0U))) 
                                                      >> 0x0000000aU)) 
                                                  | ((0x000000000000001fULL 
                                                      & ((QData)((IData)(
                                                                         (((~ 
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                             & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                           ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                           : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                         >> 0x0000002bU)) 
                                                     | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                        >> 0x0000003bU))))))),3);
        bufp->chgCData(oldp+69,((3U & (IData)(((0x000000000000007fULL 
                                                & (QData)((IData)(
                                                                  ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                    ? 
                                                                   (3U 
                                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                       >> 8U))
                                                                    : 0U)))) 
                                               | ((0x000000000000007fULL 
                                                   & ((QData)((IData)(
                                                                      ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                        ? 
                                                                       (0x000000ffU 
                                                                        & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                        : 0U))) 
                                                      >> 8U)) 
                                                  | ((0x000000000000007fULL 
                                                      & ((QData)((IData)(
                                                                         (((~ 
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                             & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                           ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                           : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                         >> 0x00000029U)) 
                                                     | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                        >> 0x00000039U))))))),2);
        bufp->chgCData(oldp+70,((0x000000ffU & (IData)(
                                                       ((0x0000000000007f00ULL 
                                                         & ((QData)((IData)(
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                              ? 
                                                                             (3U 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 8U))
                                                                              : 0U))) 
                                                            << 8U)) 
                                                        | ((0x0000000000007fffULL 
                                                            & (QData)((IData)(
                                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                                ? 
                                                                               (0x000000ffU 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                : 0U)))) 
                                                           | ((0x0000000000007fffULL 
                                                               & ((QData)((IData)(
                                                                                (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                                  >> 0x00000021U)) 
                                                              | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                                 >> 0x00000031U))))))),8);
        bufp->chgBit(oldp+71,((1U & (IData)(((0x000000000000fe00ULL 
                                              & ((QData)((IData)(
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                   ? 
                                                                  (3U 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                      >> 8U))
                                                                   : 0U))) 
                                                 << 9U)) 
                                             | ((0x000000000000fffeULL 
                                                 & ((QData)((IData)(
                                                                    ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                      ? 
                                                                     (0x000000ffU 
                                                                      & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                      : 0U))) 
                                                    << 1U)) 
                                                | ((0x000000000000ffffULL 
                                                    & ((QData)((IData)(
                                                                       (((~ 
                                                                          ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                           & ((0x00008000U 
                                                                               & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                               ? 
                                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                               | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                               : 
                                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000eU)))) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                         ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                         : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                       >> 0x00000020U)) 
                                                   | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                      >> 0x00000030U))))))));
        bufp->chgIData(oldp+72,((IData)(((0x0000fe0000000000ULL 
                                          & ((QData)((IData)(
                                                             ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                               ? 
                                                              (3U 
                                                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                  >> 8U))
                                                               : 0U))) 
                                             << 0x00000029U)) 
                                         | ((0x0000fffe00000000ULL 
                                             & ((QData)((IData)(
                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                  ? 
                                                                 (0x000000ffU 
                                                                  & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                  : 0U))) 
                                                << 0x00000021U)) 
                                            | ((0x0000ffffffffffffULL 
                                                & (QData)((IData)(
                                                                  (((~ 
                                                                     ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                      & ((0x00008000U 
                                                                          & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                          ? 
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                             >> 0x0000000eU))
                                                                          : 
                                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                          >> 0x0000000eU)))) 
                                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                          & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                             >> 0x0000000fU))))
                                                                    ? (IData)(
                                                                              (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                               >> 8U))
                                                                    : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)))) 
                                               | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                  >> 0x00000010U)))))),32);
        bufp->chgCData(oldp+73,((0x0000007fU & (IData)(
                                                       ((0x007f000000000000ULL 
                                                         & ((QData)((IData)(
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                              ? 
                                                                             (3U 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 8U))
                                                                              : 0U))) 
                                                            << 0x00000030U)) 
                                                        | ((0x007fff0000000000ULL 
                                                            & ((QData)((IData)(
                                                                               ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                                 ? 
                                                                                (0x000000ffU 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 : 0U))) 
                                                               << 0x00000028U)) 
                                                           | ((0x007fffffffffff80ULL 
                                                               & ((QData)((IData)(
                                                                                (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                                  << 7U)) 
                                                              | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                                 >> 9U))))))),7);
        bufp->chgCData(oldp+74,((0x0000007fU & (IData)(
                                                       ((0x3f80000000000000ULL 
                                                         & ((QData)((IData)(
                                                                            ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                              ? 
                                                                             (3U 
                                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 8U))
                                                                              : 0U))) 
                                                            << 0x00000037U)) 
                                                        | ((0x3fff800000000000ULL 
                                                            & ((QData)((IData)(
                                                                               ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                                 ? 
                                                                                (0x000000ffU 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 : 0U))) 
                                                               << 0x0000002fU)) 
                                                           | ((0x3fffffffffffc000ULL 
                                                               & ((QData)((IData)(
                                                                                (((~ 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                                & ((0x00008000U 
                                                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                                 ? 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                                | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                                 : 
                                                                                ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU)))) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                                 ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                                 : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                                  << 0x0000000eU)) 
                                                              | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                                 >> 2U))))))),7);
        bufp->chgBit(oldp+75,((1U & (IData)(((0x7f00000000000000ULL 
                                              & ((QData)((IData)(
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                   ? 
                                                                  (3U 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                      >> 8U))
                                                                   : 0U))) 
                                                 << 0x00000038U)) 
                                             | ((0x7fff000000000000ULL 
                                                 & ((QData)((IData)(
                                                                    ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                      ? 
                                                                     (0x000000ffU 
                                                                      & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                      : 0U))) 
                                                    << 0x00000030U)) 
                                                | ((0x7fffffffffff8000ULL 
                                                    & ((QData)((IData)(
                                                                       (((~ 
                                                                          ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                           & ((0x00008000U 
                                                                               & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                               ? 
                                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                               | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000eU))
                                                                               : 
                                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000eU)))) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                                >> 0x0000000fU))))
                                                                         ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                         : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                       << 0x0000000fU)) 
                                                   | ((QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)) 
                                                      >> 1U))))))));
        bufp->chgBit(oldp+76,((1U & (IData)((((QData)((IData)(
                                                              ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                ? 
                                                               (3U 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                   >> 8U))
                                                                : 0U))) 
                                              << 0x00000039U) 
                                             | (((QData)((IData)(
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                                   ? 
                                                                  (0x000000ffU 
                                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                   : 0U))) 
                                                 << 0x00000031U) 
                                                | (((QData)((IData)(
                                                                    (((~ 
                                                                       ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                        & ((0x00008000U 
                                                                            & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                            ? 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                            | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000eU))
                                                                            : 
                                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                            >> 0x0000000eU)))) 
                                                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                               >> 0x0000000fU))))
                                                                      ? (IData)(
                                                                                (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                                >> 8U))
                                                                      : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data))) 
                                                    << 0x00000010U) 
                                                   | (QData)((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1)))))))));
        bufp->chgBit(oldp+77,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                               & ((0x00008000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                   ? ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                         >> 0x0000000eU))
                                   : ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                      >> 0x0000000eU)))));
        bufp->chgIData(oldp+78,((((~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                      & ((0x00008000U 
                                          & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                          ? ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                             | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                >> 0x0000000eU))
                                          : ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                             >> 0x0000000eU)))) 
                                  & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                     & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                        & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                           >> 0x0000000fU))))
                                  ? (IData)((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                             >> 8U))
                                  : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)),32);
        bufp->chgCData(oldp+79,(((0x00004000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                  ? 0x0000002aU : (
                                                   ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                          >> 0x0000000fU)))
                                                    ? 
                                                   (0x0000007fU 
                                                    & (IData)(
                                                              (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                               >> 1U)))
                                                    : 0x0000002aU))),7);
        bufp->chgBit(oldp+80,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                     ^ (VL_REDXOR_32(
                                                     (((~ 
                                                        ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                         >> 0x0000000fU)) 
                                                       & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid))
                                                       ? 0U
                                                       : 1U)) 
                                        ^ (VL_REDXOR_32(
                                                        ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                          ? 
                                                         (3U 
                                                          & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                             >> 8U))
                                                          : 0U)) 
                                           ^ (VL_REDXOR_32(
                                                           ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)
                                                             ? 
                                                            (0x000000ffU 
                                                             & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                             : 0U)) 
                                              ^ (VL_REDXOR_32(
                                                              (((~ 
                                                                 ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                                  & ((0x00008000U 
                                                                      & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                                      ? 
                                                                     ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                                      | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                         >> 0x0000000eU))
                                                                      : 
                                                                     ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                      >> 0x0000000eU)))) 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                                         >> 0x0000000fU))))
                                                                ? (IData)(
                                                                          (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                                           >> 8U))
                                                                : vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data)) 
                                                 ^ 
                                                 VL_REDXOR_16(vlSelfRef.__VdfgRegularize_he50b618e_0_1)))))))));
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[4U] 
                      | vlSelfRef.__Vm_traceActivity[9U])))) {
        bufp->chgCData(oldp+81,((0x0000007fU & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                                >> 9U))),7);
        bufp->chgCData(oldp+82,((0x0000007fU & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                                >> 2U))),7);
        bufp->chgBit(oldp+83,((1U & ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1) 
                                     >> 1U))));
        bufp->chgBit(oldp+84,((1U & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_1))));
        bufp->chgIData(oldp+85,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword),32);
        bufp->chgIData(oldp+86,((IData)((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                         >> 8U))),32);
        bufp->chgCData(oldp+87,((0x0000007fU & (IData)(
                                                       (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                        >> 1U)))),7);
        bufp->chgBit(oldp+88,((1U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o))));
        bufp->chgQData(oldp+89,(((QData)((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword)) 
                                 << 8U)),40);
        bufp->chgQData(oldp+91,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o),40);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[5U] 
                      | vlSelfRef.__Vm_traceActivity[10U])))) {
        bufp->chgBit(oldp+93,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag));
        bufp->chgBit(oldp+94,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag));
        bufp->chgBit(oldp+95,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag));
        bufp->chgBit(oldp+96,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag));
        bufp->chgBit(oldp+97,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag));
        bufp->chgBit(oldp+98,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag));
        bufp->chgBit(oldp+99,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag));
        bufp->chgBit(oldp+100,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag));
        bufp->chgBit(oldp+101,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag));
        bufp->chgBit(oldp+102,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag));
        bufp->chgBit(oldp+103,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag));
        bufp->chgBit(oldp+104,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[6U]))) {
        bufp->chgSData(oldp+105,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__storage),16);
        bufp->chgQData(oldp+106,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage),40);
        bufp->chgCData(oldp+108,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__storage),5);
        bufp->chgCData(oldp+109,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cdx),8);
        bufp->chgCData(oldp+110,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cdx),8);
        bufp->chgCData(oldp+111,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cdx),8);
        bufp->chgCData(oldp+112,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cdx),8);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[7U]))) {
        bufp->chgBit(oldp+113,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid));
        bufp->chgBit(oldp+114,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid_q));
        bufp->chgBit(oldp+115,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__intg_error_q));
        bufp->chgBit(oldp+116,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
        bufp->chgBit(oldp+117,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q));
        bufp->chgBit(oldp+118,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
        bufp->chgBit(oldp+119,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i));
        bufp->chgBit(oldp+120,((1U & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q)))));
        bufp->chgBit(oldp+121,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o));
        bufp->chgBit(oldp+122,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__missed_err_gnt_q));
        bufp->chgBit(oldp+123,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q));
        bufp->chgBit(oldp+124,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[8U]))) {
        bufp->chgBit(oldp+125,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid));
        bufp->chgCData(oldp+126,((((~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                       >> 0x0000000fU)) 
                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid))
                                   ? 0U : 1U)),3);
        bufp->chgBit(oldp+127,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                      >> 0x0000000fU))));
        bufp->chgBit(oldp+128,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                      >> 0x0000000eU))));
        bufp->chgCData(oldp+129,((0x0000000fU & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                 >> 0x0000000aU))),4);
        bufp->chgCData(oldp+130,((3U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                        >> 8U))),2);
        bufp->chgCData(oldp+131,((0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))),8);
        bufp->chgCData(oldp+132,((0x0000000fU & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                 >> 1U))),4);
        bufp->chgBit(oldp+133,((1U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o))));
        bufp->chgCData(oldp+134,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o),5);
        bufp->chgIData(oldp+135,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data),32);
        bufp->chgIData(oldp+136,(((((0x0000ff00U & 
                                     ((- (IData)((1U 
                                                  & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                     >> 4U)))) 
                                      << 8U)) | (0x000000ffU 
                                                 & (- (IData)(
                                                              (1U 
                                                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                  >> 3U)))))) 
                                   << 0x00000010U) 
                                  | ((0x0000ff00U & 
                                      ((- (IData)((1U 
                                                   & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                      >> 2U)))) 
                                       << 8U)) | (0x000000ffU 
                                                  & (- (IData)(
                                                               (1U 
                                                                & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                   >> 1U)))))))),32);
        bufp->chgSData(oldp+137,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o),16);
    }
    bufp->chgBit(oldp+138,(vlSelfRef.tb_tlul_sram_if_macro__DOT__clk));
    bufp->chgBit(oldp+139,(vlSelfRef.tb_tlul_sram_if_macro__DOT__rst_n));
    bufp->chgIData(oldp+140,(vlSelfRef.tb_tlul_sram_if_macro__DOT__errors),32);
    bufp->chgIData(oldp+141,(((((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg) 
                                << 0x00000018U) | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg) 
                                                   << 0x00000010U)) 
                              | (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg) 
                                  << 8U) | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg)))),32);
    bufp->chgBit(oldp+142,((1U & (VL_REDXOR_32((0x00078000U 
                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U])) 
                                  ^ VL_REDXOR_16((0xff00U 
                                                  & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr)))))));
    bufp->chgBit(oldp+143,((1U & ((~ (((0U == (7U & 
                                               (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                >> 0x0000000eU))) 
                                       | ((1U == (7U 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                     >> 0x0000000eU))) 
                                          | (4U == 
                                             (7U & 
                                              (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 0x0000000eU))))) 
                                      & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk) 
                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk) 
                                            & ((4U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                    >> 0x0000000eU))) 
                                               | ((1U 
                                                   == 
                                                   (7U 
                                                    & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                       >> 0x0000000eU))) 
                                                  | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk))))))) 
                                  | ((~ ((6U == (0x0000000fU 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                    >> 0x0000000fU))) 
                                         | (9U == (0x0000000fU 
                                                   & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                      >> 0x0000000fU))))) 
                                     | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err))))));
    bufp->chgBit(oldp+144,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                               & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                  >> 0x0000000fU)))));
    bufp->chgBit(oldp+145,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det) 
                            & ((~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0)) 
                               & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                  >> 0x00000011U)))));
    bufp->chgBit(oldp+146,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk) 
                            & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk) 
                               & ((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                >> 0x0000000eU))) 
                                  | ((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                   >> 0x0000000eU))) 
                                     | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk)))))));
    bufp->chgSData(oldp+147,((((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                             >> 0x0000000eU))) 
                               << 0x0000000fU) | (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det) 
                                                   << 0x0000000eU) 
                                                  | ((0x00003c00U 
                                                      & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                         >> 5U)) 
                                                     | (0x000003ffU 
                                                        & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                           >> 1U)))))),16);
    bufp->chgBit(oldp+148,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                                   ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i))
                                   : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i)))));
    bufp->chgBit(oldp+149,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o)
                                   ? (~ (IData)(((0x8000U 
                                                  == 
                                                  (0xc000U 
                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))) 
                                                 & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i))))
                                   : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i)))));
    bufp->chgQData(oldp+150,(((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q)
                               ? vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage
                               : ((QData)((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword)) 
                                  << 8U))),40);
    bufp->chgBit(oldp+152,((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                                   ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i))
                                   : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i)))));
    bufp->chgCData(oldp+153,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->chgBit(oldp+154,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->chgBit(oldp+155,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->chgBit(oldp+156,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->chgBit(oldp+157,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->chgBit(oldp+158,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->chgBit(oldp+159,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->chgBit(oldp+160,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->chgBit(oldp+161,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->chgBit(oldp+162,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->chgBit(oldp+163,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->chgBit(oldp+164,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->chgBit(oldp+165,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->chgBit(oldp+166,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->chgBit(oldp+167,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->chgBit(oldp+168,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah) 
                                        | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh) 
                                           | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh) 
                                              | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->chgBit(oldp+169,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                        | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->chgBit(oldp+170,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly));
    bufp->chgBit(oldp+171,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->chgBit(oldp+172,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->chgBit(oldp+173,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_dly));
    bufp->chgBit(oldp+174,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell));
    bufp->chgBit(oldp+175,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->chgCData(oldp+176,(((~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o) 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem
                              [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->chgCData(oldp+177,((0x000000ffU & (((~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o) 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem
                                              [(0x000000ffU 
                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                             | (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata)))),8);
    bufp->chgCData(oldp+178,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->chgCData(oldp+179,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->chgCData(oldp+180,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->chgCData(oldp+181,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->chgCData(oldp+182,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->chgBit(oldp+183,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->chgCData(oldp+184,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->chgBit(oldp+185,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->chgBit(oldp+186,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->chgBit(oldp+187,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->chgBit(oldp+188,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->chgBit(oldp+189,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->chgBit(oldp+190,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->chgBit(oldp+191,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->chgBit(oldp+192,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->chgBit(oldp+193,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->chgBit(oldp+194,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->chgBit(oldp+195,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->chgBit(oldp+196,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->chgBit(oldp+197,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->chgBit(oldp+198,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->chgBit(oldp+199,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah) 
                                        | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh) 
                                           | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh) 
                                              | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->chgBit(oldp+200,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                        | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->chgBit(oldp+201,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly));
    bufp->chgBit(oldp+202,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->chgBit(oldp+203,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->chgBit(oldp+204,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_dly));
    bufp->chgBit(oldp+205,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell));
    bufp->chgBit(oldp+206,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->chgCData(oldp+207,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                  >> 8U)) & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem
                              [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->chgCData(oldp+208,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 8U)) 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem
                                              [(0x000000ffU 
                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                             | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                >> 8U)))),8);
    bufp->chgCData(oldp+209,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->chgCData(oldp+210,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->chgCData(oldp+211,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->chgCData(oldp+212,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->chgCData(oldp+213,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->chgBit(oldp+214,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->chgCData(oldp+215,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->chgBit(oldp+216,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->chgBit(oldp+217,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->chgBit(oldp+218,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->chgBit(oldp+219,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->chgBit(oldp+220,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->chgBit(oldp+221,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->chgBit(oldp+222,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->chgBit(oldp+223,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->chgBit(oldp+224,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->chgBit(oldp+225,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->chgBit(oldp+226,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->chgBit(oldp+227,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->chgBit(oldp+228,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->chgBit(oldp+229,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->chgBit(oldp+230,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah) 
                                        | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh) 
                                           | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh) 
                                              | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->chgBit(oldp+231,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                        | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->chgBit(oldp+232,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly));
    bufp->chgBit(oldp+233,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->chgBit(oldp+234,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->chgBit(oldp+235,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_dly));
    bufp->chgBit(oldp+236,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell));
    bufp->chgBit(oldp+237,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->chgCData(oldp+238,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                  >> 0x00000010U)) 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem
                              [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->chgCData(oldp+239,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 0x00000010U)) 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem
                                              [(0x000000ffU 
                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                             | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                >> 0x00000010U)))),8);
    bufp->chgCData(oldp+240,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->chgCData(oldp+241,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->chgCData(oldp+242,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->chgCData(oldp+243,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->chgCData(oldp+244,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->chgBit(oldp+245,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag_dly));
    bufp->chgCData(oldp+246,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg),8);
    bufp->chgBit(oldp+247,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc));
    bufp->chgBit(oldp+248,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh));
    bufp->chgBit(oldp+249,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl));
    bufp->chgBit(oldp+250,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs));
    bufp->chgBit(oldp+251,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas));
    bufp->chgBit(oldp+252,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds));
    bufp->chgBit(oldp+253,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws));
    bufp->chgBit(oldp+254,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis));
    bufp->chgBit(oldp+255,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch));
    bufp->chgBit(oldp+256,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah));
    bufp->chgBit(oldp+257,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh));
    bufp->chgBit(oldp+258,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh));
    bufp->chgBit(oldp+259,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih));
    bufp->chgBit(oldp+260,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_st_viol));
    bufp->chgBit(oldp+261,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah) 
                                        | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh) 
                                           | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh) 
                                              | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih)))))))));
    bufp->chgBit(oldp+262,((1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                                     | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh) 
                                        | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl)))))));
    bufp->chgBit(oldp+263,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly));
    bufp->chgBit(oldp+264,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag_dly));
    bufp->chgBit(oldp+265,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag_dly));
    bufp->chgBit(oldp+266,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_dly));
    bufp->chgBit(oldp+267,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell));
    bufp->chgBit(oldp+268,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst));
    bufp->chgCData(oldp+269,(((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                  >> 0x00000018U)) 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem
                              [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))])),8);
    bufp->chgCData(oldp+270,((0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 0x00000018U)) 
                                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem
                                              [(0x000000ffU 
                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                                             | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                 & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                                                >> 0x00000018U)))),8);
    bufp->chgCData(oldp+271,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__marked_a),8);
    bufp->chgCData(oldp+272,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[0U]),8);
    bufp->chgCData(oldp+273,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[1U]),8);
    bufp->chgCData(oldp+274,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[2U]),8);
    bufp->chgCData(oldp+275,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[3U]),8);
    bufp->chgBit(oldp+276,(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag_dly));
}

void Vtb_tlul_sram_if_macro___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root__trace_cleanup\n"); );
    // Body
    Vtb_tlul_sram_if_macro___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_tlul_sram_if_macro___024root*>(voidSelf);
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[5U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[6U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[7U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[8U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[9U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[10U] = 0U;
}
