#!/bin/bash
export PATH=$PATH:/usr/local/SDK/PS1/psxsdk/bin/
mkdir -p cd_root
elf2exe demo.elf cd_root/PS1_demo.exe
#cp PS1_demo.exe cd_root
#rm PS1_demo.exe
#systemcnf PS1_demo.exe > cd_root/system.cnf
mkisofs -o PS1_demo.iso -V PS1_demo -sysid PLAYSTATION cd_root
mkpsxiso PS1_demo.iso PS1_demo.bin infousa.dat

pcsxr -cdfile PS1_demo.bin


#bchunk Arc_The_Lad_FR.bin Arc_The_Lad_FR.cue Arc_The_Lad_FR.iso