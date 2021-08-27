# MCU name
MCU = STM32F303

# Build Options
#   change yes to no to disable
#
ENCODER_ENABLE = yes
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no        # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes            # USB Nkey Rollover
KEY_LOCK_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = pwm
WPM_ENABLE = yes		 # Show APM.
OLED_DRIVER_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
VELOCIKEY_ENABLE = yes

DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
