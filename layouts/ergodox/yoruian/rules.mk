

install-xorg-configuration:
	install -m 0664 90-$(KEYBOARD)-$(LAYOUT_ergodox).conf \
	    /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(LAYOUT_ergodox).conf
	install -m 0644 $(KEYBOARD)_$(LAYOUT_ergodox) \
	    /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(LAYOUT_ergodox)

uninstall-xorg-configuration:
	-rm -f /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(LAYOUT_ergodox).conf
	-rm -f /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(LAYOUT_ergodox)
