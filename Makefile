-include config.mk

INPUT       = EV_Nova.dat
OUTPUT      = EV\ Nova.exe
LDS         = EV_Nova.lds
IMPORTS     = 0x18F000 7670
LDFLAGS     = --section-alignment=0x1000 --subsystem=windows --enable-stdcall-fixup --disable-dynamicbase --disable-nxcompat --disable-reloc-section
NFLAGS      = -f elf -Iinc/
CFLAGS      = -std=c99 -Iinc/ -O2 -march=i486 
CXXFLAGS    = -Iinc/ -O2 -march=i486 
LIBS        = -luser32 -ladvapi32 -lshell32 -lmsvcrt -lkernel32

BASEOBJS    = rsrc.o \
			  sym.o \
			  imports.o \
			  src/winmain.o \
			  src/macroman-fix.o \
			  src/windows-keys-fix.o \
			  src/radar-interference-fix.o \
			  src/open-pilot-fix.o \
			  src/font-substitution-fix.o \
			  src/widescreen-roid-fix.o \
			  src/dlog-size-fix.o \
			  src/dynamic-resolution.o \
			  src/hotkeys.o
HERETIC     = src/HERETiC.o
OBJS        = $(BASEOBJS) $(HERETIC)

PETOOL     ?= petool
STRIP      ?= strip
NASM       ?= nasm
WINDRES    ?= windres

all: $(OUTPUT)

stock: OBJS = $(BASEOBJS)
stock: $(OUTPUT)

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<
    
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
    
rsrc.o: $(INPUT)
	$(PETOOL) re2obj $(INPUT) $@

$(OUTPUT): $(LDS) $(INPUT) $(OBJS)
	$(LD) $(LDFLAGS) -T $(LDS) -o "$@" $(OBJS) $(LIBS)
ifneq (,$(IMPORTS))
	$(PETOOL) setdd "$@" 1 $(IMPORTS) || ($(RM) "$@" && exit 1)
endif
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
	$(PETOOL) dump "$@"

clean:
	$(RM) $(OUTPUT) $(OBJS)
