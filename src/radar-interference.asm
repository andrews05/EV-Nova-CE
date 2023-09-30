%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Fixes ppat parsing for radar interference

@SET 0x004FDF74, { MOV EBX, [EDX+2] }
@SET 0x004FDF79, { MOV EAX, [EDX+6] }
@SET 0x004FDF88, { CMP EBX, 0x1C }
@SET 0x004FDF8D, { CMP EAX, 0x4E }
@SET 0x004FDFEC, { MOV EAX, [EDX+0x2A] }
@SET 0x004FE038, { MOVZX ECX, WORD[EDX+0x20] }
