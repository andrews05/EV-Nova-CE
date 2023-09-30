/* GNU ld linker script for "EV_Nova_mod.dat" */
start = 0x503F30;
ENTRY(start);
SECTIONS
{
    .text             0x401000 : { "EV_Nova_mod.dat"(.text) }
    .rdata            0x56B000 : { "EV_Nova_mod.dat"(.rdata) }
    .exc              0x574000 : { "EV_Nova_mod.dat"(.exc) }
    .data             0x575000 : { "EV_Nova_mod.dat"(.data) }
    .CRT              0x588000 : { "EV_Nova_mod.dat"(.CRT) }
    /DISCARD/                  : { "EV_Nova_mod.dat"(.rsrc) }
    FILL0             0x589000 : { . = . + 0x5534; }
    .idata            0x58F000 : { "EV_Nova_mod.dat"(.idata) }
    /DISCARD/                  : { "EV_Nova_mod.dat"(.bss) }
    .bss              0x591000 : { . = . + 0x2DFE13; }
    .reloc            0x871000 : { "EV_Nova_mod.dat"(.reloc) }

    /DISCARD/                  : { *(.drectve) *(.rdata$zzz) }
    .p_text      ALIGN(0x1000) : { *(.text) }
    .p_rdata     ALIGN(0x1000) : { *(.rdata) }
    .p_data      ALIGN(0x1000) : { *(.data) }
    .p_bss       ALIGN(0x1000) : { *(.bss) *(COMMON) }
    .rsrc        ALIGN(0x1000) : { *(.rsrc) }

    .patch       ALIGN(0x1000) : { *(.patch) }
}
