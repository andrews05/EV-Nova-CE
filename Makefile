-include config.mk

INPUT       = EV_Nova.dat
OUTPUT      = EV\ Nova.exe
LDS         = EV_Nova.lds

IMPORTS     = 0x18F000 7670
LOADCONFIG  =
TLS         = 0x0 0
IAT         = 0x0 0

LDFLAGS     = -Wl,--subsystem=windows -Wl,--disable-nxcompat -Wl,--disable-reloc-section -Wl,--enable-stdcall-fixup -static -nostdlib
ASFLAGS     = -Iinc
NFLAGS      = -Iinc -f elf
CFLAGS      = -Iinc -O2 -march=i486 -Wall
CXXFLAGS    = -Iinc -O2 -march=i486 -Wall

LIBS        = -luser32 -ladvapi32 -lshell32 -lmsvcrt -lkernel32 -lgdi32 -lcnc_ddraw

OBJS        = rsrc.o \
			  sym.o \
			  imports.o \
			  src/winmain.o \
			  src/debug-mode.o \
			  src/dynamic-resolution.o \
			  src/font-substitution-fix.o \
			  src/hotkeys.o \
			  src/hyperspace-effects.o \
			  src/macroman-fix.o \
			  src/mission-bbs-title-fix.o \
			  src/no-encryption.o \
			  src/open-pilot-fix.o \
			  src/odd-width-fix.o \
			  src/particle-cap.o \
			  src/paths.o \
			  src/ppat-decoder.o \
			  src/scale-dlog.o \
			  src/scale-grid.o \
			  src/scale-status-bar.o \
			  src/version.o \
			  src/widescreen-roid-fix.o \
			  src/windowed-toggle.o \
			  src/windows-keys-fix.o \
			  src/k.o

CC          = i686-w64-mingw32-gcc
CXX         = i686-w64-mingw32-g++
WINDRES    ?= i686-w64-mingw32-windres
PETOOL     ?= petool
STRIP      ?= strip
NASM       ?= nasm

all: $(OUTPUT)

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.rc
	$(WINDRES) $(WINDRES_FLAGS) $< $@

rsrc.o: $(INPUT)
	$(PETOOL) re2obj $(INPUT) $@

$(OUTPUT): $(LDS) $(INPUT) $(OBJS)
	$(CXX) $(LDFLAGS) -T $(LDS) -o "$@" $(OBJS) $(LIBS) -L./lib
ifneq (,$(IMPORTS))
	$(PETOOL) setdd "$@" 1 $(IMPORTS) || ($(RM) "$@" && exit 1)
endif
	$(PETOOL) setdd "$@" 9 0 0 || ($(RM) "$@" && exit 1)
	$(PETOOL) setdd "$@" 12 0 0 || ($(RM) "$@" && exit 1)
	$(PETOOL) setc  "$@" .p_text 0x60000020 || ($(RM) "$@" && exit 1)
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
	$(PETOOL) dump "$@"

clean:
	$(RM) $(OUTPUT) $(OBJS)
