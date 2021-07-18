AUTO_SHIFT_ENABLE = no
#TAP_DANCE_ENABLE = yes 
LTO_ENABLE = yes
BOOTMAGIC_ENABLE = no        # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no         # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
#CONSOLE_ENABLE = no          # Console for debug(+400)
#COMMAND_ENABLE = no          # Commands for debug and configuration
#NKRO_ENABLE = no             # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
#BACKLIGHT_ENABLE = yes        # Enable keyboard backlight functionality
MIDI_ENABLE = no             # MIDI controls
AUDIO_ENABLE = no            # Audio output on port C6
UNICODE_ENABLE = yes          # Unicode
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID
#RGBLIGHT_ENABLE = no         # Enable WS2812 RGB underlight.
#API_SYSEX_ENABLE = no
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_DRIVER_ENABLE= yes     # OLED display

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = yes    # Breathing sleep LED during USB suspend

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
