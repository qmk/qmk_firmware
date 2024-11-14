
VPATH += keyboards/womier/common
SRC += rdmctmzt_common.c
SRC += quantum/dynamic_keymap.c
SRC += three_mode.c
SRC += user_battery.c
SRC += user_eeprom.c
SRC += user_emi.c
SRC += user_led_custom.c
SRC += user_spi.c
SRC += user_system.c

VPATH += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md
# SRC += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md/md_adc.c
SRC += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md/md_spi.c

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = FS026

# Cortex version
MCU = cortex-m0

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6

## chip/board settings
# - the next two should match the directories in
#   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
#   OR
#   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = ES32
MCU_SERIES = FS026

# Linker script to use
# - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
#   or <keyboard_dir>/ld/
MCU_LDSCRIPT ?= FS026

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP ?= FS026

USE_FPU ?= no

EEPROM_DRIVER = custom
NO_USB_STARTUP_CHECK = yes
BLUETOOTH_CUSTOM = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

