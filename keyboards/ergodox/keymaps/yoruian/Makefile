ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

install-xorg-configuration:
	install -m 0664 90-$(KEYBOARD)-$(KEYMAP).conf \
	    /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(KEYMAP).conf
	install -m 0644 $(KEYBOARD)_$(KEYMAP) \
	    /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(KEYMAP)

uninstall-xorg-configuration:
	-rm -f /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(KEYMAP).conf
	-rm -f /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(KEYMAP)
