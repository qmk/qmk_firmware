# Build Options:
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically

BOOTMAGIC_ENABLE = no   # virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes  # mouse keys(+4700)
EXTRAKEY_ENABLE  = no   # audio control and System control(+450)
CONSOLE_ENABLE   = no   # console for debug(+400)
COMMAND_ENABLE   = no   # commands for debug and configuration
NKRO_ENABLE      = yes  # nkey rollover
BACKLIGHT_ENABLE = no   # enable keyboard backlight functionality
MIDI_ENABLE      = no   # MIDI controls
AUDIO_ENABLE     = no   # audio output on port C6
UNICODE_ENABLE   = no   # unicode
BLUETOOTH_ENABLE = no   # enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE  = no   # enable WS2812 RGB underlight, do not enable this with audio at the same time.
STENO_ENABLE     = yes	# enable TX Bolt protocol, requires VIRTSER and may not work with mouse keys

# do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no   # breathing sleep LED during USB suspend

TAP_DANCE_ENABLE = yes  # enable double tap completion of (),[],{}

ifndef QUANTUM_DIR
include ../../../../Makefile
endif
