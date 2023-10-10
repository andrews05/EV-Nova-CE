
#define CLEAR(start, value, end)                    \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #start ";"                         \
        ".long " #end "-" #start ";"                \
        ".fill " #end "-" #start ", 1, " #value ";" \
    )

#define LJMP(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 5;"                                  \
        ".byte 0xE9;"                               \
        ".long " #dst "-" #src " - 5;"              \
    )

#define SJMP(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 2;"                                  \
        ".byte 0xEB;"                               \
        ".byte " #dst "-" #src " - 2;"              \
    )

#define CALL(src, dst)                              \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 5;"                                  \
        ".byte 0xE8;"                               \
        ".long " #dst "-" #src " - 5;"              \
    )
    
#define CALL_NOP(src, dst)                          \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #src ";"                           \
        ".long 6;"                                  \
        ".byte 0xE8;"                               \
        ".long " #dst "-" #src " - 5;"              \
        ".byte 0x90;"                               \
    )

#define SETDWORD(dst, value)                        \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 4;"                                  \
        ".long " #value ";"                         \
    )

#define SETWORD(dst, value)                         \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 2;"                                  \
        ".short " #value ";"                        \
    )

#define SETBYTE(dst, value)                         \
    __asm (                                         \
        ".section .patch,\"d0\";"                   \
        ".long " #dst ";"                           \
        ".long 1;"                                  \
        ".byte " #value ";"                         \
    )
