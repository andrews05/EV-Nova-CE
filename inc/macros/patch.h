
#define PATCH_START(patchaddr)                      \
        ".section .patch,\"d0\";"                   \
        ".long " #patchaddr ";"                     \
        ".long (9f - 8f);"                          \
        "8:;"

#define PATCH_END                                   \
        "9:;"                                       \
        ".section .text;"

#define SETINST(addr, inst)                         \
    __asm (                                         \
        PATCH_START(addr)                           \
        inst ";"                                    \
        PATCH_END                                   \
    )

#define CLEAR(start, value, end)                    \
    __asm (                                         \
        PATCH_START(start)                          \
        ".fill (" #end ") - (" #start "), 1, " #value ";" \
        PATCH_END                                   \
    )

#define SJMP(src, dst)                              \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xEB;"                               \
        ".byte (" #dst ") - (" #src ") - 2;"        \
        PATCH_END                                   \
    )

#define LJMP(src, dst)                              \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xE9;"                               \
        ".long (" #dst ") - (" #src ") - 5;"        \
        PATCH_END                                   \
    )

#define SETDWORD(addr, value)                       \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".long " #value ";"                         \
        PATCH_END                                   \
    )

#define SETWORD(addr, value)                        \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".short " #value ";"                        \
        PATCH_END                                   \
    )

#define SETBYTE(addr, value)                        \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".byte " #value ";"                         \
        PATCH_END                                   \
    )
    
#define SETBYTES(addr, value)                       \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".ascii " #value ";"                        \
        PATCH_END                                   \
    )

#define HOOK_1(addr)                                \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".byte 0xE9;"                               \
        ".long _dest" #addr "-" #addr " - 5;"       \
        PATCH_END                                   \
    );                                              \
    EXTERN_C void __attribute__((naked)) dest##addr()

#define HOOK_2(addr, end)                           \
    __asm (                                         \
        PATCH_START(addr)                           \
        ".byte 0xE9;"                               \
        ".long _dest" #addr "-" #addr " - 5;"       \
        ".fill (" #end ") - ((" #addr ") + 5), 1, 0xCC;" \
        PATCH_END                                   \
    );                                              \
    EXTERN_C void __attribute__((naked)) dest##addr()

#define HOOK_X(x,A,B,FUNC, ...)  FUNC  
#define HOOK(...)         HOOK_X(,##__VA_ARGS__,    \
                               HOOK_2(__VA_ARGS__), \
                               HOOK_1(__VA_ARGS__), \
                               HOOK_0(__VA_ARGS__)  \
                               )

#define CLEAR_NOP(start, end) CLEAR(start, 0x90, end)
#define CLEAR_INT(start, end) CLEAR(start, 0xCC, end)

#define WATCALL_TO_CDECL(dst, arg_count)            \
        ".align 16, 0xCC;"                          \
        ".if " #arg_count " == 0;"                  \
            "1:;"                                   \
            "push ecx;"                             \
            "push edx;"                             \
            "call " #dst ";"                        \
            "pop edx;"                              \
            "pop ecx;"                              \
            "ret;"                                  \
        ".elseif " #arg_count " == 1;"              \
            "1:;"                                   \
            "push ecx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 4;"                           \
            "pop edx;"                              \
            "pop ecx;"                              \
            "ret;"                                  \
        ".elseif " #arg_count " == 2;"              \
            "1:;"                                   \
            "push ecx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 8;"                           \
            "pop ecx;"                              \
            "ret;"                                  \
        ".elseif " #arg_count " == 3;"              \
            "1:;"                                   \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 12;"                          \
            "pop ecx;"                              \
            "ret;"                                  \
        ".elseif " #arg_count " == 4;"              \
            "1:;"                                   \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 16;"                          \
            "ret;"                                  \
        ".elseif " #arg_count " == 5;"              \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 20;"                          \
            "pop ebp;"                              \
            "ret 4;"                                \
        ".elseif " #arg_count " == 6;"              \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 24;"                          \
            "pop ebp;"                              \
            "ret 8;"                                \
        ".elseif " #arg_count " == 7;"              \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 28;"                          \
            "pop ebp;"                              \
            "ret 12;"                               \
        ".elseif " #arg_count " == 8;"              \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 32;"                          \
            "pop ebp;"                              \
            "ret 16;"                               \
        ".elseif " #arg_count " == 9;"              \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 36;"                          \
            "pop ebp;"                              \
            "ret 20;"                               \
        ".elseif " #arg_count " == 10;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 40;"                          \
            "pop ebp;"                              \
            "ret 24;"                               \
        ".elseif " #arg_count " == 11;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+32];"                        \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 44;"                          \
            "pop ebp;"                              \
            "ret 28;"                               \
        ".elseif " #arg_count " == 12;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+36];"                        \
            "push [ebp+32];"                        \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 48;"                          \
            "pop ebp;"                              \
            "ret 32;"                               \
        ".elseif " #arg_count " == 13;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+40];"                        \
            "push [ebp+36];"                        \
            "push [ebp+32];"                        \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 52;"                          \
            "pop ebp;"                              \
            "ret 36;"                               \
        ".elseif " #arg_count " == 14;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+44];"                        \
            "push [ebp+40];"                        \
            "push [ebp+36];"                        \
            "push [ebp+32];"                        \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 56;"                          \
            "pop ebp;"                              \
            "ret 40;"                               \
        ".elseif " #arg_count " == 15;"             \
            "1:;"                                   \
            "push ebp;"                             \
            "mov ebp, esp;"                         \
            "push [ebp+48];"                        \
            "push [ebp+44];"                        \
            "push [ebp+40];"                        \
            "push [ebp+36];"                        \
            "push [ebp+32];"                        \
            "push [ebp+28];"                        \
            "push [ebp+24];"                        \
            "push [ebp+20];"                        \
            "push [ebp+16];"                        \
            "push [ebp+12];"                        \
            "push [ebp+8];"                         \
            "push ecx;"                             \
            "push ebx;"                             \
            "push edx;"                             \
            "push eax;"                             \
            "call " #dst ";"                        \
            "add esp, 60;"                          \
            "pop ebp;"                              \
            "ret 44;"                               \
        ".else;"                                    \
            ".error \"Too many args in macro\";"    \
        ".endif;"
        
#define DETOUR_3(start, end, dst)                   \
    __asm (                                         \
        PATCH_START(start)                          \
        ".byte 0xE9;"                               \
        ".long (" #dst ") - (" #start ") - 5;"      \
        ".fill (" #end ") - ((" #start ") + 5), 1, 0xCC;" \
        PATCH_END                                   \
    )
    
#define DETOUR_4(start, end, dst, arg_count)        \
    __asm (                                         \
        PATCH_START(start)                          \
        ".byte 0xE9;"                               \
        ".long 1f - (" #start ") - 5;"              \
        ".fill (" #end ") - ((" #start ") + 5), 1, 0xCC;" \
        PATCH_END                                   \
        WATCALL_TO_CDECL(dst, arg_count)            \
    )

#define DETOUR_X(x,A,B,C,D,FUNC, ...)  FUNC  
#define DETOUR(...)                                 \
                        DETOUR_X(,##__VA_ARGS__,    \
                             DETOUR_4(__VA_ARGS__), \
                             DETOUR_3(__VA_ARGS__), \
                             DETOUR_2(__VA_ARGS__), \
                             DETOUR_1(__VA_ARGS__), \
                             DETOUR_0(__VA_ARGS__)  \
                             )

#define CALL_2(src, dst)                            \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xE8;"                               \
        ".long (" #dst ") - (" #src ") - 5;"        \
        PATCH_END                                   \
    )

#define CALL_3(src, dst, arg_count)                 \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xE8;"                               \
        ".long 1f - (" #src ") - 5;"                \
        PATCH_END                                   \
        WATCALL_TO_CDECL(dst, arg_count)            \
    )

#define CALL_X(x,A,B,C,FUNC, ...)  FUNC  
#define CALL(...)                                   \
                          CALL_X(,##__VA_ARGS__,    \
                               CALL_3(__VA_ARGS__), \
                               CALL_2(__VA_ARGS__), \
                               CALL_1(__VA_ARGS__), \
                               CALL_0(__VA_ARGS__)  \
                               )

#define CALL_NOP_2(src, dst)                        \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xE8;"                               \
        ".long (" #dst ") - (" #src ") - 5;"        \
        ".byte 0x90;"                               \
        PATCH_END                                   \
    )

#define CALL_NOP_3(src, dst, arg_count)             \
    __asm (                                         \
        PATCH_START(src)                            \
        ".byte 0xE8;"                               \
        ".long 1f - (" #src ") - 5;"                \
        ".byte 0x90;"                               \
        PATCH_END                                   \
        WATCALL_TO_CDECL(dst, arg_count)            \
    )

#define CALL_NOP_X(x,A,B,C,FUNC, ...)  FUNC  
#define CALL_NOP(...)                               \
                      CALL_NOP_X(,##__VA_ARGS__,    \
                           CALL_NOP_3(__VA_ARGS__), \
                           CALL_NOP_2(__VA_ARGS__), \
                           CALL_NOP_1(__VA_ARGS__), \
                           CALL_NOP_0(__VA_ARGS__)  \
                           )
