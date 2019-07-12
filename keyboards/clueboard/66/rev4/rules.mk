LAYOUTS = 66_ansi 66_iso

## chip/board settings
MCU_FAMILY = STM32
MCU_SERIES = STM32F3xx
MCU_LDSCRIPT = STM32F303xC
MCU_STARTUP = stm32f3xx
BOARD = GENERIC_STM32_F303XC
MCU  = cortex-m4
ARMV = 7
USE_FPU = yes
OPT_DEFS =

# Options to pass to dfu-util when flashing
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = yes
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes   # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes   # Audio control and System control(+450)
CONSOLE_ENABLE = yes    # Console for debug(+400)
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no    # Enable keyboard underlight functionality
MIDI_ENABLE = no        # MIDI controls
UNICODE_ENABLE = no     # Unicode
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = yes
