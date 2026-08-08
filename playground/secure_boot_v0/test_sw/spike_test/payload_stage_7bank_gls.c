// payload_stage_7bank_gls.c -- the verified BL0 payload for the top_pd_7bank
// real secure-boot + PUF demo. Forked from payload_stage.c (same role:
// ROM copies these bytes from DMEM into ESRAM at runtime after verifying
// the signature, then jumps in). Two changes: ends with '!' (the sentinel
// character top_pd_7bank_secboot_gls_tb.sv's UART decoder already exits
// on), and the halt loop uses a volatile asm so the compiler can't prove
// it has no side effects and elide it entirely -- exactly the bug found
// and fixed in the timing_probe.c measurement earlier this session.
#include "./utils/uart.h"

void payload_main(void) {
  const char *msg = "Payload: verified boot OK!\r\n";
  while (*msg) uart_putc(*msg++);
  while (1) { __asm__ volatile(""); }
}
