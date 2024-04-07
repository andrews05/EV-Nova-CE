
#define SETINST(addr, inst)                         \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #addr ";"                          \
        ".long (2f - 1f);"                          \
        "1:;"                                       \
            inst ";"                                \
        "2:;"                                       \
        ".section .text;"                           \
    )

#define CLEAR(start, value, end)                    \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #start ";"                         \
        ".long " #end "-" #start ";"                \
        ".fill " #end "-" #start ", 1, " #value ";" \
        ".section .text;"                           \
    )

#define SJMP(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 2;"                                  \
        ".byte 0xEB;"                               \
        ".byte " #dst "-" #src " - 2;"              \
        ".section .text;"                           \
    )

#define LJMP(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 5;"                                  \
        ".byte 0xE9;"                               \
        ".long " #dst "-" #src " - 5;"              \
        ".section .text;"                           \
    )

#define CALL(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 5;"                                  \
        ".byte 0xE8;"                               \
        ".long " #dst "-" #src " - 5;"              \
        ".section .text;"                           \
    )
    
#define CALL_NOP(src, dst)                          \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 6;"                                  \
        ".byte 0xE8;"                               \
        ".long " #dst "-" #src " - 5;"              \
        ".byte 0x90;"                               \
        ".section .text;"                           \
    )

#define SETDWORD(dst, value)                        \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 4;"                                  \
        ".long " #value ";"                         \
        ".section .text;"                           \
    )

#define SETWORD(dst, value)                         \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 2;"                                  \
        ".short " #value ";"                        \
        ".section .text;"                           \
    )

#define SETBYTE(dst, value)                         \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 1;"                                  \
        ".byte " #value ";"                         \
        ".section .text;"                           \
    )
    
#define SETBYTES(addr, value)                       \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #addr ";"                          \
        ".long (2f - 1f);"                          \
        "1:;"                                       \
            ".ascii " #value ";"                    \
        "2:;"                                       \
        ".section .text;"                           \
    )

#define HOOK_1(src)                                 \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 5;"                                  \
        ".byte 0xE9;"                               \
        ".long _dest" #src "-" #src " - 5;"         \
        ".section .text;"                           \
    );                                              \
    EXTERN_C void __attribute__((naked)) dest##src()
    
#define HOOK_2(src, end)                            \
    CLEAR_INT((src + 5), end);                      \
    HOOK_1(src)

#define HOOK_X(x,A,B,FUNC, ...)  FUNC  
#define HOOK(...)         HOOK_X(,##__VA_ARGS__,    \
                               HOOK_2(__VA_ARGS__), \
                               HOOK_1(__VA_ARGS__), \
                               HOOK_0(__VA_ARGS__)  \
                               )

#define CLEAR_NOP(start, end) CLEAR(start, 0x90, end)
#define CLEAR_INT(start, end) CLEAR(start, 0xCC, end)
