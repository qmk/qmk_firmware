# MCU name
MCU = STM32F072

# Build Options
#   comment out to disable the options.
#
# EXTRAFLAGS+=-flto
LINK_TIME_OPTIMIZATION_ENABLE = yes
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes     # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
SERIAL_LINK_ENABLE = no
