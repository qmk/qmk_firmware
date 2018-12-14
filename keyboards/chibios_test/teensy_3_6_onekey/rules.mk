# project specific files
SRC =	matrix.c \
	    led.c

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
# - For Teensies, FAMILY = KINETIS and SERIES is either
#   KL2x (LC), K20x (3.0,3.1,3.2), or MK66F18 (3.6)
MCU_FAMILY = KINETIS
MCU_SERIES = MK66F18

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
# - NOTE: a custom ld script is needed for EEPROM on Teensy LC
# - LDSCRIPT =
#   - MKL26Z64 for Teensy LC
#   - MK20DX128 for Teensy 3.0
#   - MK20DX256 for Teensy 3.1 and 3.2
#   - MK66FX1M0 for Teensy 3.6
MCU_LDSCRIPT = MK66FX1M0

# Startup code to use
#  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
# - STARTUP =
#   - kl2x for Teensy LC
#   - k20x5 for Teensy 3.0
#   - k20x7 for Teensy 3.1 and 3.2
#   - MK66F18 for Teensy 3.6
MCU_STARTUP = MK66F18

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# - BOARD =
#   - PJRC_TEENSY_LC for Teensy LC
#   - PJRC_TEENSY_3 for Teensy 3.0
#   - PJRC_TEENSY_3_1 for Teensy 3.1 or 3.2
#   - PJRC_TEENSY_3_6 for Teensy 3.6
BOARD = PJRC_TEENSY_3_6

# Cortex version
# Teensy LC is cortex-m0plus; Teensy 3.x are cortex-m4
MCU  = cortex-m4

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
# I.e. 6 for Teensy LC; 7 for Teensy 3.x
ARMV = 7

CUSTOM_MATRIX = yes # Custom matrix file

SDC_ENABLE = no

VPATH += $(LIB_PATH)/chibios/os/various/shell
VPATH += $(LIB_PATH)/chibios/test/lib
VPATH += $(LIB_PATH)/chibios/test/rt/source/test
VPATH += $(LIB_PATH)/chibios-contrib/os/hal/include
VPATH += $(LIB_PATH)/chibios-contrib/os/hal/include/usbh/dev

ifeq ($(strip $(SDC_ENABLE)), yes)
  VPATH += fatfs/src
  SRC += fatfs/src/fatfs_diskio.c 
  SRC += fatfs/src/fatfs_syscall.c 
  SRC += fatfs/src/ff.c
  SRC += fatfs/src/ffunicode.c
  CSRC += fatfs/src
  INCDIR += fatfs/src
endif
