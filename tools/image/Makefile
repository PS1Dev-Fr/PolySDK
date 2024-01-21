all: png2tig bmp2tig

.PHONY: clean

png2tig: png2tig.c upng.c upng.h
	gcc -gdwarf-4 -g3 -o $@ $@.c upng.c

bmp2tig: bmp2tig.c
	gcc -gdwarf-4 -g3 -o $@ $@.c

clean:
	-rm *.o png2tig bmp2tig
