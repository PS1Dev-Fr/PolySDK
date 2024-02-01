#rmake

#name executable
exe_name:bin/demo.elf

#command execute
cmd_execute:cd bin && bash compilationcd.sh 

#file .c or .cpp or folder : main.c;test.c , src;core;
add_folder:src/PolySDK/PS1
add_file:src/main.c;src/crt0.c
#--------compiler option------------
libdirs: 
includes:-Iinclude

#-O1 -O2 -O3 -Wall -Wextra -pedantic
options:-O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter
#-lnamelib 
libs:

cmd_precompiler:
cmd_compiler:$compiler -target mipsel-linux-gnu -march=mips2 -fno-builtin $options $includes -c $file -o $object
cmd_linker:$linker -target mipsel-linux-gnu -march=mips2 -nostartfiles -Wl,-Ttext=0x80010000 -Wl,-Tbss=0x80028000 -s $libdirs $object -o $exe_name $libs
cmd_postcompiler:llvm-objcopy --only-section=.text --only-section=.rodata --only-section=.data --only-section=.bss bin/demo.elf bin/demo.elf

#--------compiler config------------
compilerc:clang
compilercpp:clang
linker:clang