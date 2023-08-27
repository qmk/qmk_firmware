TARGETS = config.h keymap.c

all: $(TARGETS)

clean:
	rm $(TARGETS)

config.h: ../../../../../layouts/community/split_3x5_3/manna-harbour_miryoku/config.h .makefile
	cp $< $@
	patch -p0 $@ config.h.patch

keymap.c: ../../../../../layouts/community/split_3x5_3/manna-harbour_miryoku/keymap.c .makefile
	cp $< $@
