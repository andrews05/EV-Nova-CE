%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Disables font substitution so that, e.g., Geneva won't be replace with Arial

@SJMP 0x004BC474, 0x004BC4D0
