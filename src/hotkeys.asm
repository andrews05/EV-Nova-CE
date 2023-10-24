%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Adds additional hot keys to match Mac Nova


; Shipyard: spacebar = Info
@HOOK 0x00494035, 0x0049403B
    ; Redo the jump we replaced
    JZ 0x004940E4
    CMP EAX, ' '
    JNZ @HOOKEND
    MOV WORD[ESI], 1
    ; Info button is item 10
    MOV WORD[EBX], 10
    ; Jump to return
    JMP 0x00494054

; Ship Info: spacebar = Done
@HOOK 0x00495AB3, 0x00495AB9
    JZ @HOOKEND
    CMP EAX, ' '
    JZ @HOOKEND
    ; Redo the jump we replaced
    JMP 0x004959EF


; Map: C = Clear Route (normally centers map, but spacebar does this also)
;      B = Show/Hide Borders
@HOOK 0x004A7674, 0x004A767A
    JNZ .next
    ; Clear button is item 8
    MOV WORD[EBX], 8
    ; Jump to return
    JMP 0x004A7705
.next:
    CMP EAX, 'b'
    JNZ @HOOKEND
    ; Borders button is item 9
    MOV WORD[EBX], 9
    ; Jump to return
    JMP 0x004A7705
