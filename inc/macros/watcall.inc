%include "macros/extern.inc"

cextern watcall

; make existing watcall functions global
%macro setwatglob 3
    global _%2
    global %2
    %2 equ %1
    
    [section .text]
    align 16, db 0xCC
    _%2:
    push %1
    push %3
    jmp watcall
    __SECT__
%endmacro

; create new global watcall functions
%macro gwatfunction 2
    global %1
    global _%1
    
    [section .text]
    align 16, db 0xCC
    _%1:
    push %1
    push %2
    jmp watcall
    
    align 16, db 0xCC
    %1:
%endmacro
