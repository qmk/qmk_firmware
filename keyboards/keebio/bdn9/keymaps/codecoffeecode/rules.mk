MOUSEKEY_ENABLE = yes
ifneq (, $(findstring rev1, $(KEYBOARD)))
  CONVERT_TO=proton_c
endif
