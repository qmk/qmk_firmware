# MCU name
MCU = atmega32u4
BOARD = HMC_Keyboard

# Build Options
#   comment out to disable the options.
#
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE    = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE     = yes      # Mouse keys
EXTRAKEY_ENABLE     = yes      # Audio control and System control
CONSOLE_ENABLE      = no      # Console for debug
COMMAND_ENABLE      = yes      # Commands for debug and configuration
NKRO_ENABLE         = yes      # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE         = no       # MIDI controls
AUDIO_ENABLE        = no       # Audio output on port C6
UNICODE_ENABLE      = no       # Unicode
BACKLIGHT_ENABLE    = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE     = yes      # Enable WS2812 RGB underlight.


API_SYSEX_ENABLE    = no
SLEEP_LED_ENABLE    = no       # Breathing sleep LED during USB suspend
OLED_DRIVER_ENABLE  = no
ALLOW_WARNINGS      = yes
LG_Indicator_Enable = yes
RGB_LG              = yes
#WS2812_DRIVER       = pwm
# Enter lower-power sleep mode when on the ChibiOS idle thread
# OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE