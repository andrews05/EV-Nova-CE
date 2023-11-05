%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Enables some miscellaneous error logging


; Clear a jump
@CLEAR_NOP 0x00503ec8, 0x00503ec8 + 2
; Replace a log&exit call with just a log call
@CALL 0x00503ed4, 0x004d9d10
