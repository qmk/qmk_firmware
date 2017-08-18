

install-xorg-configuration:
	install -m 0664 90-$(KEYBOARD)-$(LAYOUT_ERGODOX).conf \
	    /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(LAYOUT_ERGODOX).conf
	install -m 0644 $(KEYBOARD)_$(LAYOUT_ERGODOX) \
	    /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(LAYOUT_ERGODOX)

uninstall-xorg-configuration:
	-rm -f /etc/X11/xorg.conf.d/90-$(KEYBOARD)-$(LAYOUT_ERGODOX).conf
	-rm -f /usr/share/X11/xkb/symbols/$(KEYBOARD)_$(LAYOUT_ERGODOX)
