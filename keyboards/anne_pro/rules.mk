## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32L1xx
# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
MCU_LDSCRIPT = STM32L151
# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32l1xx
# board to use
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = STM32L151_ANNE_PRO
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m3
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

# Extra arguments for dfu-util to flash to the correct location
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08004000

# Extra source files
SRC += anne_pro_lighting.c

# Build Options
#   comment out to disable the options.
#
MOUSEKEY_ENABLE = no  # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
NKRO_ENABLE = yes     # USB Nkey Rollover
