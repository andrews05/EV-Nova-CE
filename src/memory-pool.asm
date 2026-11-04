%include "macros/patch.inc"

; Nova makes its memory pool half the RAM Windows reports, but Windows reports at most 2 GB to Nova,
; so the pool is always 1 GB and large plug-in sets fail to load ("Error loading spïn resource from RLE
; data"). Use a fixed 1400 MB instead. If that much can't be had, Nova already falls back to the largest
; block it can get.
@SET       0x004D2AD0, { mov ecx, 1400 * 1024 * 1024 }
@CLEAR_NOP 0x004D2AD5, 0x004D2AD9
