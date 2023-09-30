-include config.mk

INPUT       = EV_Nova
OUTPUT      = $(subst _, ,$(INPUT))
SUFFIXES    = mod stock
IMPORTS     = 0x18F000 7670
LDFLAGS     = --section-alignment=0x1000 --subsystem=windows --enable-stdcall-fixup
NFLAGS      = -f elf -Iinc/
CFLAGS      = -std=c99 -Iinc/ -O2 -march=i486

OBJS        = sym.o \
			  imports.o \
			  src/winmain.o \
              src/open-pilot.o

PETOOL     ?= petool
STRIP      ?= strip
NASM       ?= nasm
WINDRES    ?= windres

all: mod

$(SUFFIXES): %: $(INPUT)_%.exe
	cp "$<" "$(OUTPUT).exe" || copy "$<" "$(OUTPUT).exe"

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<
    
rsrc%.o: $(INPUT)%.dat
	$(PETOOL) re2obj "$<" $@

$(INPUT)%.exe: rsrc%.o $(OBJS)
	$(LD) $(LDFLAGS) -T "$(basename $@).lds" -o "$@" $< $(OBJS)
ifneq (,$(IMPORTS))
	$(PETOOL) setdd "$@" 1 $(IMPORTS) || ($(RM) "$@" && exit 1)
endif
	$(PETOOL) patch "$@" || ($(RM) "$@" && exit 1)
	$(STRIP) -R .patch "$@" || ($(RM) "$@" && exit 1)
	$(PETOOL) dump "$@"

clean:
	$(RM) $(wildcard $(INPUT)*.exe) "$(OUTPUT).exe" $(wildcard rsrc*.o) $(OBJS)

.SECONDARY: $(OBJS)
