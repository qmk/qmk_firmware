# Compile the shared ninjaPixel-ferris source file.
#
# QMK adds users/ninjaPixel-ferris/ to the build's search path (VPATH and the
# include path) whenever a keymap sets `USER_NAME := ninjaPixel-ferris`, so this
# relative filename resolves without a full path.
#
# Note: feature toggles (e.g. CAPS_WORD_ENABLE) live in the keymap's rules.mk
# at keyboards/ferris/keymaps/ninjaPixel/rules.mk, mirroring the layout of the
# users/ninjaPixel (Sofle) userspace.
SRC += ninjaPixel_ferris.c
