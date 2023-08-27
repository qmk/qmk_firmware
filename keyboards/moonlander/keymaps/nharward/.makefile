TARGETS = config.h keymap.c

all: $(TARGETS)

clean:
	rm $(TARGETS)

config.h: ../manna-harbour_miryoku/config.h .makefile
	cp $< $@

keymap.c: ../manna-harbour_miryoku/keymap.c .makefile
	cp $< $@
