ifneq ($(strip $(USE_PROTON_C)),)
  # Proton-C
  MCU = STM32F303

  SPLIT_KEYBOARD = no
  RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.

  EXTRAFLAGS += -DUSE_PROTON_C
  LDFLAGS += -specs=nano.specs -specs=nosys.specs
else
  # Pro Micro or Elite-C
  MCU = atmega32u4
  F_CPU = 16000000
  ARCH = AVR8
  F_USB = $(F_CPU)
  BOOTLOADER = dfu
  OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

  # Currently moved to Pro Micro only section because of lack of Proton-C support
  SPLIT_KEYBOARD = yes
  RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
  ENCODER_ENABLE = yes
endif


# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
SUBPROJECT_rev2 = yes

SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend


DEFAULT_FOLDER = zen/rev2
