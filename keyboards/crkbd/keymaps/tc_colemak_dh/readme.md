# Ergomech Corne Choc
Ergomech.store ships a keyboard that does not work by default with t
h The default keymap for cornelius doesn't necessarily work out of the box.

Old:
keyboards/foostan/cornelius/config.h
`#define EE_HANDS`
keyboards/foostan/cornelius/rules.mk
`SPLIT_KEYBOARD = yes`

Ergomech advice:
config.h:
`#define SPLIT_USB_DETECT`
