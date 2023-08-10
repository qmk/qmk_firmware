# SPDX-License-Identifier: GPL-2.0-or-later
# SPDX-FileCopyrightText: 2023 Mischback <mischback.dev@googlemail.com>
# SPDX-FileType: SOURCE

# The Keychron V4 features a DIP switch at the back that let the user switch
# between Mac and Windows layouts. As I run Linux anyways, this switch is not
# in use for me personally.
#
# While this feature is deactivated, the default selection of layers in
# Keychron's default keymap is not working and the first layer will be applied
# as the default to the keyboard.
#
# TODO: This might be used for something different...
#       See https://github.com/qmk/qmk_firmware/blob/master/docs/feature_dip_switch.md
#       THIS WILL ALSO ENABLE Keychron's default function for switching layers
#       depending on the position of the DIP, but that function is meant to be
#       overridden by keymap specific code (see ``keyboards/keychron/v4/v4.c``),
DIP_SWITCH_ENABLE = no

# The V4's keyboard code enables Mouse Keys (https://docs.qmk.fm/#/feature_mouse_keys),
# but that feature is not used in this keymap.
MOUSEKEY_ENABLE = no

# Enable Link Time Optimization (LTO) to reduce build size.
#
# Ref: https://docs.qmk.fm/#/squeezing_avr?id=squeezing-the-most-out-of-avr
LTO_ENABLE = yes
