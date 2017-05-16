# project specific files
SRC =	matrix.c \
	    led.c

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
# - For Teensies, FAMILY = KINETIS and SERIES is either
#   KL2x (LC) or K20x (3.0,3.1,3.2).
MCU_FAMILY = KINETIS
MCU_SERIES = KL2x

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
# - NOTE: a custom ld script is needed for EEPROM on Teensy LC
# - LDSCRIPT =
#   - MKL26Z64 for Teensy LC
#   - MK20DX128 for Teensy 3.0
#   - MK20DX256 for Teensy 3.1 and 3.2
MCU_LDSCRIPT = MKL26Z64

# Startup code to use
#  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
# - STARTUP =
#   - kl2x for Teensy LC
#   - k20x5 for Teensy 3.0
#   - k20x7 for Teensy 3.1 and 3.2
MCU_STARTUP = kl2x

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# - BOARD =
#   - PJRC_TEENSY_LC for Teensy LC
#   - PJRC_TEENSY_3 for Teensy 3.0
#   - PJRC_TEENSY_3_1 for Teensy 3.1 or 3.2
BOARD = PJRC_TEENSY_LC

# Cortex version
# Teensy LC is cortex-m0plus; Teensy 3.x are cortex-m4
MCU  = cortex-m0plus

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
# I.e. 6 for Teensy LC; 7 for Teensy 3.x
ARMV = 6

MOUSEKEY_ENABLE ?= no       # Mouse keys
EXTRAKEY_ENABLE ?= yes      # Audio control and System control
CONSOLE_ENABLE ?= no        # Console for debug
COMMAND_ENABLE ?= yes       # Commands for debug and configuration
SLEEP_LED_ENABLE ?= yes     # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= no           # USB Nkey Rollover
CUSTOM_MATRIX ?= yes        # Custom matrix file
BOOTMAGIC_ENABLE ?= yes     # Virtual DIP switch configuration(+1000)
KEYBOARD_LOCK_ENABLE ?= no  # Allow locking of keyboard via magic key
BACKLIGHT_ENABLE ?= no      # Enable keyboard backlight functionality
MIDI_ENABLE ?= no           # MIDI controls
UNICODE_ENABLE ?= no        # Unicode
BLUETOOTH_ENABLE ?= no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE ?= no          # Audio output on port C6


ifndef QUANTUM_DIR
	include ../../../Makefile
endif