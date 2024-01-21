all: bin2c img2tig

.PHONY: img2tig clean

bin2c: bin2c.c
	gcc -O2 -o $@ $@.c

img2tig:
	make -C image

clean:
	-rm *.o bin2c
	make -C image clean
