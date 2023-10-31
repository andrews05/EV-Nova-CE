%include "macros/patch.inc"
%include "macros/datatypes.inc"
%include "nova.inc"

; Change the status bar drawing to reference global var for the width

; Purpose unknown - hook anyway
@HOOK 0x00438FC0, 0x00438FC7
    MOV EDX, [g_statusBarWidth]
    SUB word [ESP + 0x6], DX
    JMP @HOOKEND

; Game area click
@HOOK 0x0044E012, 0x0044E019
    MOV EDX, [g_statusBarWidth]
    SUB word [ESP + 0x7A], DX
    JMP @HOOKEND

; Game width
@HOOK 0x004AB9CA, 0x004AB9D4
    MOV EDX, [g_statusBarWidth]
    SUB word [ESP + 0x10A], DX
    JMP @HOOKEND

; Mini map position
@HOOK 0x004ABD87, 0x004ABD8D
    ADD EDX, [g_statusBarWidth]
    ADD EDX, 16
    JMP @HOOKEND

; Status bar background buffer
@SET 0x004AC9E4, { ADD ECX, [g_statusBarWidth] }

; Status bar area
@SET 0x0045D0FE, { SUB EDX, [g_statusBarWidth] }
@SET 0x0045D211, { SUB ECX, [g_statusBarWidth] }
@HOOK 0x0045D282, 0x0045D287
    SUB EAX, [g_statusBarWidth]
    JMP @HOOKEND

; Status bar items
@SET 0x0045D6D0, { SUB EDX, [g_statusBarWidth] }
@SET 0x0045E4BF, { SUB EBP, [g_statusBarWidth] }
@HOOK 0x0045EA61, 0x0045EA66
    SUB EAX, [g_statusBarWidth]
    JMP @HOOKEND
@HOOK 0x0045EBE3, 0x0045EBE8
    SUB EAX, [g_statusBarWidth]
    JMP @HOOKEND
@HOOK 0x0045F081, 0x0045F086
    SUB EAX, [g_statusBarWidth]
    JMP @HOOKEND
@SET 0x0045F6BD, { SUB EDX, [g_statusBarWidth] }
@SET 0x00460FA7, { SUB ECX, [g_statusBarWidth] }
@SET 0x0046139C, { SUB EBP, [g_statusBarWidth] }

; Status bar redraw area?
@SET 0x0046AA1E, { SUB EDX, [g_statusBarWidth] }

; Main screen
@HOOK 0x00487FC8, 0x00487FCD
    SUB EAX, [g_statusBarWidth]
    JMP @HOOKEND
@SET 0x00488034, { SUB EBX, [g_statusBarWidth] }

; Map close redraw check
@SET 0x004A5115, { SUB EDI, [g_statusBarWidth] }

; Game center
@SET 0x004AC488, { SUB EDX, [g_statusBarWidth] }
