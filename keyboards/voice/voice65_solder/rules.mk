
MCU = STM32F303
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave


RGBLIGHT_ENABLE = yes   
# WS2812_DRIVER = spi
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
# F_CPU = 16000000 lizm take off

#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
# ARCH = AVR8 lizm take off

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
# F_USB = $(F_CPU) lizm take off



# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000) lizm
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700) lizm
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
ENCODER_ENABLE = yes    


CONSOLE_ENABLE = yes	# Console for debug(+400) lizm
COMMAND_ENABLE = yes    # Commands for debug and configuration lizm
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no

RGB_MATRIX_ENABLE = IS31FL3741




