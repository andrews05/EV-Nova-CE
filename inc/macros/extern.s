
.macro cglobal name
    .global _\name
    .equ _\name, \name
.endm

.macro cextern name
    .equ \name, _\name
.endm
