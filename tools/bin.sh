#!/bin/sh
gcc bin2psx.c -O2 -s -o bin2psx
gcc bin2c.c -O2 -s -o bin2c

gcc mkpsxiso.c  -O2 -s -o mkpsxiso
gcc systemcnf.c -O2 -s -o systemcnf
gcc cdcat.c     -O2 -s -o cdcat
#gcc adpcm.c -O2 -s -o adpcm



