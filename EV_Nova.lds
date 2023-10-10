/* GNU ld linker script for EV_Nova.dat */
start = 0x503F30;
ENTRY(start);
SECTIONS
{
    .text             0x401000 : { EV_Nova.dat(.text) }
    .rdata            0x56B000 : { EV_Nova.dat(.rdata) }
    .exc              0x574000 : { EV_Nova.dat(.exc) }
    .data             0x575000 : { EV_Nova.dat(.data) }
    .CRT              0x588000 : { EV_Nova.dat(.CRT) }
    /DISCARD/                  : { EV_Nova.dat(.rsrc) }
    FILL0             0x589000 : { . = . + 0x5534; }
    .o_idata        0x58F000 : { EV_Nova.dat(.idata) }
    /DISCARD/                  : { EV_Nova.dat(.bss) }
    .bss              0x591000 : { . = . + 0x2DFE13; }
    /DISCARD/                  : { EV_Nova.dat(.reloc) }

    /DISCARD/                  : { *(.drectve) *(.rdata$zzz) }
    .idata       ALIGN(0x1000) : { *(.idata) }
    .p_text      ALIGN(0x1000) : { *(.text) }
    .p_rdata     ALIGN(0x1000) : { *(.rdata) }
    .p_data      ALIGN(0x1000) : { *(.data) }
    .p_bss       ALIGN(0x1000) : { *(.bss) *(COMMON) }
    .rsrc        ALIGN(0x1000) : { *(.rsrc) }

    .patch       ALIGN(0x1000) : { *(.patch) }
}
