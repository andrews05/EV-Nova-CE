
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
        @LJMP (\addr), _dest\addr
    .else
        .set @HOOKEND, (\end)

        .if (\end) - ((\addr) + 5) < 0
            .error "end must be at least 5 bytes (the size of a long jump) after start (\end)"
        .endif
    
        .section .patch,"d0"
        .long (\addr)
        .long 5 + ((\end) - ((\addr) + 5))
        .byte 0xE9
        .long (_dest\addr) - (\addr) - 5
        .fill (\end) - ((\addr) + 5), 1, 0xCC
    .endif
    
    .section .text
    .align 8, 0xCC
    _dest\addr\():
.endm

.macro @CLEAR_NOP start:req, end:req
    @CLEAR (\start), 0x90, (\end)
.endm

.macro @CLEAR_INT start:req, end:req
    @CLEAR (\start), 0xCC, (\end)
.endm

.macro @LJMP_NOP start:req, end:req, dst:req
    .if (\end) - ((\start) + 5) < 0
        .error "end must be at least 5 bytes (the size of a long jump) after start (\end)"
    .endif

    .section .patch,"d0"
    .long (\start)
    .long 5 + ((\end) - ((\start) + 5))
    .byte 0xE9
    .long (\dst) - (\start) - 5
    .fill (\end) - ((\start) + 5), 1, 0x90
.endm

.macro @LJMP_INT start:req, end:req, dst:req
    .if (\end) - ((\start) + 5) < 0
        .error "end must be at least 5 bytes (the size of a long jump) after start (\end)"
    .endif

    .section .patch,"d0"
    .long (\start)
    .long 5 + ((\end) - ((\start) + 5))
    .byte 0xE9
    .long (\dst) - (\start) - 5
    .fill (\end) - ((\start) + 5), 1, 0xCC
.endm
