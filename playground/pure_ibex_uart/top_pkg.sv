// Simple TL-UL parameter package for the pure ibex + UART playground
package top_pkg;
  parameter int TL_AW  = 32;
  parameter int TL_DW  = 32;
  parameter int TL_AIW = 8;
  parameter int TL_DIW = 1;
  parameter int TL_AUW = 23;
  parameter int TL_DUW = 4;
  parameter int TL_DBW = TL_DW/8;
  parameter int TL_SZW = 3; // log2(bytes)
endpackage
