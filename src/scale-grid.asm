%include "macros/patch.inc"
%include "macros/datatypes.inc"
%include "nova.inc"

; Change the outfitter/shipyard grid drawing and click detection to reference global vars for the cell size

; Grid cell height
@HOOK 0x0049918D, 0x00499193
    IMUL EDI, [g_gridCellHeight]
    IMUL ESI, [g_gridCellHeight]
    JMP @HOOKEND

; Grid cell width
@HOOK 0x0049919C, 0x004991A2
    IMUL EDI, [g_gridCellWidth]
    IMUL EAX, [g_gridCellWidth]
    JMP @HOOKEND

; Outfitter click
@HOOK 0x00490974, 0x004909A0
    ; Divide x by global var
    MOV EAX, EDX
    MOV CL, [g_gridCellWidth]
    IDIV CL
    MOVZX ECX, AL
    ; Repeat these original instructions
    MOVZX EAX, word [ESP]
    MOVZX EDX, word [ESP + 0x10]
    SUB EDX, EAX
    ; Divide y by global var
    MOV EAX, EDX
    MOV DL, [g_gridCellHeight]
    IDIV DL
    MOVZX EDI, AL
    JMP @HOOKEND

; Shipyard click
@HOOK 0x00494563, 0x0049458D
    ; Divide x by global var
    MOV EAX, EDX
    MOV CL, [g_gridCellWidth]
    IDIV CL
    MOVZX ECX, AL
    ; Repeat these original instructions
    MOVZX EAX, word [ESP]
    MOVZX EDX, word [ESP + 0x18]
    SUB EDX, EAX
    ; Divide y by global var
    MOV EAX, EDX
    MOV DL, [g_gridCellHeight]
    IDIV DL
    MOVZX EDI, AL
    JMP @HOOKEND
