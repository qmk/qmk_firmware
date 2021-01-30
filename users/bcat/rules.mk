SRC += bcat.c

# Enable Bootmagic Lite to consistently reset to bootloader and clear EEPROM.
BOOTMAGIC_ENABLE = lite

# Enable media keys on all keyboards.
EXTRAKEY_ENABLE = yes

# Enable N-key rollover on all keyboards. In addition to its intended
# functionality, as of July 2020, this is required for Chrome OS to process
# media keys. (It appears that Chrome OS filters out key events from the second
# USB endpoint's consumer and system control devices unless that endpoint also
# reports a keyboard or mouse device.)
NKRO_ENABLE = yes

# Enable link-time optimization to reduce binary size.
LTO_ENABLE = yes

# Disable unused build options on all keyboards.
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = no
TERMINAL_ENABLE = no

# Disable unused hardware options on all keyboards.
FAUXCLICKY_ENABLE = no
MIDI_ENABLE = no
SLEEP_LED_ENABLE = no

# Disable other unused options on all keyboards.
API_SYSEX_ENABLE = no
AUTO_SHIFT_ENABLE = no
COMBO_ENABLE = no
KEYBOARD_LOCK_ENABLE = no
KEY_LOCK_ENABLE = no
LEADER_ENABLE = no
SWAP_HANDS_ENABLE = no
TAP_DANCE_ENABLE = no
UCIS_ENABLE = no
UNICODEMAP_ENABLE = no
UNICODE_ENABLE = no
