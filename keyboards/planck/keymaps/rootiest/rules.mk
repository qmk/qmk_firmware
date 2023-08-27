SRC += muse.c
ENCODER_ENABLE = yes # Enables basic encoder support
OLED_ENABLE = yes
# UNICODE_ENABLE = yes # Allow inputting basic unicode characters
UNICODEMAP_ENABLE = yes # Enable use of Unicode mapping array
# UCIS_ENABLE = yes # Another method for generating Unicode characters via maps
TAP_DANCE_ENABLE = yes # Enable Tap-Dance
NKRO_ENABLE = yes # Enable N-Key rollover
MOUSEKEY_ENABLE = yes # Enable mouse emulation
EXTRAKEY_ENABLE = yes # Allows audio control and System control
RAW_ENABLE = yes # Enable bi-directional communication to host
CONSOLE_ENABLE = yes # Enable outputting debugging data/logs to terminal
WPM_ENABLE = yes # Enable on-board words-per-minute tracking
VELOCIKEY_ENABLE = yes # Enables dynamically changing rgb animation speed based on WPM
LEADER_ENABLE = yes # Enables Leader-Key
COMBO_ENABLE = yes # Enables combo keys
KEY_LOCK_ENABLE = yes # Enables using lock key to maintain holds
# LTO_ENABLE = yes # Does some optimisation to make firmware size smaller
# SWAP_HANDS_ENABLE = yes # Enables the swap hands function
# DEBOUNCE_TYPE = sym_eager_pk # Change debounce algorithm

# NOTE: The following is not yet available in main qmk branch
KEY_OVERRIDE_ENABLE = yes # Allows overiding modifier combos (change Shift+1 without affecting 1 or Shift's normal operation)
