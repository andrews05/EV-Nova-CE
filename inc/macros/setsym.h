#define CDECL_TO_WATCALL(addr, arg_count)            \
        "push ebx;"                                  \
        "push ebp;"                                  \
        "mov ebp, esp;"                              \
        ".if " #arg_count " >= 16;"                  \
            ".error \"Too many args in macro\";"     \
        ".endif;"                                    \
        ".if " #arg_count " >= 15;"                  \
            "push [ebp+68];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 14;"                  \
            "push [ebp+64];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 13;"                  \
            "push [ebp+60];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 12;"                  \
            "push [ebp+56];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 11;"                  \
            "push [ebp+52];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 10;"                  \
            "push [ebp+48];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 9;"                   \
            "push [ebp+44];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 8;"                   \
            "push [ebp+40];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 7;"                   \
            "push [ebp+36];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 6;"                   \
            "push [ebp+32];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 5;"                   \
            "push [ebp+28];"                         \
        ".endif;"                                    \
        ".if " #arg_count " >= 4;"                   \
            "mov ecx, [ebp+24];"                     \
        ".endif;"                                    \
        ".if " #arg_count " >= 3;"                   \
            "mov ebx, [ebp+20];"                     \
        ".endif;"                                    \
        ".if " #arg_count " >= 2;"                   \
            "mov edx, [ebp+16];"                     \
        ".endif;"                                    \
        ".if " #arg_count " >= 1;"                   \
            "mov eax, [ebp+12];"                     \
        ".endif;"                                    \
        "call " #addr ";"                            \
        "pop ebp;"                                   \
        "pop ebx;"                                   \
        "ret;"

#define SETCGLOB_2(addr, name)                       \
    __asm (                                          \
        ".global _" #name ";"                        \
        ".equ _" #name ", " #addr ";"                \
    )

#define SETCGLOB_3(addr, name, arg_count)            \
    __asm (                                          \
        ".global _" #name ";"                        \
        ".global " #name ";"                         \
        ".equ " #name ", " #addr ";"                 \
        ".section .text;"                            \
        ".align 8, 0xCC;"                            \
        "_" #name ":;"                               \
        CDECL_TO_WATCALL(addr, arg_count)            \
    )

#define SETCGLOB_X(x,A,B,C,FUNC, ...)  FUNC  
#define SETCGLOB(...)                                \
                       SETCGLOB_X(,##__VA_ARGS__,    \
                            SETCGLOB_3(__VA_ARGS__), \
                            SETCGLOB_2(__VA_ARGS__), \
                            SETCGLOB_1(__VA_ARGS__), \
                            SETCGLOB_0(__VA_ARGS__)  \
                            )

#define TRAMPOLINE_3(addr, name, inst)               \
    __asm (                                          \
        ".global _" #name ";"                        \
        ".section .text;"                            \
        ".align 8, 0xCC;"                            \
        "_" #name ":;"                               \
        inst ";"                                     \
        "jmp " #addr ";"                             \
    )

#define TRAMPOLINE_4(addr, name, inst, arg_count)    \
    __asm (                                          \
        ".global _" #name ";"                        \
        ".global " #name ";"                         \
        ".section .text;"                            \
        ".align 8, 0xCC;"                            \
        #name ":;"                                   \
        inst ";"                                     \
        "jmp " #addr ";"                             \
        ".align 8, 0xCC;"                            \
        "_" #name ":;"                               \
        CDECL_TO_WATCALL(name, arg_count)            \
    )

#define TRAMPOLINE_X(x,A,B,C,D,FUNC, ...)  FUNC  
#define TRAMPOLINE(...)                              \
                     TRAMPOLINE_X(,##__VA_ARGS__,    \
                          TRAMPOLINE_4(__VA_ARGS__), \
                          TRAMPOLINE_3(__VA_ARGS__), \
                          TRAMPOLINE_2(__VA_ARGS__), \
                          TRAMPOLINE_1(__VA_ARGS__), \
                          TRAMPOLINE_0(__VA_ARGS__)  \
                          )
