TARGETS = config.h custom_config.h manna-harbour_miryoku.h manna-harbour_miryoku.c rules.mk custom_rules.mk post_rules.mk miryoku_babel/miryoku_layer_list.h miryoku_babel/miryoku_layer_selection.h

all: $(TARGETS)
	$(MAKE) -C ../../keyboards/crkbd/rev1/keymaps/nharward -f .makefile
	$(MAKE) -C ../../keyboards/moonlander/keymaps/nharward -f .makefile

clean:
	rm $(TARGETS)

config.h: ../manna-harbour_miryoku/config.h .makefile
	cp $< $@

custom_config.h: ../manna-harbour_miryoku/custom_config.h .makefile
	cp $< $@

manna-harbour_miryoku.h: ../manna-harbour_miryoku/manna-harbour_miryoku.h .makefile
	cp $< $@

manna-harbour_miryoku.c: ../manna-harbour_miryoku/manna-harbour_miryoku.c .makefile
	cp $< $@

rules.mk: ../manna-harbour_miryoku/rules.mk rules.mk.patch .makefile
	sed -e 's,users/manna-harbour_miryoku,users/nharward,g' < $< > $@
	patch -p0 $@ rules.mk.patch

custom_rules.mk: ../manna-harbour_miryoku/custom_rules.mk .makefile
	cp $< $@

post_rules.mk: ../manna-harbour_miryoku/post_rules.mk .makefile
	cp $< $@

miryoku_babel/miryoku_layer_list.h: ../manna-harbour_miryoku/miryoku_babel/miryoku_layer_list.h .makefile
	cp $< $@

miryoku_babel/miryoku_layer_selection.h: ../manna-harbour_miryoku/miryoku_babel/miryoku_layer_selection.h .makefile
	cp $< $@
