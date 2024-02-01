#!/bin/sh

clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/main.c -o obj/src/main.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/crt0.c -o obj/src/crt0.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/syscall.c -o obj/src/PolySDK/PS1/syscall.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/BIOS.c -o obj/src/PolySDK/PS1/BIOS.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/PS1.c -o obj/src/PolySDK/PS1/PS1.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/elib.c -o obj/src/PolySDK/PS1/elib.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_mvram.c -o obj/src/PolySDK/PS1/Poly_mvram.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_event.c -o obj/src/PolySDK/PS1/Poly_event.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/PS1_GTE.c -o obj/src/PolySDK/PS1/PS1_GTE.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_io.c -o obj/src/PolySDK/PS1/Poly_io.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_gen.c -o obj/src/PolySDK/PS1/Poly_gen.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_ot.c -o obj/src/PolySDK/PS1/Poly_ot.o
clang -target mipsel-linux-gnu -march=mips2 -fno-builtin -O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter -Iinclude -c src/PolySDK/PS1/Poly_draw2D.c -o obj/src/PolySDK/PS1/Poly_draw2D.o

clang -target mipsel-linux-gnu -march=mips2 -nostartfiles -Wl,-Ttext=0x80010000 -Wl,-Tbss=0x80028000 -s   obj/src/crt0.o obj/src/main.o obj/src/PolySDK/PS1/syscall.o obj/src/PolySDK/PS1/BIOS.o obj/src/PolySDK/PS1/PS1.o obj/src/PolySDK/PS1/elib.o obj/src/PolySDK/PS1/Poly_mvram.o obj/src/PolySDK/PS1/Poly_event.o obj/src/PolySDK/PS1/PS1_GTE.o obj/src/PolySDK/PS1/Poly_io.o obj/src/PolySDK/PS1/Poly_gen.o obj/src/PolySDK/PS1/Poly_ot.o obj/src/PolySDK/PS1/Poly_draw2D.o  -o bin/demo.elf 

llvm-objcopy --only-section=.text --only-section=.rodata --only-section=.data --only-section=.bss bin/demo.elf bin/demo.elf
