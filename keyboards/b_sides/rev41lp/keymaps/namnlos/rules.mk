# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = yes      # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes           # USB Nkey Rollover
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = yes        # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
HD44780_ENABLE = no         # Enable support for HD44780 based LCDs
OLED_ENABLE = no            # Enable OLED screen support
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
TAP_DANCE_ENABLE = yes      # Let's dance
COMBO_ENABLE = no           # Combos
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = pwm

DEBOUNCE_TYPE = sym_defer_pk

LTO_ENABLE      = yes
EXTRAFLAGS += -flto

#Debug options
VERBOSE = no
