# Enable VIAL support when merged into QMK
# ENABLE_VIAL = yes

# Setup QMK features
BOOTMAGIC_ENABLE = yes	# Enable QMK_Boot on plug-in
DIP_SWITCH_ENABLE = no	# Won't use for now
COMMAND_ENABLE = no		# Won't use for now
CONSOLE_ENABLE = no		# Won't use for now
ENCODER_ENABLE = no		# Won't use for now
GRAVE_ESC_ENABLE = no	# Not needed
MAGIC_ENABLE = no		# Won't use for now
MOUSEKEY_ENABLE = no	# Won't use for now
RAW_ENABLE = no			# Disable raw HID commands
RGBLIGHT_ENABLE = no	# Won't use for now
SPACE_CADET_ENABLE = no	# Free up space

# Enable QMK features
CAPS_WORD_ENABLE = yes

# Enable Link Time Optimizations
LTO_ENABLE = yes

SRC += muse.c
