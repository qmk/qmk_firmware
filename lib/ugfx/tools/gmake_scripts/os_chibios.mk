#
# This file is subject to the terms of the GFX License. If a copy of
# the license was not distributed with this file, you can obtain one at:
#
#             http://ugfx.io/license.html
#

# See readme.txt for the make API

# Requirements:
#
# CHIBIOS_VERSION               Which version of ChibiOS is this (2, 3, 4, 5, 16, git) - default is 16
#								Note the 'git' option is one we try to keep up to date with the ChibiOS master
#									If you find the 'git' option requires update please let us know.
#


ifeq ($(CHIBIOS_VERSION),2)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_2.mk
else ifeq ($(CHIBIOS_VERSION),3)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk
else ifeq ($(CHIBIOS_VERSION),4)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk
else ifeq ($(CHIBIOS_VERSION),5)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk
else ifeq ($(CHIBIOS_VERSION),16)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk
else ifeq ($(CHIBIOS_VERSION),git)
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_git.mk
else
  include $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk
endif
