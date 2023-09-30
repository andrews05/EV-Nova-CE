%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Prevents switching to windowed mode when opening pilot


; There are differnt methods for patching, here 2 examples for the same patch


; replacing raw bytes to fix the two jumps (original copy of byte patch from andrews github)
; fill data between arg1 and arg3 with value from arg2
@CLEAR 0x004C9FB8, 0x90, 0x004C9FBE
; set 2 bytes at arg1
@SET 0x004C9F4C, { db 0xEB, 0x42 }



; alternative patch
; insert small jump
;@SJMP 0x004C9F4C, 0x004C9F90
; remove long jump and fill with NOPS
;@CLEAR_NOP 0x004C9FB8, 0x004C9FBE
