-include config.mk

INPUT       = EV_Nova.dat
OUTPUT      = EV\ Nova.exe
LDS         = EV_Nova.lds

LDFLAGS     = -Wl,--subsystem=windows -Wl,--disable-nxcompat -Wl,--disable-reloc-section -Wl,--enable-stdcall-fixup -static -nostdlib
ASFLAGS     = -Iinc
NFLAGS      = -Iinc -f elf
CFLAGS      = -Iinc -O2 -march=i486 -Wall -masm=intel
CXXFLAGS    = -Iinc -O2 -march=i486 -Wall -masm=intel

LIBS        = -luser32 -ladvapi32 -lshell32 -lmsvcrt-os -lkernel32 -lgdi32 -lcnc_ddraw

OBJS        = rsrc.o \
			  sym.o \
			  src/imports.o \
			  src/winmain.o \
			  src/debug-mode.o \
			  src/dynamic-resolution.o \
			  src/font-substitution-fix.o \
			  src/hotkeys.o \
			  src/hotkeys-x2.o \
			  src/hyperspace-effects.o \
			  src/macroman-fix.o \
			  src/map-borders.o \
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
			  src/k.o \
			  src/wine.o

CC          = i686-w64-mingw32-gcc
CXX         = i686-w64-mingw32-g++
AS          = i686-w64-mingw32-as
STRIP      ?= i686-w64-mingw32-strip
WINDRES    ?= i686-w64-mingw32-windres
PETOOL     ?= petool
NASM       ?= nasm

IMPORTDIR   =  1 0x18F000 7670
TLSDIR      =  9 0x0 0
IAT         = 12 0x0 0

all: $(OUTPUT)

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<

%.o: %.rc
	$(WINDRES) $(WFLAGS) $< $@

rsrc.o: $(INPUT)
	$(PETOOL) re2obj $< $@

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) -T $(LDS) -o "$@" $^ $(LIBS)
	$(PETOOL) setdd "$@" $(IMPORTDIR) || ($(RM) "$@" && exit 1)
	$(PETOOL) setdd "$@" $(TLSDIR) || ($(RM) "$@" && exit 1)
	$(PETOOL) setdd "$@" $(IAT) || ($(RM) "$@" && exit 1)
	$(PETOOL) setc "$@" .p_text 0x60000020 || ($(RM) "$@" && exit 1)
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
#	$(PETOOL) dump "$(INPUT)"
#	$(PETOOL) dump "$@"

clean:
	$(RM) $(OUTPUT) $(OBJS)
