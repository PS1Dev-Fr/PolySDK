all: bin2c bin2psx mkpsxiso img2tig

.PHONY: img2tig clean

bin2c: bin2c.c
	gcc -O2 -o $@ $@.c

bin2psx: bin2psx.c
	gcc -O2 -o $@ $@.c

mkpsxiso: mkpsxiso.c
	gcc -O2 -o $@ $@.c

img2tig:
	make -C image

clean:
	-rm *.o bin2c
	make -C image clean
