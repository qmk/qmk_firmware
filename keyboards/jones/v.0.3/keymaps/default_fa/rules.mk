# Enabling options for FA (Full Armor) version.
# Disabling options to reduce firmware size.
# Add Link Time Optimization option.

# Build Options
#   change yes to no to disable
#

MOUSEKEY_ENABLE = no        # Mouse keys
AUDIO_ENABLE = yes           # Audio output
TAP_DANCE_ENABLE = no		# Tap Dance
OLED_DRIVER_ENABLE = yes
# EXTRAKEY_ENABLE = no	# reduce 500 bytes


EXTRAFLAGS += -flto
