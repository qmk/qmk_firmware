# Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
# 
# This file is part of qmk_firmware.
# 
# qmk_firmware is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# qmk_firmware is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.

SRC += jjerrell.c \
       process_records.c \
	   matrix_scans.c

LEADER_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif
SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no

DISABLE_SECRETS ?= no
ifneq ($(strip $(DISABLE_SECRETS)), yes)
	ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
        SRC += secrets.c
    endif
	ifeq ($(strip $(DISABLE_SECRETS)), lite)
		OPT_DEFS += -DNO_SECRETS
	endif
endif

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
	SRC += rgb_matrix_stuff.c
endif