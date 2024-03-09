-include config.mk

INPUT       = EV_Nova.dat
OUTPUT      = EV\ Nova.exe
LDS         = EV_Nova.lds
GCCVERSION  = $(shell gcc --version | grep ^gcc | sed 's/^.* //g')
IMPORTS     = 0x18F000 7670
LDFLAGS     = --section-alignment=0x1000 --subsystem=windows --enable-stdcall-fixup --disable-dynamicbase --disable-nxcompat --disable-reloc-section
NFLAGS      = -f elf -Iinc/
CFLAGS      = -std=c99 -Iinc/ -O2 -march=i486 -Wall
CXXFLAGS    = -Iinc/ -O2 -march=i486 -Wall
LIBS        = -luser32 -ladvapi32 -lshell32 -lmsvcrt -lkernel32 -lgdi32 -lcnc_ddraw
#CXXLIBS     = =./lib/crt2.o -lstdc++ -lgcc -lpthread -lmingw32 -lmoldname -lmingwex -lgcc

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
			  src/ppat-decoder.o \
			  src/scale-dlog.o \
			  src/scale-grid.o \
			  src/scale-status-bar.o \
			  src/version.o \
			  src/widescreen-roid-fix.o \
			  src/windowed-toggle.o \
			  src/windows-keys-fix.o \
			  src/k.o

PETOOL     ?= petool
STRIP      ?= strip
NASM       ?= nasm
WINDRES    ?= windres

all: $(OUTPUT)

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

rsrc.o: $(INPUT)
	$(PETOOL) re2obj $(INPUT) $@

$(OUTPUT): $(LDS) $(INPUT) $(OBJS)
	$(LD) $(LDFLAGS) -T $(LDS) -o "$@" $(OBJS) $(CXXLIBS) $(LIBS) -L=./../lib/gcc/i686-w64-mingw32/$(GCCVERSION) -L=./lib/gcc/i686-w64-mingw32/$(GCCVERSION) -L./lib
ifneq (,$(IMPORTS))
	$(PETOOL) setdd "$@" 1 $(IMPORTS) || ($(RM) "$@" && exit 1)
endif
	$(PETOOL) setdd "$@" 9 0 0 || ($(RM) "$@" && exit 1)
	$(PETOOL) setdd "$@" 12 0 0 || ($(RM) "$@" && exit 1)
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
	$(PETOOL) dump "$@"

clean:
	$(RM) $(OUTPUT) $(OBJS)
