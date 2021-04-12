# MCU name
MCU = STM32F303
DEBUG_MATRIX_SCAN_RATE_ENABLE = no
#Outputs matrix scan rate in QMK Toolbox

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = lite       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
TAP_DANCE_ENABLE = yes
WPM_ENABLE = yes

# OLED_DRIVER_ENABLE = yes

# RGB related
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = pwm
#PWM needs patch to <https://github.com/qmk/qmk_firmware/blob/master/platforms/chibios/GENERIC_STM`32_F303XC/configs/proton_c.mk>, otherwise defaults to bitbang.
#See develop PR <https://github.com/qmk/qmk_firmware/pull/11864>

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = yes    # Breathing sleep LED during USB suspend

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror    # for when Split Mirroring drops, it will maintain mirroring functionality
SERIAL_DRIVER = usart

# if firmware size over limit, try this option
# CFLAGS += -flto

SRC += ./lib/glcdfont.c \

DEFAULT_FOLDER = bakekujira/rev1

# ifeq ($strip $(BAKEKUJIRA)), yes)
# 	OPT_DEFS += -DBAKEKUJIRA
# endif
