%include "macros/patch.inc"
%include "macros/datatypes.inc"
%include "nova.inc"

; Improve map borders construction performance by restricting to the visible area


; Checking bounds for replicating the 1/8th scale borders
@SET 0x004A9F51, { CMP EDI, [_g_mapBordersVisibleWidth] }
@SET 0x004A9F64, { CMP EBP, [_g_mapBordersVisibleHeight] }

; Checking if the system is within or near the map borders
@HOOK 0x004AA250, 0x004AA25E
    ; Add our global width
    ADD EBP, [_g_mapBordersVisibleWidth]
    ; Repeat the original CMP and JG
    CMP ESI, EBP
    JG 0x004AA610
    ; Restore the EBP then add our global height
    MOV EBP, [ESP + 0x2C]
    ADD EBP, [_g_mapBordersVisibleHeight]
    JMP @HOOKEND

; Checking if the point is within the map borders
@HOOK 0x004AA2D3, 0x004AA2DA
    ; Load global var before comparing
    MOV BX, [_g_mapBordersVisibleWidth]
    CMP word [ESP + 0x28], BX
    JMP @HOOKEND
@HOOK 0x004AA2EC, 0x004AA2F3
    ; Load global var before comparing
    MOV BX, [_g_mapBordersVisibleHeight]
    CMP word [ESP + 0x24], BX
    JMP @HOOKEND
