# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# EEPROM driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = rp2040_flash

LAYOUTS = tkl_ansi tkl_ansi_split_bs_rshift tkl_ansi_tsangan tkl_ansi_tsangan_split_bs_rshift tkl_f13_ansi tkl_f13_ansi_split_bs_rshift tkl_f13_ansi_tsangan tkl_f13_ansi_tsangan_split_bs_rshift tkl_iso tkl_iso_split_bs_rshift tkl_iso_tsangan tkl_iso_tsangan_split_bs_rshift tkl_f13_iso tkl_f13_iso_split_bs_rshift tkl_f13_iso_tsangan tkl_f13_iso_tsangan_split_bs_rshift
