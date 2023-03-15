# Copyright 2022 Selene ToyKeeper
# SPDX-License-Identifier: GPL-2.0-or-later
# Compile options for ToyKeeper's Keyboardio Model01 layout
# (see users/toykeeper/rules.mk for the rest of the options)

# dang, this board can't use QMK's debouncing
#DEBOUNCE_TYPE = sym_eager_pk

# needed for the "Any" key, but it takes too much space
DEFERRED_EXEC_ENABLE = no

