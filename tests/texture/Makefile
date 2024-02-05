TARGET = texture
TYPE = ps-exe

SRCS = ../../third_party/nugget/common/crt0/crt0.s \
texture.c

CPPFLAGS += -I../../third_party/psyq-iwyu/include
LDFLAGS += -L../../third_party/psyq/lib
LDFLAGS += -Wl,--start-group
LDFLAGS += -lapi -lc -lc2 -lcard -lcd -lcomb -lds -letc -lgpu -lgs -lgte -lgun -lhmd -lmath -lmcrd -lmcx -lpad -lpress -lsio -lsnd -lspu -ltap
LDFLAGS += -Wl,--end-group

include ../../third_party/nugget/common.mk

all: dep tools $(BINDIR)$(TARGET).$(TYPE) democd

tools:
	make -C ../../tools

%.tig: %.bmp
	../../tools/image/bmp2tig $< $@

%.tig: %.png
	../../tools/image/png2tig $< $@

democd: minou16.tig minou8.tig minou4.tig
	mkdir -p cd_root
	mv $(TARGET).$(TYPE) cd_root/PS1_DEMO.EXE
	cp minou*.tig cd_root
	mkisofs -o PS1_demo.iso -V PS1_DEMO -sysid PLAYSTATION cd_root
	../../tools/mkpsxiso PS1_demo.iso PS1_demo.bin ../../core/bin/infousa.dat
#	retroarch -L "$(HOME)/.config/retroarch/cores/pcsx_rearmed_libretro.so" PS1_demo.cue
