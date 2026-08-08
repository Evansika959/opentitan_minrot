// dmem_preload_spike.S -- links the packed DMEM image directly into the
// spike-only ELF as a proper loadable segment (objcopy --add-section
// only adds section-table metadata, not a PT_LOAD program header, so
// spike's ELF loader silently never actually copied that data into
// memory -- this .incbin approach goes through the normal linker
// SECTIONS placement instead, which does get a real PT_LOAD segment).
.section .dmem_preload_sec, "a"
.incbin DMEM_BIN_PATH
