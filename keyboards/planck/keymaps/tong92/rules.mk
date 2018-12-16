#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device.
#                Please customize your programmer settings(PROGRAM_CMD)
#
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
# make dfu = Download the hex file to the device, using dfu-programmer (must
#            have dfu-programmer installed).
#
# make flip = Download the hex file to the device, using Atmel FLIP (must
#             have Atmel FLIP installed).
#
# make dfu-ee = Download the eeprom file to the device, using dfu-programmer
#               (must have dfu-programmer installed).
#
# make flip-ee = Download the eeprom file to the device, using Atmel FLIP
#                (must have Atmel FLIP installed).
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------
# Build Options
#   change to "no" to disable the options, or define them in the makefile.mk in 
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
EXTRAKEY_ENABLE  = no # Audio control and System control(+450)
CONSOLE_ENABLE   = no  # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
NKRO_ENABLE      = no # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
MIDI_ENABLE      = no  # MIDI controls
AUDIO_ENABLE     = no # Audio output on port C6
UNICODE_ENABLE   = no  # Unicode
BLUETOOTH_ENABLE = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE  = no  # Enable WS2812 RGB underlight. 

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif