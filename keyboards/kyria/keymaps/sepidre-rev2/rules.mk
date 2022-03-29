OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = no    # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes     # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION = no
TAP_DANCE_ENABLE = no
WPM_ENABLE = yes
LEADER_ENABLE = yes

STENO_ENABLE = no
BOOTMAGIC_ENABLE =no
TERMINAL_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_LOCK_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
VELOCIKEY_ENABLE = no

COMMAND_ENABLE = no         # Commands for debug and configuration
UNICODE_ENABLE   = no  # Unicode
SWAP_HANDS_ENABLE= no  # Allow swapping hands of keyboard
MIDI_ENABLE = no            # MIDI controls
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
RAW_ENABLE = yes
# If you want to change the display of OLED, you need to change here
SRC +=  logo_reader.c \
		layer.c
EXTRAFLAGS += -flto
