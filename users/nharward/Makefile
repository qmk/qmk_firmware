TARGETS = config.h custom_config.h manna-harbour_miryoku.h manna-harbour_miryoku.c rules.mk custom_rules.mk post_rules.mk miryoku_babel/miryoku_layer_list.h miryoku_babel/miryoku_layer_selection.h

all: $(TARGETS)

clean:
	rm $(TARGETS)

config.h: ../manna-harbour_miryoku/config.h config.h.patch Makefile
	cp $< $@
	patch -p0 $@ config.h.patch

custom_config.h: ../manna-harbour_miryoku/custom_config.h Makefile
	cp $< $@

manna-harbour_miryoku.h: ../manna-harbour_miryoku/manna-harbour_miryoku.h Makefile
	cp $< $@

manna-harbour_miryoku.c: ../manna-harbour_miryoku/manna-harbour_miryoku.c Makefile
	cp $< $@

rules.mk: ../manna-harbour_miryoku/rules.mk rules.mk.patch Makefile
	sed -e 's,users/manna-harbour_miryoku,users/nharward,g' < $< > $@
	patch -p0 $@ rules.mk.patch

custom_rules.mk: ../manna-harbour_miryoku/custom_rules.mk Makefile
	cp $< $@

post_rules.mk: ../manna-harbour_miryoku/post_rules.mk Makefile
	cp $< $@

miryoku_babel/miryoku_layer_list.h: ../manna-harbour_miryoku/miryoku_babel/miryoku_layer_list.h Makefile
	cp $< $@

miryoku_babel/miryoku_layer_selection.h: ../manna-harbour_miryoku/miryoku_babel/miryoku_layer_selection.h Makefile
	cp $< $@
