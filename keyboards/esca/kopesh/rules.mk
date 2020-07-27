# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        #./lib/rgb_state_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c 

# MCU name
MCU = atmega32u4

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE ?= no	# Virtual DIP switch configuration
MOUSEKEY_ENABLE ?= no	# Mouse keys
EXTRAKEY_ENABLE ?= yes	# Audio control and System control
CONSOLE_ENABLE ?= no	# Console for debug
COMMAND_ENABLE ?= no    # Commands for debug and configuration
SLEEP_LED_ENABLE ?= no  # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
RGB_MATRIX_ENABLE = no
AUDIO_ENABLE ?= no
RGBLIGHT_ENABLE = yes
OLED_DRIVER_ENABLE = yes
QUANTUM_LIB_SRC += 	i2c.c 
SRC += ssd1306.c\
