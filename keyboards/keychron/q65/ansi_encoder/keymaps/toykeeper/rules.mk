# Copyright 2022 Selene ToyKeeper
# SPDX-License-Identifier: GPL-2.0-or-later
# Compile options for ToyKeeper's Keychron Q65 layout
# (see users/toykeeper/rules.mk for the rest of the options)

# Let me assign events to the knob
ENCODER_MAP_ENABLE = yes

# my space bar keeps double-triggering, but all other keys are fine
DEBOUNCE_TYPE = sym_eager_pk

# make better use of that giant non-split backspace key
COMBO_ENABLE = yes
