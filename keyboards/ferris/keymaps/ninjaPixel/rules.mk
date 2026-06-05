# Point this keymap at the shared userspace in users/ninjaPixel-ferris/.
#
# This keymap directory is named "ninjaPixel" purely so the build command stays
# short (`make ferris/sweep:ninjaPixel`). USER_NAME otherwise defaults to the
# keymap name, which would (incorrectly) pick up the Sofle userspace at
# users/ninjaPixel/, so we override it explicitly. QMK reads this rules.mk
# before resolving the userspace, so the override takes effect.
USER_NAME := ninjaPixel-ferris

# Caps Word: type one capitalised word, then auto-disable on the next space or
# punctuation. Triggered by the CW_TOGG key on the FN layer. Hugely useful on a
# 34-key board for typing SCREAMING_SNAKE_CASE constants without holding Shift.
CAPS_WORD_ENABLE = yes
