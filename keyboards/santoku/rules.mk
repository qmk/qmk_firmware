

# MCU name
MCU = atmega32u4

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096


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
# PS2_USE_USART = yes
#PS2_USE_INT = yes
PS2_USE_BUSYWAIT = yes
ENCODER_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes

SRC = i2c.c \
      ssd1306.c 
