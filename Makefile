all: tools tests

.PHONY: tools tests clean

tools:
	make -C tools

tests:
	make -C tests

clean:
	make -C tools clean
	make -C tests clean
