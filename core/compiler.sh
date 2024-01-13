#!/bin/sh
#clang -target mipsel-linux-gnu -march=mips2 -O1 -S main.c
#clang -target mips-linux-gnu -march=mips2 -nostartfiles _start.s -o _start.o

clang -target mipsel-linux-gnu -march=mips2 -O1 -c src/start.c -o obj/start.o -Iinclude
clang -target mipsel-linux-gnu -march=mips2 -O1 -c src/main.c  -o obj/main.o -Iinclude


clang -target mipsel-linux-gnu -march=mips2 -O1 -c src/elibc/print.c  -o obj/print.o -Iinclude

clang -target mipsel-linux-gnu -march=mips2 -O1 -c src/PolySDK/PS1/Poly_init.c  -o obj/Poly_init.o -Iinclude
clang -target mipsel-linux-gnu -march=mips2 -O1 -c src/PolySDK/PS1/PS1.c  -o obj/PS1.o -Iinclude

clang -target mipsel-linux-gnu -march=mips2 -nostartfiles -Wl,-Ttext=0x10000,-Tdata=0x20000   -s obj/start.o obj/print.o obj/PS1.o obj/Poly_init.o obj/main.o -o bin/GAME.elf

llvm-objcopy --only-section=.text --only-section=.rodata --only-section=.data --only-section=.bss bin/GAME.elf bin/GAME.elf
llvm-objcopy -O binary bin/GAME.elf bin/GAME.bin
bin/bin2psx bin/GAME.bin bin/GAME.EXE
#readelf -S GAME.elf
#ghex GAME.elf
#llvm-objcopy --only-section=.text --only-section=.rodata --only-section=.data --only-section=.bss GAME.elf GAME.elf

#llvm-objcopy --only-section=.text   --output-target=binary GAME.elf GAMEt.bin
#llvm-objcopy --only-section=.rodata --output-target=binary GAME.elf GAMErd.bin
#llvm-objcopy --only-section=.data   --output-target=binary GAME.elf GAMEd.bin


#./elf2exe GAME.bin GAME.EXE -mark_eur





