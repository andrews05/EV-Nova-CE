%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Max particles (default 1024)
@SET 0x004AC29C+1, { dd 100000 }

; Max shots (default 128)
; Signed 16-bit value, must be multiple of 8
%define MAX_SHOTS 512
@SET 0x004AC81F+1, { dd MAX_SHOTS * 72 }
@SET 0x00418F0E+3, { dw MAX_SHOTS }
@SET 0x00419280+3, { dw MAX_SHOTS }
@SET 0x0041FDB6+3, { dw MAX_SHOTS }
@SET 0x00422327+3, { dw MAX_SHOTS }
@SET 0x0042DA38+3, { dw MAX_SHOTS }
@SET 0x0043762E+1, { dd MAX_SHOTS }
@SET 0x004385FC+5, { dw MAX_SHOTS }
@SET 0x0043A5FE+5, { dw MAX_SHOTS }
@SET 0x0044849F+3, { dw MAX_SHOTS }
@SET 0x00456243+3, { dw MAX_SHOTS }
@SET 0x0045BB9B+3, { dw MAX_SHOTS }
@SET 0x004AD014+3, { dw MAX_SHOTS }
@SET 0x004AF797+3, { dw MAX_SHOTS }
@SET 0x004B27C1+3, { dw MAX_SHOTS }
@SET 0x004B4A3B+3, { dw MAX_SHOTS }
