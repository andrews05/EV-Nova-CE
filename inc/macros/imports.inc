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
    call [edi]
    
    mov edx, str_%1
    test eax, eax
    jz .fail
    
    mov [_imp__%1], eax
%endmacro

%macro define_library 1
    %defstr ___TmpStringX_ %1
        
    sstring str_%1_dll, ___TmpStringX_
%endmacro

%macro load_library 1
    mov edx, str_LoadLibraryA
    test ebx, ebx
    jz .fail
    
    mov edx, str_GetProcAddress
    test edi, edi
    jz .fail

    push str_%1_dll
    call [ebx]
    
    mov edx, str_%1_dll
    test eax, eax
    jz .fail
    
    mov esi, eax
%endmacro

%endif
