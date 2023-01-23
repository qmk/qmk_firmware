# Copyright 2022 Mega Mind (@megamind4089)
# SPDX-License-Identifier: GPL-2.0-or-later

# Default pin config of nucleo64_411re has most pins in input pull up mode

# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F411RE/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F411RE


# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
