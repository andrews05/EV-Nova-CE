%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Increase the particle cap from the default of 1024


@SET 0x004AC29C, { PUSH 100000 }
