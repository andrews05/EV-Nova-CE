%ifndef IMPORTS_INC
%define IMPORTS_INC

%include "macros/datatypes.inc"

%macro define_import 1
    %defstr ___TmpStringX_ %1

    sstring str_%1, ___TmpStringX_
    gint _imp__%1, 0

    global _%1
    sfunction _%1
        jmp [_imp__%1]
%endmacro

%macro load_import 1
    push str_%1
    push esi
    call [_imp__GetProcAddress]
    mov [_imp__%1], eax
%endmacro

%macro define_library 1
    %defstr ___TmpStringX_ %1
        
    sstring str_%1_dll, ___TmpStringX_
%endmacro

%macro load_library 1
    push str_%1_dll
    call [_imp__LoadLibraryA]
    mov esi, eax
%endmacro

%endif
