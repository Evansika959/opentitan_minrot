// puf_preload_spike.S -- links the known PUF response bytes into spike's
// memory at PUF_BASE+4 (0x80040004), same .incbin technique as
// dmem_preload_spike.S. Placed via the linker so it becomes a real
// PT_LOAD segment (a post-link objcopy --add-section was tried first and
// silently failed to actually load, see dmem_preload_spike.S's comment).
.section .puf_preload_sec, "a"
.incbin PUF_BIN_PATH
