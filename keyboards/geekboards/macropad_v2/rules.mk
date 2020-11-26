# MCU name
MCU = STM32F072
BOARD = ST_STM32F072B_DISCOVERY

BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
POINTING_DEVICE_ENABLE = yes
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes		# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
RGB_MATRIX_ENABLE = WS2812
WS2812_DRIVER = pwm
# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE