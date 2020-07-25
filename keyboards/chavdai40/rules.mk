# project specific files

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F0xx

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = STM32F042x6

# Startup code to use
#  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f0xx

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = GENERIC_STM32_F042X6

# Cortex version
MCU  = cortex-m0

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6

# Vector table for application
# 0x00000000-0x00001000 area is occupied by bootlaoder.*/
# The CORTEX_VTOR... is needed only for MCHCK/Infinity KB
#OPT_DEFS = -DCORTEX_VTOR_INIT=0x00001000

# Options to pass to dfu-util when flashing
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
# DFU_SUFFIX_ARGS = -p DF11 -v 0483

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no				# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no				# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes				# Audio control and System control(+450)
CONSOLE_ENABLE = yes					# Console for debug(+400)
COMMAND_ENABLE = yes    				# Commands for debug and configuration
NKRO_ENABLE = no					# USB Nkey Rollover
BACKLIGHT_ENABLE = no				# Enable keyboard backlight functionality
NO_USB_STARTUP_CHECK = no         	# Disable initialization only when usb is plugged in
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs (+400)
# EXTRAFLAGS += -flto			# Link Time Optimization and disabling core functionality

