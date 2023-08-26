# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

###### This block copyright 2023 Nathaniel Harward
#      https://github.com/nharward/miryoku_babel
FORCE_LAYOUT      = split_3x5_3
MIRYOKU_ALPHAS    = QWERTY
MIRYOKU_TAP       = QWERTY
MIRYOKU_NAV       = VI
###### end block copyright 2023 Nathaniel Harward

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

INTROSPECTION_KEYMAP_C = manna-harbour_miryoku.c # keymaps

include users/nharward/custom_rules.mk

include users/nharward/post_rules.mk
