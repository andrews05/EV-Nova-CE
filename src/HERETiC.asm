%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Applies the HERETiC crack

%assign text_base 0x400C00

@SET text_base + 0x00020CE3, { db 0x01 }
@SET text_base + 0x000D38E4, { db 0xC6 }
@SET text_base + 0x000D38E5, { db 0x05 }
@SET text_base + 0x000D38EA, { db 0x01 }
@SET text_base + 0x000D38EC, { db 0x00 }
