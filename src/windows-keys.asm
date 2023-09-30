%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Nova disables both windows keys for any reason, this patch will re-enable them

@SJMP 0x004D2403, 0x004D2420
