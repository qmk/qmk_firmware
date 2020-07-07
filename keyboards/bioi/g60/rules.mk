# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = qmk-dfu

SRC +=	../usart.c \
				../ble.c \
				../main.c

OPT_DEFS += -DPROTOCOL_BLE
OPT_DEFS += -DUART_RX1_BUFFER_SIZE=16 -DUART_TX1_BUFFER_SIZE=16
OPT_DEFS += -DUSART1_ENABLED

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no      # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = no           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
LTO_ENABLE            = yes # Reduce firmware size

VIA_ENABLE = yes            # VIA support should be enabled here due to the main() loop will be compiled first.
