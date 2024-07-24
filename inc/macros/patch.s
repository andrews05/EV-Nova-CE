
.macro @SET addr:req, inst:req
    .section .patch,"d0" 
    .long (\addr)
    .long (_patchset_end_\@ - _patchset_start_\@)
_patchset_start_\@:
    \inst
_patchset_end_\@:
.endm

.macro @CLEAR start:req, value:req, end:req
    .section .patch,"d0"
    .long (\start)
    .long (\end) - (\start)
    .fill (\end) - (\start), 1, (\value)
.endm

.macro @SJMP src:req, dst:req
    .section .patch,"d0"
    .long (\src)
    .long 2
    .byte 0xEB
    .byte (\dst) - (\src) - 2
.endm

.macro @LJMP src:req, dst:req
    .section .patch,"d0"
    .long (\src)
    .long 5
    .byte 0xE9
    .long (\dst) - (\src) - 5
.endm

.macro @CALL src:req, dst:req
    .section .patch,"d0" 
    .long (\src)
    .long 5
    .byte 0xE8
    .long (\dst) - (\src) - 5
.endm

.macro @CALL_NOP src:req, dst:req
    .section .patch,"d0" 
    .long (\src)
    .long 6
    .byte 0xE8
    .long (\dst) - (\src) - 5
    .byte 0x90 
.endm

.macro @HOOK addr:req, end
    .ifb \end
        .set @HOOKEND, (\addr) + 5
    .else
        .set @HOOKEND, (\end)
        @CLEAR (\addr) + 5, 0xCC, (\end)
    .endif
    
    @LJMP (\addr), dest\addr
    .section .text
    .align 8, 0xCC
    dest\addr\():
.endm

.macro @CLEAR_NOP start:req, end:req
    @CLEAR (\start), 0x90, (\end)
.endm

.macro @CLEAR_INT start:req, end:req
    @CLEAR (\start), 0xCC, (\end)
.endm

.macro @LJMP_NOP start:req, end:req, dst:req
    @CLEAR (\start) + 5, 0x90, (\end)
    @LJMP (\start), (\dst)
.endm

.macro @LJMP_INT start:req, end:req, dst:req
    @CLEAR (\start) + 5, 0xCC, (\end)
    @LJMP (\start), (\dst)
.endm
