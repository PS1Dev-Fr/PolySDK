all: demo democd

ELF = bin/demo.elf
EXE = bin/demo.exe
PSEXE = bin/cd_root/PS1_DEMO.EXE

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

OBJS = $(SRCS:%.c=%.o)

# conversion makefile de .vscode/compile.sh
CPPFLAGS += -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude
LDFLAGS += -target mipsel-linux-gnu -march=mips2 -nostartfiles -Wl,-Ttext=0x80010000 -Wl,-Tbss=0x80028000

%.o: %.c
	clang $(CPPFLAGS) -c $< -o $@

demo: $(OBJS)
	clang $(LDFLAGS) -s $(OBJS) -o $(ELF)
	llvm-objcopy-14 --only-section=.text --only-section=.rodata --only-section=.data --only-section=.bss $(ELF) $(EXE)

# conversion makefile de bin/compilationcd.sh
democd: demo
	mkdir -p bin/cd_root
	../tools/elf2exe $(EXE) $(PSEXE)
	mkisofs -o bin/PS1_demo.iso -V PS1_DEMO -sysid PLAYSTATION bin/cd_root
	../tools/mkpsxiso bin/PS1_demo.iso bin/PS1_demo.bin bin/infousa.dat
#	retroarch -L "$(HOME)/.config/retroarch/cores/pcsx_rearmed_libretro.so" bin/PS1_demo.cue

clean:
	-rm $(OBJS) $(ELF) $(EXE) $(PSEXE)
