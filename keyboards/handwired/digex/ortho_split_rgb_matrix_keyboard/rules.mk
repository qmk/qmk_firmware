# MCU name
#MCU = STM32F103
DEFAULT_FOLDER =  handwired/digex/ortho_split_rgb_matrix_keyboard/rev_1

#BOARD = STM32_F103_STM32DUINO

# Bootloader selection
#BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
#
#BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
#MOUSEKEY_ENABLE = yes       # Mouse keys
#EXTRAKEY_ENABLE = yes       # Audio control and System control
#CONSOLE_ENABLE = false         # Console for debug
#COMMAND_ENABLE = no         # Commands for debug and configuration
#NKRO_ENABLE = yes           # Enable N-Key Rollover
#BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
#RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
#RGB_MATRIX_ENABLE = yes
#RGB_MATRIX_DRIVER = ws2812
#AUDIO_ENABLE = no           # Audio output

#SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
#WS2812_DRIVER = pwm
#EEPROM_DRIVER = transient
#LAYOUTS = ortho_4x12

# Disable unsupported hardware
#AUDIO_SUPPORTED = no
#BACKLIGHT_SUPPORTED = no
#TAP_DANCE_ENABLE = yes
#USB_WAIT_FOR_ENUMERATION = no
#NO_SUSPEND_POWER_DOWN = yes
#NO_USB_STARTUP_CHECK = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE