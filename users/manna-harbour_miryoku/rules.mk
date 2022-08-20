# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift

SRC += manna-harbour_miryoku.c # keymaps

include users/manna-harbour_miryoku/custom_rules.mk

include users/manna-harbour_miryoku/post_rules.mk
