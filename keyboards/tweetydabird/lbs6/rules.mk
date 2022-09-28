# Copyright 2021 Your Name (@yourgithub)
# SPDX-License-Identifier: GPL-2.0-or-later

# Bootloader selection
BOOTLOADER = caterina		#Pro Micro
#BOOTLOADER = atmel-dfu 	#Elite C

# Not yet supported in info.json
BOOTMAGIC_ENABLE = yes
ENCODER_ENABLE = yes

# Link Time Optimization
# Not yet supported in info.json
LTO_ENABLE = yes			# Optimize size at compile (takes longer time)