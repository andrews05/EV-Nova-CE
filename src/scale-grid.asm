%include "macros/patch.inc"
%include "macros/datatypes.inc"
%include "nova.inc"

; Change the outfitter/shipyard click detection to reference global vars for the cell size

; Outfitter click
@HOOK 0x00490974, 0x004909A0
    ; Divide x by global var
    MOV EAX, EDX
    MOV CL, [g_gridCellWidth]
    DIV CL
    MOVZX ECX, AL
    ; Repeat these original instructions
    MOVZX EAX, word [ESP]
    MOVZX EDX, word [ESP + 0x10]
    SUB EDX, EAX
    ; Divide y by global var
    MOV EAX, EDX
    MOV DL, [g_gridCellHeight]
    DIV DL
    MOVZX EDI, AL
    JMP @HOOKEND

; Shipyard click
@HOOK 0x00494563, 0x0049458D
    ; Divide x by global var
    MOV EAX, EDX
    MOV CL, [g_gridCellWidth]
    DIV CL
    MOVZX ECX, AL
    ; Repeat these original instructions
    MOVZX EAX, word [ESP]
    MOVZX EDX, word [ESP + 0x18]
    SUB EDX, EAX
    ; Divide y by global var
    MOV EAX, EDX
    MOV DL, [g_gridCellHeight]
    DIV DL
    MOVZX EDI, AL
    JMP @HOOKEND

; Control label
@HOOK 0x004D0EE3, 0x004D0EE9
    MOV AX, word [g_controlLabelWidth]
    ADD word [ESP + 0x3A], AX
    JMP @HOOKEND

; Popup menu
@HOOK 0x004CF20E, 0x004CF214
    MOV BX, word [g_controlLabelWidth]
    ADD word [ESP + 0x16], BX
    JMP @HOOKEND

; Change control label to the CNTL title instead of the MENU title
@SET 0x004CEB78, { MOV ECX, [ESP + 0x32C]}
