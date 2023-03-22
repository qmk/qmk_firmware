# MCU name
# MCU = STM32F103

#
OS_DETECTION_ENABLE = yes   #Enable OS detection
#BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = AW20216

#flash
#WEAR_LEVELING_DRIVER = spi_flash
#EEPROM_DRIVER = wear_leveling
#WEAR_LEVELING_DRIVER = spi_flash

# Enter lower-power sleep mode when on the ChibiOS idle thread
#OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

#UART_DEBUG = yes
#SERIAL_DRIVER = usart
QUANTUM_LIB_SRC += uart.c
