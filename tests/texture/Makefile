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

texture.c: tools minou16.h minou8.h minou4.h

tools:
	make -C ../../tools

%.tig: %.png
	../../tools/image/png2tig $< $@

%.tig: %.bmp
	../../tools/image/bmp2tig $< $@

%.h: %.tig
	../../tools/bin2c $(patsubst %.h,%,$@) < $< > $@
