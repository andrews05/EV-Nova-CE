/* GNU ld linker script for EV_Nova.dat */

/* Default linker script, for normal executables */
/* Copyright (C) 2014-2023 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */

ENTRY(_WinMainCRTStartup);
SEARCH_DIR("/usr/i686-w64-mingw32/lib");
SEARCH_DIR("=/w64devkit/i686-w64-mingw32/lib");
SEARCH_DIR("=/w64devkit/lib");
SEARCH_DIR("=/mingw32/i686-w64-mingw32/lib");
SEARCH_DIR("=/mingw32/lib");
SEARCH_DIR("=/usr/local/lib");
SEARCH_DIR("=/lib");
SEARCH_DIR("=/usr/lib");
SEARCH_DIR("./lib");
SECTIONS
{
    .text             0x401000 : { EV_Nova.dat(.text) }
    .rdata            0x56B000 : { EV_Nova.dat(.rdata) }
    .exc              0x574000 : { EV_Nova.dat(.exc) }
    .data             0x575000 : { EV_Nova.dat(.data) }

  .CRT 0x588000 :
  {
    EV_Nova.dat(.CRT)
    ___crt_xc_start__ = . ;
    KEEP (*(SORT(.CRT$XC*)))  /* C initialization */
    ___crt_xc_end__ = . ;
    ___crt_xi_start__ = . ;
    KEEP (*(SORT(.CRT$XI*)))  /* C++ initialization */
    ___crt_xi_end__ = . ;
    ___crt_xl_start__ = . ;
    KEEP (*(SORT(.CRT$XL*)))  /* TLS callbacks */
    /* ___crt_xl_end__ is defined in the TLS Directory support code */
    ___crt_xp_start__ = . ;
    KEEP (*(SORT(.CRT$XP*)))  /* Pre-termination */
    ___crt_xp_end__ = . ;
    ___crt_xt_start__ = . ;
    KEEP (*(SORT(.CRT$XT*)))  /* Termination */
    ___crt_xt_end__ = . ;
  }

    /DISCARD/                  : { EV_Nova.dat(.rsrc) }
    FILL0             0x589000 : { . = . + 0x5534; }
    .o_idata          0x58F000 : { EV_Nova.dat(.idata) }
    /DISCARD/                  : { EV_Nova.dat(.bss) }
    .bss              0x591000 : { . = . + 0x2DFE13; }
    /DISCARD/                  : { EV_Nova.dat(.reloc) }

    /DISCARD/                  : { *(.rdata$zzz) }

  .p_text BLOCK(__section_alignment__) :
  {
    KEEP (*(SORT_NONE(.init)))
    *(.text)
    *(SORT(.text$*))
     *(.text.*)
     *(.gnu.linkonce.t.*)
    *(.glue_7t)
    *(.glue_7)
       /* Note: we always define __CTOR_LIST__ and ___CTOR_LIST__ here,
          we do not PROVIDE them.  This is because the ctors.o startup
          code in libgcc defines them as common symbols, with the
          expectation that they will be overridden by the definitions
          here.  If we PROVIDE the symbols then they will not be
          overridden and global constructors will not be run.
          See PR 22762 for more details.

          This does mean that it is not possible for a user to define
          their own __CTOR_LIST__ and __DTOR_LIST__ symbols; if they do,
          the content from those variables are included but the symbols
          defined here silently take precedence.  If they truly need to
          be redefined, a custom linker script will have to be used.
          (The custom script can just be a copy of this script with the
          PROVIDE() qualifiers added).
          In particular this means that ld -Ur does not work, because
          the proper __CTOR_LIST__ set by ld -Ur is overridden by a
          bogus __CTOR_LIST__ set by the final link.  See PR 46.  */
       ___CTOR_LIST__ = .;
       __CTOR_LIST__ = .;
       LONG (-1);
       KEEP(*(.ctors));
       KEEP(*(.ctor));
       KEEP(*(SORT_BY_NAME(.ctors.*)));
       LONG (0);
       /* See comment about __CTOR_LIST__ above.  The same reasoning
          applies here too.  */
       ___DTOR_LIST__ = .;
       __DTOR_LIST__ = .;
       LONG (-1);
       KEEP(*(.dtors));
       KEEP(*(.dtor));
       KEEP(*(SORT_BY_NAME(.dtors.*)));
       LONG (0);
    KEEP (*(SORT_NONE(.fini)))
    /* ??? Why is .gcc_exc here?  */
     *(.gcc_exc)
    PROVIDE (etext = .);
    PROVIDE (_etext = .);
     KEEP (*(.gcc_except_table))
  }
  
  /* The Cygwin32 library uses a section to avoid copying certain data
     on fork.  This used to be named ".data".  The linker used
     to include this between __data_start__ and __data_end__, but that
     breaks building the cygwin32 dll.  Instead, we name the section
     ".data_cygwin_nocopy" and explicitly include it after __data_end__. */
  .p_data BLOCK(__section_alignment__) :
  {
    __data_start__ = . ;
    *(.data)
    *(.data2)
    *(SORT(.data$*))
    KEEP(*(.jcr))
    __data_end__ = . ;
    *(.data_cygwin_nocopy)
  }
  .p_rdata BLOCK(__section_alignment__) :
  {
    *(.rdata)
             *(SORT(.rdata$*))
    . = ALIGN(4);
    __rt_psrelocs_start = .;
    KEEP(*(.rdata_runtime_pseudo_reloc))
    __rt_psrelocs_end = .;
  }
  __rt_psrelocs_size = __rt_psrelocs_end - __rt_psrelocs_start;
  ___RUNTIME_PSEUDO_RELOC_LIST_END__ = .;
  __RUNTIME_PSEUDO_RELOC_LIST_END__ = .;
  ___RUNTIME_PSEUDO_RELOC_LIST__ = . - __rt_psrelocs_size;
  __RUNTIME_PSEUDO_RELOC_LIST__ = . - __rt_psrelocs_size;
  .eh_fram BLOCK(__section_alignment__) :
  {
    KEEP(*(.eh_frame*))
  }
  .pdata BLOCK(__section_alignment__) :
  {
    KEEP(*(.pdata*))
  }
  .p_bss BLOCK(__section_alignment__) :
  {
    __bss_start__ = . ;
    *(.bss)
    *(COMMON)
    __bss_end__ = . ;
  }
  .p_edata BLOCK(__section_alignment__) :
  {
    *(.edata)
  }
  /DISCARD/ :
  {
    *(.debug$S)
    *(.debug$T)
    *(.debug$F)
     *(.drectve)
     *(.note.GNU-stack)
     *(.gnu.lto_*)
  }
  .idata BLOCK(__section_alignment__) :
  {
    /* This cannot currently be handled with grouped sections.
        See pe.em:sort_sections.  */

    /* ADVAPI32.dll */
    LONG (0x18F104); LONG (0x0); LONG (0x0); LONG (0x18FB08); LONG (0x18F5C8);

    /* COMCTL32.dll */
    LONG (0x18F124); LONG (0x0); LONG (0x0); LONG (0x18FB16); LONG (0x18F5E8);

    /* GDI32.dll */
    LONG (0x18F12C); LONG (0x0); LONG (0x0); LONG (0x18FFAA); LONG (0x18F5F0);

    /* KERNEL32.dll */
    LONG (0x18F24C); LONG (0x0); LONG (0x0); LONG (0x1906D8); LONG (0x18F710);

    /* OPENGL32.dll */
    LONG (0x18F3D8); LONG (0x0); LONG (0x0); LONG (0x1906E6); LONG (0x18F89C);

    /* SHELL32.dll */
    LONG (0x18F3DC); LONG (0x0); LONG (0x0); LONG (0x190706); LONG (0x18F8A0);

    /* USER32.dll */
    LONG (0x18F3E4); LONG (0x0); LONG (0x0); LONG (0x190C90); LONG (0x18F8A8);

    /* VERSION.dll */
    LONG (0x18F52C); LONG (0x0); LONG (0x0); LONG (0x190C9C); LONG (0x18F9F0);

    /* WINMM.dll */
    LONG (0x18F530); LONG (0x0); LONG (0x0); LONG (0x190D7E); LONG (0x18F9F4);

    /* WSOCK32.dll */
    LONG (0x18F560); LONG (0x0); LONG (0x0); LONG (0x190D88); LONG (0x18FA24);

    /* comdlg32.dll */
    LONG (0x18F5B0); LONG (0x0); LONG (0x0); LONG (0x190DC0); LONG (0x18FA74);

    /* iconv.dll */
    LONG (0x18F5BC); LONG (0x0); LONG (0x0); LONG (0x190DEC); LONG (0x18FA80);

    KEEP (SORT(*)(.idata$2))
    KEEP (SORT(*)(.idata$3))
    /* These zeroes mark the end of the import list.  */
    LONG (0); LONG (0); LONG (0); LONG (0); LONG (0);
    KEEP (SORT(*)(.idata$4))
    __IAT_start__ = .;
    KEEP (SORT(*)(.idata$5))
    __IAT_end__ = .;
    KEEP (SORT(*)(.idata$6))
    KEEP (SORT(*)(.idata$7))
  }
  /* Windows TLS expects .tls$AAA to be at the start and .tls$ZZZ to be
     at the end of section.  This is important because _tls_start MUST
     be at the beginning of the section to enable SECREL32 relocations with TLS
     data.  */
  .p_tls BLOCK(__section_alignment__) :
  {
    ___tls_start__ = . ;
    KEEP (*(.tls$AAA))
    KEEP (*(.tls))
    KEEP (*(.tls$))
    KEEP (*(SORT(.tls$*)))
    KEEP (*(.tls$ZZZ))
    ___tls_end__ = . ;
  }
  .endjunk BLOCK(__section_alignment__) :
  {
    /* end is deprecated, don't use it */
    PROVIDE (end = .);
    PROVIDE ( _end = .);
     __end__ = .;
  }
  .rsrc BLOCK(__section_alignment__) : SUBALIGN(4)
  {
    KEEP (*(.rsrc))
    KEEP (*(.rsrc$*))
  }
  .p_reloc BLOCK(__section_alignment__) :
  {
    *(.reloc)
  }
  .stab BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.stab)
  }
  .stabstr BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.stabstr)
  }
    
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section.  Unlike other targets that fake this by putting the
     section VMA at 0, the PE format will not allow it.  */
  /* DWARF 1.1 and DWARF 2.  */
  .debug_aranges BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_aranges)
  }
  .zdebug_aranges BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_aranges)
  }
  .debug_pubnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_pubnames)
  }
  .zdebug_pubnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_pubnames)
  }
  /* DWARF 2.  */
  .debug_info BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_info .gnu.linkonce.wi.*)
  }
  .zdebug_info BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_info .zdebug.gnu.linkonce.wi.*)
  }
  .debug_abbrev BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_abbrev)
  }
  .zdebug_abbrev BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_abbrev)
  }
  .debug_line BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_line)
  }
  .zdebug_line BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_line)
  }
  .debug_frame BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_frame*)
  }
  .zdebug_frame BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_frame*)
  }
  .debug_str BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_str)
  }
  .zdebug_str BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_str)
  }
  .debug_loc BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_loc)
  }
  .zdebug_loc BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_loc)
  }
  .debug_macinfo BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_macinfo)
  }
  .zdebug_macinfo BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_macinfo)
  }
  /* SGI/MIPS DWARF 2 extensions.  */
  .debug_weaknames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_weaknames)
  }
  .zdebug_weaknames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_weaknames)
  }
  .debug_funcnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_funcnames)
  }
  .zdebug_funcnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_funcnames)
  }
  .debug_typenames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_typenames)
  }
  .zdebug_typenames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_typenames)
  }
  .debug_varnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_varnames)
  }
  .zdebug_varnames BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_varnames)
  }
  /* DWARF 3.  */
  .debug_pubtypes BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_pubtypes)
  }
  .zdebug_pubtypes BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_pubtypes)
  }
  .debug_ranges BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_ranges)
  }
  .zdebug_ranges BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_ranges)
  }
  /* DWARF 4.  */
  .debug_types BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_types .gnu.linkonce.wt.*)
  }
  .zdebug_types BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_types .gnu.linkonce.wt.*)
  }
  /* DWARF 5.  */
  .debug_addr BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_addr)
  }
  .zdebug_addr BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_addr)
  }
  .debug_line_str BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_line_str)
  }
  .zdebug_line_str BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_line_str)
  }
  .debug_loclists BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_loclists)
  }
  .zdebug_loclists BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_loclists)
  }
  .debug_macro BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_macro)
  }
  .zdebug_macro BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_macro)
  }
  .debug_names BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_names)
  }
  .zdebug_names BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_names)
  }
  .debug_rnglists BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_rnglists)
  }
  .zdebug_rnglists BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_rnglists)
  }
  .debug_str_offsets BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_str_offsets)
  }
  .zdebug_str_offsets BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_str_offsets)
  }
  .debug_sup BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_sup)
  }
  /* For Go and Rust.  */
  .debug_gdb_scripts BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.debug_gdb_scripts)
  }
  .zdebug_gdb_scripts BLOCK(__section_alignment__) (NOLOAD) :
  {
    *(.zdebug_gdb_scripts)
  }
  .patch BLOCK(__section_alignment__) : 
  { 
    *(.patch)
  }
}

