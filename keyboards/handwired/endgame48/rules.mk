# MCU name
MCU = atmega32u4
BOOTLOADER = atmel-dfu

BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
# https://github.com/qmk/qmk_firmware/blob/master/docs/faq_debug.md
DEBUG_ENABLE = no  # HID prints
COMMAND_ENABLE = no  # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
OLED_ENABLE = yes

PS2_MOUSE_ENABLE = no
# PS2_USE_USART = yes
# PS2_USE_INT = yes

DEBOUNCE_TYPE = sym_eager_pk

SRC += taphold.c symbols.c menu.c

# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
EXTRAFLAGS += -flto
