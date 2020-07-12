SRC += bcat.c

# Enable Bootmagic Lite to consistently reset to bootloader and clear EEPROM.
BOOTMAGIC_ENABLE = lite

# Enable media keys on all keyboards. (Even though I don't use mouse keys, they
# seem to be required for media keys to register on Chrome OS.)
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes

# Enable link-time optimization to reduce binary size.
LINK_TIME_OPTIMIZATION_ENABLE = yes

# Disable unused build options on all keyboards.
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
NKRO_ENABLE = no
TERMINAL_ENABLE = no

# Disable unused hardware options on all keyboards.
FAUXCLICKY_ENABLE = no
MIDI_ENABLE = no
SLEEP_LED_ENABLE = no

# Disable unused other options.
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
