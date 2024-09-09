
.macro @PATCH patchaddr:req
    .if __patch == 1
        .error "can't nest patches"
    .endif
    
    .set __patch, 1
    .section .patch,"d0"
    .long (\patchaddr)
    .long (9f - 8f)
8:
.endm

.macro @ENDPATCH
    .if __patch == 0
        .error "no corresponding `@PATCH'"
    .endif
    
    .ifndef __patch
        .error "no corresponding `@PATCH'"
    .endif

    .set __patch, 0
9:
    .section .text
.endm

.macro @SET addr:req, inst:req
    @PATCH (\addr)
    \inst
    @ENDPATCH
.endm

.macro @CLEAR start:req, value:req, end:req
    @PATCH (\start)
    .fill (\end) - (\start), 1, (\value)
    @ENDPATCH
.endm

.macro @SJMP src:req, dst:req
    @PATCH (\src)
    .byte 0xEB
    .byte (\dst) - (\src) - 2
    @ENDPATCH
.endm

.macro @LJMP src:req, dst:req
    @PATCH (\src)
    .byte 0xE9
    .long (\dst) - (\src) - 5
    @ENDPATCH
.endm

.macro @CALL src:req, dst:req
    @PATCH (\src)
    .byte 0xE8
    .long (\dst) - (\src) - 5
    @ENDPATCH
.endm

.macro @CALL_NOP src:req, dst:req
    @PATCH (\src)
    .byte 0xE8
    .long (\dst) - (\src) - 5
    .byte 0x90 
    @ENDPATCH
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
    
        @PATCH (\addr)
        .byte 0xE9
        .long (_dest\addr) - (\addr) - 5
        .fill (\end) - ((\addr) + 5), 1, 0xCC
        @ENDPATCH
    .endif
    
    .section .text
    .align 16, 0xCC
    _dest\addr\():
.endm

.macro @CLEAR_NOP start:req, end:req
    @CLEAR (\start), 0x90, (\end)
.endm

.macro @CLEAR_INT start:req, end:req
    @CLEAR (\start), 0xCC, (\end)
.endm
