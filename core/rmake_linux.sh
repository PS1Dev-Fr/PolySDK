#rmake

#name executable
exe_name:bin/demo

#command execute
cmd_execute:cd bin && ./demo

#file .c or .cpp or folder : main.c;test.c , src;core;
add_folder:src/PolySDK/PC
add_file:src/main.c
#--------compiler option------------
libdirs: 
includes:-Iinclude

#-O1 -O2 -O3 -Wall -Wextra -pedantic
options:-O1 -Wno-language-extension-token -Wall -Wextra -pedantic -Wno-unused-parameter
#-lnamelib 
libs:

cmd_precompiler:
cmd_compiler:$compiler $options $includes -c $file -o $object
cmd_linker:$linker -s $libdirs $object -o $exe_name $libs
cmd_postcompiler:

#--------compiler config------------
compilerc:clang
compilercpp:clang
linker:clang