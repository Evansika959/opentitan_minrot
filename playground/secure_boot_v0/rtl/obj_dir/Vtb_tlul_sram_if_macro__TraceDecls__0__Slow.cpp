// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing declarations

#include "verilated_fst_c.h"


void Vtb_tlul_sram_if_macro___024root__traceDeclTypesSub0(VerilatedFst* tracep) {
    {
        const char* __VenumItemNames[]
        = {"PutFullData", "PutPartialData", "Get"};
        const char* __VenumItemValues[]
        = {"0", "1", "100"};
        tracep->declDTypeEnum(1, "tlul_pkg::tl_a_op_e", 3, 3, __VenumItemNames, __VenumItemValues);
    }
    {
        const char* __VenumItemNames[]
        = {"MuBi4True", "MuBi4False"};
        const char* __VenumItemValues[]
        = {"110", "1001"};
        tracep->declDTypeEnum(2, "prim_mubi_pkg::mubi4_t", 2, 4, __VenumItemNames, __VenumItemValues);
    }
    {
        const char* __VenumItemNames[]
        = {"AccessAck", "AccessAckData"};
        const char* __VenumItemValues[]
        = {"0", "1"};
        tracep->declDTypeEnum(3, "tlul_pkg::tl_d_op_e", 2, 3, __VenumItemNames, __VenumItemValues);
    }
}

void Vtb_tlul_sram_if_macro___024root__trace_decl_types(VerilatedFst* tracep) {
    Vtb_tlul_sram_if_macro___024root__traceDeclTypesSub0(tracep);
}
