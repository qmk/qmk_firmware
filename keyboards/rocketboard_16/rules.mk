# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# project specific files


#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	      # USB Nkey Rollover
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = yes
#WS2812_DRIVER = spi
LTO_ENABLE = yes
OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
