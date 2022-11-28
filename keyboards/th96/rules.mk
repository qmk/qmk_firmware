# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

STM32_BOOTLOADER_ADDRESS = 0x1FFF0000

BOOTMAGIC_ENABLE = yes      	# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      		# Mouse keys
EXTRAKEY_ENABLE = yes      		# Audio control and System control
CONSOLE_ENABLE = no        		# Console for debug
COMMAND_ENABLE = no        		# Commands for debug and configuration
NKRO_ENABLE = no           		# Enable N-Key Rollover
BACKLIGHT_ENABLE = no      		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        	# Enable keyboard RGB underglow
AUDIO_ENABLE = no           	# Audio output

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3733
DIP_SWITCH_ENABLE = yes
ENCODER_ENABLE = yes

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
