// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tlul_sram_if_macro.h for the primary calling header

#include "Vtb_tlul_sram_if_macro__pch.h"

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_static__TOP(Vtb_tlul_sram_if_macro___024root* vlSelf);
void Vtb_tlul_sram_if_macro___024root___timing_ready(Vtb_tlul_sram_if_macro___024root* vlSelf);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_static(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_static\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_tlul_sram_if_macro___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__VactTriggered[0U] = (2ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (4ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000010ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000020ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000040ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000080ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000100ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000800000ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000001000000ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000008000000000ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0040000000000000ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[1U] = (0x0000000000000020ULL 
                                     | vlSelfRef.__VactTriggered[1U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__clk__0 = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP____VdfgRegularize_he50b618e_0_0__0 
        = vlSelfRef.__VdfgRegularize_he50b618e_0_0;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__addr__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__req__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__wdata__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__we__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__rst_n__0 = 0U;
    vlSelfRef.__Vtrigprevexpr_h81d9a602__0 = 1U;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws__0 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws;
    Vtb_tlul_sram_if_macro___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((1U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_static__TOP(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_static__TOP\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tlul_sram_if_macro__DOT__clk = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__rst_n = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__errors = 0U;
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_initial__TOP(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_initial__TOP\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__marked_a = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell = 1U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i)) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[(0x000000ffU 
                                                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i)] = 0U;
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i 
            = ((IData)(1U) + vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i);
    }
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__marked_a = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell = 1U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i)) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[(0x000000ffU 
                                                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i)] = 0U;
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i 
            = ((IData)(1U) + vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i);
    }
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__marked_a = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell = 1U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i)) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[(0x000000ffU 
                                                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i)] = 0U;
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i 
            = ((IData)(1U) + vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i);
    }
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__marked_a = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_dly = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell = 1U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i)) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[(0x000000ffU 
                                                                                & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i)] = 0U;
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i 
            = ((IData)(1U) + vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i);
    }
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_final(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_final\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_tlul_sram_if_macro___024root___eval_phase__stl(Vtb_tlul_sram_if_macro___024root* vlSelf);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_settle(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_settle\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_tlul_sram_if_macro___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb_tlul_sram_if_macro.sv", 3, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_tlul_sram_if_macro___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_triggers_vec__stl(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_triggers_vec__stl\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_tlul_sram_if_macro___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_tlul_sram_if_macro___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_tlul_sram_if_macro___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___stl_sequent__TOP__0(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___stl_sequent__TOP__0\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__clk;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__clk;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__clk;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly 
        = vlSelfRef.tb_tlul_sram_if_macro__DOT__clk;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_ck_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh) 
                       | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_ck_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh) 
                       | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_ck_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh) 
                       | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_ck_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh) 
                       | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_st_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_hd_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_st_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_hd_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_st_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_hd_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_st_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_hd_viol 
        = (1U & (~ ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch) 
                    | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah) 
                       | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh) 
                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh) 
                             | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih)))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0 
        = (1U & ((~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)) 
                 & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we 
        = ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
            >> 0x00000011U) & ((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                             >> 0x0000000eU))) 
                               | (1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 0x0000000eU)))));
    if ((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr 
            = (0x0000ffffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                              >> 3U));
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
            = ((((0x0000ff00U & ((- (IData)((1U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U]))) 
                                 << 8U)) | (0x000000ffU 
                                            & (- (IData)(
                                                         (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                          >> 0x0000001fU))))) 
                << 0x00000010U) | ((0x0000ff00U & (
                                                   (- (IData)(
                                                              (1U 
                                                               & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                                  >> 0x0000001eU)))) 
                                                   << 8U)) 
                                   | (0x000000ffU & 
                                      (- (IData)((1U 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                     >> 0x0000001dU)))))));
    } else {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr = 0U;
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o = 0U;
    }
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)
            ? (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__storage)
            : 0U);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)
            ? (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__storage)
            : 0U);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err 
        = (([&]() {
                vlSelfRef.__Vfunc_mubi4_test_true_strict__9__val 
                    = (0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 0x0000000fU));
                vlSelfRef.__Vfunc_mubi4_test_true_strict__9__Vfuncout 
                    = (6U == (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__9__val));
            }(), (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__9__Vfuncout)) 
           & ((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                            >> 0x0000000eU))) | (1U 
                                                 == 
                                                 (7U 
                                                  & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                     >> 0x0000000eU)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__instr_error 
        = (([&]() {
                vlSelfRef.__Vfunc_mubi4_test_invalid__5__val 
                    = (0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 0x0000000fU));
                vlSelfRef.__Vfunc_mubi4_test_invalid__5__Vfuncout 
                    = (1U & (~ ((6U == (IData)(vlSelfRef.__Vfunc_mubi4_test_invalid__5__val)) 
                                | (9U == (IData)(vlSelfRef.__Vfunc_mubi4_test_invalid__5__val)))));
            }(), (IData)(vlSelfRef.__Vfunc_mubi4_test_invalid__5__Vfuncout)) 
           | ([&]() {
                vlSelfRef.__Vfunc_mubi4_test_true_strict__6__val 
                    = (0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 0x0000000fU));
                vlSelfRef.__Vfunc_mubi4_test_true_strict__6__Vfuncout 
                    = (6U == (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__6__val));
            }(), (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__6__Vfuncout)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk = 0U;
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk = 0U;
    if ((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])) {
        if ((0U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                          >> 9U)))) {
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk = 1U;
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk 
                = (1U & (~ (0U != (0x0000000fU & ((
                                                   (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                    << 3U) 
                                                   | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                      >> 0x0000001dU)) 
                                                  & (~ 
                                                     ((IData)(1U) 
                                                      << 
                                                      (3U 
                                                       & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                          >> 1U)))))))));
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk 
                = (0U != (0x0000000fU & (((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                           << 3U) | 
                                          (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                           >> 0x0000001dU)) 
                                         & ((IData)(1U) 
                                            << (3U 
                                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                   >> 1U))))));
        } else if ((1U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                 >> 9U)))) {
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk 
                = (1U & (~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                            >> 1U)));
            if ((4U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U])) {
                vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk 
                    = (1U & (~ (0U != (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                             >> 0x0000001dU)))));
                vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk 
                    = (3U == (3U & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                     << 1U) | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                               >> 0x0000001fU))));
            } else {
                vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk 
                    = (1U & (~ (0U != (0x0cU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                 << 3U) 
                                                | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                   >> 0x0000001dU))))));
                vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk 
                    = (3U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                    >> 0x0000001dU)));
            }
        } else if ((2U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                 >> 9U)))) {
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk 
                = (1U & (~ (0U != (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                         >> 1U)))));
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk = 1U;
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk 
                = (0x0000000fU == (0x0000000fU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                                                   << 3U) 
                                                  | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                     >> 0x0000001dU))));
        } else {
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk = 0U;
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk = 0U;
            vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk = 0U;
        }
        if ((1U & (~ VL_ONEHOT_I((((2U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                 >> 9U))) 
                                   << 2U) | (((1U == 
                                               (3U 
                                                & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                   >> 9U))) 
                                              << 1U) 
                                             | (0U 
                                                == 
                                                (3U 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                    >> 9U))))))))) {
            if ((0U != (((2U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                       >> 9U))) << 2U) 
                        | (((1U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                          >> 9U))) 
                            << 1U) | (0U == (3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                   >> 9U))))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tlul_err.sv:62: Assertion failed in %Ntb_tlul_sram_if_macro.dut.u_adapt.u_err: unique case, but multiple matches found for '32'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1),
                                 -12,vlSymsp->name(),
                                 32,(3U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                           >> 9U)));
                    VL_STOP_MT("/foss/designs/opentitan_minrot_nix/build/xinting_pd_tlul_sram_if_macro_0.1/lint-verilator/src/lowrisc_tlul_common_0.1/rtl/tlul_err.sv", 62, "");
                }
            }
        }
    }
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i 
        = ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
            >> 0x00000011U) & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword 
        = (((((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg) 
              << 0x00000018U) | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg) 
                                 << 0x00000010U)) | 
            (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg) 
              << 8U) | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg))) 
           & ((((0x0000ff00U & ((- (IData)((1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                  >> 4U)))) 
                                << 8U)) | (0x000000ffU 
                                           & (- (IData)(
                                                        (1U 
                                                         & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                            >> 3U)))))) 
               << 0x00000010U) | ((0x0000ff00U & ((- (IData)(
                                                             (1U 
                                                              & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                                 >> 2U)))) 
                                                  << 8U)) 
                                  | (0x000000ffU & 
                                     (- (IData)((1U 
                                                 & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o) 
                                                    >> 1U))))))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data 
        = (([&]() {
                vlSelfRef.__Vfunc_mubi4_test_true_strict__8__val 
                    = (0x0000000fU & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                      >> 0x0000000aU));
                vlSelfRef.__Vfunc_mubi4_test_true_strict__8__Vfuncout 
                    = (6U == (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__8__val));
            }(), (IData)(vlSelfRef.__Vfunc_mubi4_test_true_strict__8__Vfuncout))
            ? 0U : 0xffffffffU);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata 
        = ((0x00020000U & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U])
            ? (((((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[2U] 
                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we))
                   ? (0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                     >> 0x00000015U))
                   : 0U) << 0x00000018U) | ((((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                               >> 0x0000001fU) 
                                              & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we))
                                              ? (0x000000ffU 
                                                 & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                    >> 0x0000000dU))
                                              : 0U) 
                                            << 0x00000010U)) 
               | (((((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                      >> 0x0000001eU) & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we))
                     ? (0x000000ffU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                       >> 5U)) : 0U) 
                   << 8U) | (((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                               >> 0x0000001dU) & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we))
                              ? (0x000000ffU & ((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[1U] 
                                                 << 3U) 
                                                | (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                   >> 0x0000001dU)))
                              : 0U))) : 0U);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q) 
           | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det 
        = (1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__instr_error) 
                 | ((~ (((0U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                       >> 0x0000000eU))) 
                         | ((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                          >> 0x0000000eU))) 
                            | (4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                            >> 0x0000000eU))))) 
                        & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk) 
                           & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk) 
                              & ((4U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                               >> 0x0000000eU))) 
                                 | ((1U == (7U & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                                                  >> 0x0000000eU))) 
                                    | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk))))))) 
                    | ((~ ((6U == (0x0000000fU & (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                                  >> 0x0000000fU))) 
                           | (9U == (0x0000000fU & 
                                     (vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U] 
                                      >> 0x0000000fU))))) 
                       | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err)))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o)
            ? ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q)
                ? vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage
                : ((QData)((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword)) 
                   << 8U)) : 0ULL);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
           & (IData)(((0x8000U != (0xc000U & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))) 
                      | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o))));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cd5 
        = (0x000000ffU & (((~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o) 
                           & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem
                           [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                          | (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                             & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cd5 
        = (0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                               >> 8U)) & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem
                           [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                          | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                             >> 8U)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cd5 
        = (0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                               >> 0x00000010U)) & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem
                           [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                          | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                             >> 0x00000010U)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cd5 
        = (0x000000ffU & (((~ (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                               >> 0x00000018U)) & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem
                           [(0x000000ffU & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__addr))]) 
                          | ((vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                              & vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__wdata) 
                             >> 0x00000018U)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req 
        = (IData)((((vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[3U] 
                     >> 0x00000011U) & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det))) 
                   & (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q))));
    vlSelfRef.__VdfgRegularize_he50b618e_0_1 = ((((0x00004000U 
                                                   & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                   ? 0x0000002aU
                                                   : 
                                                  (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
                                                    & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o) 
                                                       & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                          >> 0x0000000fU)))
                                                    ? 
                                                   (0x0000007fU 
                                                    & (IData)(
                                                              (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o 
                                                               >> 1U)))
                                                    : 0x0000002aU)) 
                                                 << 2U) 
                                                | (((((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q) 
                                                      & ((0x00008000U 
                                                          & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o))
                                                          ? 
                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o) 
                                                          | ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                             >> 0x0000000eU))
                                                          : 
                                                         ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o) 
                                                          >> 0x0000000eU))) 
                                                     & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid)) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid) 
           & vlSelfRef.tb_tlul_sram_if_macro__DOT__tl_h2d[0U]);
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_d 
        = (1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                  ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i))
                  : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i 
        = ((~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we)) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_d 
        = (1U & ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q)
                  ? (~ (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i))
                  : (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i)));
    if (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
         & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_dly))) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell = 1U;
    }
    if (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
         & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_dly))) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell = 1U;
    }
    if (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
         & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_dly))) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell = 1U;
    }
    if (((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
         & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_dly))) {
        vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell = 1U;
    }
    vlSelfRef.__VdfgRegularize_he50b618e_0_0 = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
                                                & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__we));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__req) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag) 
           & ((~ (0x000000ffU == (0x000000ffU & (~ vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o)))) 
              & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag) 
           & ((~ (0x000000ffU == (0x000000ffU & (~ 
                                                 (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 8U))))) 
              & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag) 
           & ((~ (0x000000ffU == (0x000000ffU & (~ 
                                                 (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 0x00000010U))))) 
              & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
           & (IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag));
    vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag 
        = ((IData)(vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag) 
           & ((~ (0x000000ffU == (0x000000ffU & (~ 
                                                 (vlSelfRef.tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o 
                                                  >> 0x00000018U))))) 
              & (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)));
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root____Vm_traceActivitySetAll(Vtb_tlul_sram_if_macro___024root* vlSelf);

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___eval_stl(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_stl\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_tlul_sram_if_macro___024root___stl_sequent__TOP__0(vlSelf);
        Vtb_tlul_sram_if_macro___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_tlul_sram_if_macro___024root___eval_phase__stl(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___eval_phase__stl\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_tlul_sram_if_macro___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_tlul_sram_if_macro___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_tlul_sram_if_macro___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_tlul_sram_if_macro___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_tlul_sram_if_macro___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_tlul_sram_if_macro___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_tlul_sram_if_macro.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( __VdfgRegularize_he50b618e_0_0)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( tb_tlul_sram_if_macro.dut.addr)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_tlul_sram_if_macro.dut.req)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( tb_tlul_sram_if_macro.dut.rvalid)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( tb_tlul_sram_if_macro.dut.wdata)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @( tb_tlul_sram_if_macro.dut.we)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @( tb_tlul_sram_if_macro.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 8 is active: @( 1'h1)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 9 is active: @(negedge tb_tlul_sram_if_macro.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 10 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.cen_not_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 11 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.cen_fell)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 12 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 13 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.cen_not_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 14 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.cen_fell)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 15 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000010U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 16 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.cen_not_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000011U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 17 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.cen_fell)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000012U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 18 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000013U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 19 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.cen_not_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000014U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 20 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.cen_fell)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000015U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 21 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000016U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 22 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000017U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 23 is active: @( tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.cen_flag)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000018U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 24 is active: @( tb_tlul_sram_if_macro.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000019U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 25 is active: @(negedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 26 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_Tckh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 27 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_Tckl)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 28 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_Tcyc)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 29 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tah)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 30 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tas)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 31 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tch)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000020U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 32 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tcs)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000021U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 33 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tdh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000022U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 34 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tds)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000023U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 35 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_twh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000024U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 36 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_twih)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000025U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 37 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_twis)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000026U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 38 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[0].u_macro.ntf_tws)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000027U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 39 is active: @( tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.cen_flag)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000028U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 40 is active: @(negedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000029U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 41 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_Tckh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 42 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_Tckl)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 43 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_Tcyc)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 44 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tah)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 45 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tas)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 46 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tch)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000002fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 47 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tcs)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000030U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 48 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tdh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000031U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 49 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tds)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000032U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 50 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_twh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000033U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 51 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_twih)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000034U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 52 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_twis)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000035U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 53 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[1].u_macro.ntf_tws)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000036U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 54 is active: @( tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.cen_flag)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000037U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 55 is active: @(negedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000038U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 56 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_Tckh)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000039U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 57 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_Tckl)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 58 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_Tcyc)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 59 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tah)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 60 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tas)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 61 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tch)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 62 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tcs)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000003fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 63 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tdh)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tds)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 65 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_twh)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 66 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_twih)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 67 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_twis)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 68 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[2].u_macro.ntf_tws)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 69 is active: @( tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.cen_flag)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 70 is active: @(negedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.clk_dly)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 71 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_Tckh)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 72 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_Tckl)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 73 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_Tcyc)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 74 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tah)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 75 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tas)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 76 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tch)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 77 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tcs)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 78 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tdh)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x0000000fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 79 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tds)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x00000010U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 80 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_twh)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x00000011U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 81 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_twih)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x00000012U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 82 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_twis)\n");
    }
    if ((1U & (IData)((triggers[1U] >> 0x00000013U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 83 is active: @(posedge tb_tlul_sram_if_macro.dut.u_mem.gen_byte[3].u_macro.ntf_tws)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root____Vm_traceActivitySetAll(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root____Vm_traceActivitySetAll\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.__Vm_traceActivity[3U] = 1U;
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.__Vm_traceActivity[5U] = 1U;
    vlSelfRef.__Vm_traceActivity[6U] = 1U;
    vlSelfRef.__Vm_traceActivity[7U] = 1U;
    vlSelfRef.__Vm_traceActivity[8U] = 1U;
    vlSelfRef.__Vm_traceActivity[9U] = 1U;
    vlSelfRef.__Vm_traceActivity[10U] = 1U;
}

VL_ATTR_COLD void Vtb_tlul_sram_if_macro___024root___ctor_var_reset(Vtb_tlul_sram_if_macro___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tlul_sram_if_macro___024root___ctor_var_reset\n"); );
    Vtb_tlul_sram_if_macro__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(114, vlSelf->tb_tlul_sram_if_macro__DOT__tl_h2d, __VscopeHash, 14277422096753217499ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__rd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9819924225331190380ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__rerr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5700967741148385043ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5885959535202798954ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11333116369334772202ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8987339336651146420ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__addr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18336020904660924878ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10688668378009350676ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15493337514563940421ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__wmask_o = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4710825340787237095ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_det = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9055217587154661986ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__instr_error = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13991392175022225282ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__intg_error_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9762207355623086811ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__d_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15304804987587263842ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__error_blanking_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6642729933264740545ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__missed_err_gnt_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4291670266302611735ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__rdata_tlword = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 929906879579118600ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT____VdfgRegularize_h506ee29d_0_0 = 0;
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__instr_wr_err = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8552044283333532684ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__addr_sz_chk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16710385537853654914ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__mask_chk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17982529683472753731ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_err__DOT__fulldata_chk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3482527365842481458ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__wvalid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4357654564823026063ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rready_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3069259328527381739ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__rdata_o = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3222954769109124530ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1889902388651255947ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__full_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 590071867524072858ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_reqfifo__DOT__gen_singleton_fifo__DOT__storage = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4184128122983147620ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__wvalid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6908669698520788595ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__rdata_o = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9144561584189316004ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9454189576035073380ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__full_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5347051934664342884ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_sramreqfifo__DOT__gen_singleton_fifo__DOT__storage = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15574912368477107987ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__wvalid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3112580560080620982ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rvalid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7320728853225950689ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__rdata_o = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 9235951434957060990ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__full_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2165949114759937857ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_adapt__DOT__u_rspfifo__DOT__gen_singleton_fifo__DOT__storage = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 7388445814356838878ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8538565268480908910ull);
    }
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__qo_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1173284409169297377ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10467172496745172839ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5183518849276156385ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7864638078193933117ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14074469152854688179ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9380673845817661082ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2738535329910561983ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6753930405153006369ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1928012464369550281ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12311916852682454399ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15694466881585127549ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9264951368248870349ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2421092045672738642ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15791714138711410200ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17811810063195567154ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4529294174411808580ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15729091674711907422ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_st_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6955350186848460927ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_hd_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 199335450109900019ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__no_ck_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13607009603783666027ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4404395083202468396ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__write_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 66712103835316207ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__read_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 513375747082874572ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18187820602760163023ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 224382205915206608ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8417615359218467268ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cd5 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17934845018063645198ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cdx = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17357361496952622621ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__marked_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4934232108172426715ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4550693520577536717ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17986618989003519188ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16798611906226121609ull);
    }
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__qo_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2718698720811371052ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7705146789854302730ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8601872054696381628ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 195931312094419659ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7309717712690590145ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13516105426647316203ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8483969060179115326ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 963787926975656871ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18077969921539420062ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11523599227231486801ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9597815641925371085ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4496626489812092859ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9421350931377411958ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6798401279057003807ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18323101957634381883ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6648482861603934146ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14418653279631997127ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_st_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14584973054198798990ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_hd_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7536597828871107468ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__no_ck_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8408215456787786653ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8724655793240740461ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__write_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16966607864997652628ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__read_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10079625187184378865ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3538800183402920240ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2112494640764470594ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4606698230332365559ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cd5 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15274693582197009718ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cdx = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9549476711617262228ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__marked_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1515387001847765088ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17932926047949238855ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18213081068093902653ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8888229065464034741ull);
    }
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__qo_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3672850789681838349ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4067533832496523989ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3482821928056138480ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15719095247998062293ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10662517126787217538ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5948695585288895858ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2741952248870183545ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16681771189818641919ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12488607666582257275ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5957206936667225746ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8253749201470381245ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13169839685945292840ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8969873677299569347ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5021895798753392930ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4069265143088654546ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14619498147565062357ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2625604016233334541ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_st_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2271282698346482025ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_hd_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4649707927973004964ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__no_ck_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15627134253858784973ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4414772979137140795ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__write_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4673749801849923286ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__read_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4349247651790601074ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13262677201403459853ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4397646795761194710ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4246633679206192276ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cd5 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8850956029688098157ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cdx = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14001472396860939856ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__marked_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6554803875216218852ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6801346680393794213ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4034192105279207828ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10705635342926395756ull);
    }
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__qo_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5405425830150669485ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 244765352564222009ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11063394540813169233ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13906635756644648800ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17063595220187454764ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1083648014918056785ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12290767995677067610ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8164594541922896879ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 847847094501758625ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2645954967144610719ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18331462808093369768ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10044189408492126970ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11970145634239353404ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14208644115950459881ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15308018354254638303ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5249309103024261376ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11220909862816837185ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_st_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4671041484531659163ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_hd_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1110299467656704615ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__no_ck_viol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7280121672135305614ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13295149550973695939ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__write_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8906722648499895588ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__read_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10759069407748870893ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11420949999190266255ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8992864405405040960ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15495407079709689040ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cd5 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5619341368702881430ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cdx = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4133428462908136638ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__marked_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17387232126199268005ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4947645505360807565ull);
    vlSelf->tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag_dly = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13671284306653078904ull);
    vlSelf->__VdfgRegularize_he50b618e_0_0 = 0;
    vlSelf->__VdfgRegularize_he50b618e_0_1 = 0;
    vlSelf->__Vfunc_mubi4_test_invalid__5__Vfuncout = 0;
    vlSelf->__Vfunc_mubi4_test_invalid__5__val = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__6__Vfuncout = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__6__val = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__8__Vfuncout = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__8__val = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__9__Vfuncout = 0;
    vlSelf->__Vfunc_mubi4_test_true_strict__9__val = 0;
    vlSelf->__Vintraval_h57c051a3__0 = 0;
    vlSelf->__Vintraval_ha447b470__0 = 0;
    vlSelf->__Vintraval_h7ee04a24__0 = 0;
    vlSelf->__Vintraval_hc1e52bc4__0 = 0;
    vlSelf->__Vintraval_hccd7d94c__0 = 0;
    vlSelf->__Vintraval_h1f2c754a__0 = 0;
    vlSelf->__Vintraval_hd1b02d39__0 = 0;
    vlSelf->__Vintraval_h7e6bc218__0 = 0;
    vlSelf->__Vintraval_hef677ca9__0 = 0;
    vlSelf->__Vintraval_h0ec179f4__0 = 0;
    vlSelf->__Vintraval_hdf1a9ba7__0 = 0;
    vlSelf->__Vintraval_ha0148163__0 = 0;
    vlSelf->__Vintraval_hf20d2f19__0 = 0;
    vlSelf->__Vintraval_h78c23df8__0 = 0;
    vlSelf->__Vintraval_hc14dc0cd__0 = 0;
    vlSelf->__Vintraval_hcd5f43f9__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP____VdfgRegularize_he50b618e_0_0__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__addr__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__req__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__rvalid__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__wdata__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__we__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr_h81d9a602__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_not_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_fell__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__clk_dly__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_not_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_fell__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__clk_dly__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_not_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_fell__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__clk_dly__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_not_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_fell__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__clk_dly__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__cen_flag__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tckl__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_Tcyc__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tah__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tas__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tch__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tcs__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tdh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tds__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twih__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_twis__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__0__KET____DOT__u_macro__DOT__ntf_tws__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__cen_flag__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tckl__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_Tcyc__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tah__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tas__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tch__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tcs__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tdh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tds__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twih__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_twis__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__1__KET____DOT__u_macro__DOT__ntf_tws__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__cen_flag__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tckl__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_Tcyc__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tah__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tas__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tch__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tcs__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tdh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tds__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twih__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_twis__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__2__KET____DOT__u_macro__DOT__ntf_tws__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__cen_flag__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tckl__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_Tcyc__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tah__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tas__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tch__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tcs__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tdh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tds__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twh__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twih__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_twis__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tlul_sram_if_macro__DOT__dut__DOT__u_mem__DOT__gen_byte__BRA__3__KET____DOT__u_macro__DOT__ntf_tws__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 11; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
