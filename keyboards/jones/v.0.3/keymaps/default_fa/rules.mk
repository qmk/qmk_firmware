# Enabling options for FA (Full Armor) version.
# Disabling options to reduce firmware size.
# Add Link Time Optimization option.

# Build Options
#   change yes to no to disableß
#

MOUSEKEY_ENABLE = no        # Mouse keys
AUDIO_ENABLE = yes           # Audio outputß
OLED_DRIVER_ENABLE = yes    # OLED
EXTRAFLAGS += -flto
