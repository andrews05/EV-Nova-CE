%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Improve selection of nebula image sizes
; Nova prefers to scale up a smaller image but we change it to prefer scaling down a larger image


; Break the loop when the image is greater than or equal to the desired size
; Jump to just past a MOVSX so we end up using the loop variable as the size
@SET 0x004A584C, { db 0x7D, 0x36 }
@SET 0x004A5874, { db 0x7D, 0x0D }
