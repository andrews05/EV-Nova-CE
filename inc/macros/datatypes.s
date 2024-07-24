.include "macros/extern.s"

.set true, 1
.set false, 0

# global const string -> arg1 = name, arg2 = value
.macro gstring name:req, value:req
    cglobal \name
    sstring \name, \value
.endm

# static (local) const string -> arg1 = name, arg2 = value
.macro sstring name:req, value:req
    .section .rdata
    \name\(): .asciz "\value"
.endm

# global int -> arg1 = name, arg2 = value, arg3 = array length
.macro gint name:req, value:req, length=0
    cglobal \name
    sint \name, \value, \length
.endm

# static (local) int -> arg1 = name, arg2 = value, arg3 = array length
.macro sint name:req, value:req, length=0
    .ifeq (\value)
        .section .bss
    .else
        .section .data
    .endif

    .ifeq (\length)
        \name\(): .long (\value)
    .else
        \name\(): .fill (\length), 4, (\value)
    .endif
.endm

# global short -> arg1 = name, arg2 = value, arg3 = array length
.macro gshort name:req, value:req, length=0
    cglobal \name
    sshort \name, \value, \length
.endm

# static (local) short -> arg1 = name, arg2 = value, arg3 = array length
.macro sshort name:req, value:req, length=0
    .ifeq (\value)
        .section .bss
    .else
        .section .data
    .endif
    
    .ifeq (\length)
        \name\(): .short (\value)
    .else
        \name\(): .fill (\length), 2, (\value)
    .endif
.endm

# global byte -> arg1 = name, arg2 = value, arg3 = array length
.macro gbyte name:req, value:req, length=0
    cglobal \name
    sbyte \name, \value, \length
.endm

# static (local) byte -> arg1 = name, arg2 = value, arg3 = array length
.macro sbyte name:req, value:req, length=0
    .ifeq (\value)
        .section .bss
    .else
        .section .data
    .endif
    
    .ifeq (\length)
        \name\(): .byte (\value)
    .else
        \name\(): .fill (\length), 1, (\value)
    .endif
.endm

# global bool -> arg1 = name, arg2 = value, arg3 = array length
.macro gbool name:req, value:req, length=0
    cglobal \name
    sbyte \name, \value, \length
.endm

# static (local) bool -> arg1 = name, arg2 = value, arg3 = array length
.macro sbool name:req, value:req, length=0
    sbyte \name, \value, \length
.endm

# global function -> arg1 = name
.macro gfunction name:req
    cglobal \name
    sfunction \name
.endm

# static (local) function -> arg1 = name
.macro sfunction name:req
    .section .text
    .align 8, 0xCC
    \name\():
.endm

# global file (const byte array) -> arg1 = name, arg2 = filePath
.macro gfile name:req, path:req
    cglobal \name
    cglobal \name\()Length
    sfile \name, \path
.endm

# static (local) file (const byte array) -> arg1 = name, arg2 = filePath
.macro sfile name:req, path:req
    .section .rdata
_incbin_start_\@:
    \name\(): .incbin "\path"
_incbin_end_\@: 
    \name\()Length: .long (_incbin_end_\@ - _incbin_start_\@)
.endm
