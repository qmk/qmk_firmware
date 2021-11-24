# 60% is default
SRC += 60/kpalatzky.c

# Flags
## Enable features
TAP_DANCE_ENABLE = yes      # Tap dance (https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance)
MOUSEKEY_ENABLE = yes       # Mouse keys (https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_mouse_keys)
## Disable features
CONSOLE_ENABLE = no         # Debugging (https://beta.docs.qmk.fm/faqs/faq_debug) = NO_DEBUG, NO_PRINT
AUDIO_ENABLE = no           # Audio output (https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_audio)

# Disable unsupported hardware
AUDIO_SUPPORTED = no        # Audio output (https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_audio)

# TODO: Link time optimization, should save on firmware size
# EXTRAFLAGS += -flto

# Enable Link Time Optimization (LTO)
# This makes the process take longer, but it can significantly reduce the compiled size
ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif
