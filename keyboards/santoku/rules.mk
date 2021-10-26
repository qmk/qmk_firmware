MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu


BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes 	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
#NKRO_ENABLE = yes	# USB Nkey Rollover - not yet supported in LUFA

# Options that are specific to current build of Santoku
WPM_ENABLE = yes		# Enable Words Per Minute Count for OLED 
OLED_DRIVER_ENABLE = yes
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
#PS2_USE_INT = yes
#PS2_USE_BUSYWAIT = yes
ENCODER_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes

SRC = i2c.c \
      ssd1306.c 
