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


; Change some logic to keep the 8th scale borders visible until the full borders are completed.
@HOOK 0x004A75B1, 0x004A75C0
    ; We've just compared the number of full borders constructed with 0.
    ; If it's >= 0, proceed to the next section.
    JGE .next
    ; If it's -1 this means the 8th scale borders have been drawn and we want to construct the full
    ; borders on the next draw. Set the number of full borders to 0 and then go to the return.
    MOV word [0x007DCF90], 0
    JMP 0x004A7E29
.next:
    ; 0x801 indicates that all full borders have been drawn and we should return.
    CMP word [0x007DCF90], 0x801
    JGE 0x004A7E29
    ; Otherwise proceed with the original code which will clear the borders data.
    JMP @HOOKEND

; Go straight to border construction after clearing the borders data.
@LJMP 0x004A762F, 0x004A7DD0

; Clear a jump that breaks the border construction loop between each system.
; This makes sure all the systems are processed before the next draw.
@CLEAR_NOP 0x004A7E74, 0x004A7E74 + 2


; Fix incorrect rect being passed to borders function when clicking the Show Borders button.
@HOOK 0x004A434A, 0x004A4353
    LEA EDX, [ESP + 0x10]
    PUSH EDX
    CALL 0x004A9D10
    JMP @HOOKEND
