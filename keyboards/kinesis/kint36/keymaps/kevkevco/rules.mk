BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = yes
MOUSEKEY_ENABLE = yes
NKRO_ENABLE = yes
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
FIRMWARE_FORMAT = hex
SWAP_HANDS_ENABLE = yes
NKRO_ENABLE = no 			# For QMK Apple Fn Key patch
APPLE_FN_ENABLE = yes       # Enable Apple Fn key functionality
DYNAMIC_MACRO_ENABLE = yes
CONSOLE_ENABLE = yes 		# Enable debugging

SRC += ./process_records.c

# Add features
SRC += features/caps_word.c 
SRC += features/select_word.c
SRC += features/num_word.c

# Tap dances
SRC += ./tap_dances.c


