SRC += matrix.c TWIlib.c issi.c lighting.c

# MCU name
MCU = atmega32u4


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB = $(F_CPU)

# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded 
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = caterina

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   atmega32a    bootloadHID
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight. 
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
BACKLIGHT_CUSTOM_DRIVER = yes
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality, also set ISSI_ENABLE below for Miera
ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled

CUSTOM_MATRIX = yes

#ifeq ($(strip $(ISSI_ENABLE)), yes)
#    TMK_COMMON_DEFS += -DISSI_ENABLE
#endif
#
#ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
#    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
#endif

DEFAULT_FOLDER = meira/promicro
LAYOUTS = ortho_4x12
