# MCU name
MCU = STM32F303

# Bootloader selection
BOOTLOADER = stm32-dfu

# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
NO_USB_STARTUP_CHECK = no   # Disable initialization only when usb is plugged in

CIE1931_CURVE = yes

LAYOUTS = 65_ansi

# project specific files
SRC +=  keyboards/wilba_tech/wt_main.c \
        keyboards/wilba_tech/wt_rgb_backlight.c \
        drivers/issi/is31fl3733.c \
        quantum/color.c
QUANTUM_LIB_SRC += drivers/chibios/i2c_master.c
