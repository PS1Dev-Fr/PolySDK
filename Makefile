all: tools core

.PHONY: tools core tests clean

tools:
	make -C tools

core:
	make -C core

tests:
	make -C tests

clean:
	make -C tools clean
	make -C core clean
	make -C tests clean
