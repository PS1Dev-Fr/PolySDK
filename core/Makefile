TARGET = demo
TYPE = ps-exe

SRCS = 	src/crt0.c \
		src/main.c \
		src/PolySDK/PS1/BIOS.c \
		src/PolySDK/PS1/elib.c \
		src/PolySDK/PS1/Poly_draw2D.c \
		src/PolySDK/PS1/Poly_event.c \
		src/PolySDK/PS1/Poly_gen.c \
		src/PolySDK/PS1/Poly_io.c \
		src/PolySDK/PS1/Poly_mvram.c \
		src/PolySDK/PS1/Poly_ot.c \
		src/PolySDK/PS1/PS1_GTE.c \
		src/PolySDK/PS1/PS1.c \
		src/PolySDK/PS1/syscall.c

CPPFLAGS += -Iinclude

include ../third_party/nugget/common.mk

all: dep $(BINDIR)$(TARGET).$(TYPE) democd

democd:
	mkdir -p bin/cd_root
	mv $(TARGET).$(TYPE) bin/cd_root/PS1_DEMO.EXE
	mkisofs -o bin/PS1_demo.iso -V PS1_DEMO -sysid PLAYSTATION bin/cd_root
	../tools/mkpsxiso bin/PS1_demo.iso bin/PS1_demo.bin bin/infousa.dat
#	retroarch -L "$(HOME)/.config/retroarch/cores/pcsx_rearmed_libretro.so" bin/PS1_demo.cue
