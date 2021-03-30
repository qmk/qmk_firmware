# MCU name
MCU = attiny85

# Bootloader selection
BOOTLOADER = micronucleus
OPT_DEFS += -DBOOTLOADER_SIZE=1862
PROGRAM_CMD = micronucleus --run $(BUILD_DIR)/$(TARGET).hex

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output

# Save as much space as we can...
LTO_ENABLE = yes
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no

BACKLIGHT_DRIVER = software
