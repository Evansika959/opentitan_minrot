// Minimal compiler-rt replacements for freestanding build
unsigned long long __lshrdi3(unsigned long long a, int b) {
  return a >> b;
}
