# https://docs.qmk.fm/getting_started_make_guide.html

# Userspace options
USER_CAPS_WORD_ENABLE = yes
USER_NUM_WORD_ENABLE = yes
USER_SECRETS_ENABLE = yes
USER_SUPER_ALT_TAB_ENABLE = yes

# Features to enable
DYNAMIC_MACRO_ENABLE = yes
KEY_LOCK_ENABLE = yes

# Extra features that are nice but takes space. Enable only if they're
# used in the layout.
WPM_ENABLE = no
# EXTRAKEY_ENABLE = no        # For volume keys and similar
# MOUSEKEY_ENABLE = no        # Them mouse keys yo
KEY_OVERRIDE_ENABLE = no
LEADER_ENABLE = no
TAP_DANCE_ENABLE = no
# RGBLIGHT_ENABLE = no        # Keyboard RGB underglow
RGB_MATRIX_ENABLE = no

# Features I definitely don't care aboud
LTO_ENABLE = yes
CONSOLE_ENABLE = no
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no

