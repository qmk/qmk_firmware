# MCU name
MCU = atmega32u4

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.


# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable


# Build Options
#   comment out to disable the options.
#

SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = yes  # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
# RGB_MATRIX_DRIVER = WS2812
ENCODER_ENABLE = yes
RGBLIGHT_ENABLE = yes
UNICODE_ENABLE = yes        # Unicode
