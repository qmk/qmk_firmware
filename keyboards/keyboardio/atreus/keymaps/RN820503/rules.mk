
VPATH += keyboards/gboards/ # using gboards combo code: see https://combos.gboards.ca/

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite

EXTRAKEY_ENABLE = yes       # Audio control and System control
LTO_ENABLE = yes			# link time optimisation
CONSOLE_ENABLE = yes        # Console for debug
NKRO_ENABLE = yes           # Enable N-Key Rollover
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE =  no

AUTO_SHIFT_ENABLE = no
MOUSEKEY_ENABLE = no       	# Mouse keys
COMMAND_ENABLE = no			# Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
SPACE_CADET_ENABLE = no		# parentheses when tapping left/right mods
GRAVE_ESC_ENABLE = no		# superimpose the grave (`) and Escape keys
MAGIC_ENABLE = no			# NKRO toggling, mod swapping, etc
UNICODE_ENABLE = no        	# Unicode
