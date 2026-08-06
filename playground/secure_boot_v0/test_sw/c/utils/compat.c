// Minimal compiler-rt replacements for freestanding build
//
// __lshrdi3 is the libgcc runtime-helper symbol name the compiler emits a
// call to whenever it needs to right-shift a 64-bit value on a 32-bit target
// (RV32 has no native 64-bit shift). Implementing it with a plain 64-bit
// shift (`a >> b`) is a footgun: depending on optimization level, the
// compiler can lower that shift back into a call to __lshrdi3 itself,
// producing infinite recursion that runs the stack pointer through zero and
// off into invalid memory. Split into 32-bit halves instead (what real
// libgcc does), so no 64-bit shift ever appears in this function's body.
unsigned long long __lshrdi3(unsigned long long a, int b) {
  union { unsigned long long ull; struct { unsigned int lo, hi; } p; } u;
  u.ull = a;
  unsigned int hi = u.p.hi, lo = u.p.lo;
  if (b <= 0) return a;
  if (b >= 32) { u.p.hi = 0; u.p.lo = hi >> (b - 32); }
  else         { u.p.hi = hi >> b; u.p.lo = (hi << (32 - b)) | (lo >> b); }
  return u.ull;
}
