# Enabling options for FA (Full Armor) version.
# Disabling options to reduce firmware size.
# Add Link Time Optimization option.

# Build Options
#   change yes to no to disableß
#

MOUSEKEY_ENABLE = no        # Mouse keys
AUDIO_ENABLE = no           # Audio output


EXTRAFLAGS += -flto
