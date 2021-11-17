# MCU name
MCU  =  atmega32u4

# Bootloader selection
BOOTLOADER  =  caterina

# Build Options
BOOTMAGIC_ENABLE        =  no         # Virtual DIP switch configuration
MOUSEKEY_ENABLE         =  no        # Mouse keys
EXTRAKEY_ENABLE         =  no        # Audio control and System control
CONSOLE_ENABLE          =  no        # Console for debug
COMMAND_ENABLE          =  no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE        =  no        # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE             =  no        # USB Nkey Rollover
BACKLIGHT_ENABLE        =  no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE         =  no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE        =  no        # Enable Bluetooth
AUDIO_ENABLE            =  no        # Audio output
LTO_ENABLE              =  yes       # Reduced firmware size

# Formy46 Features Options
SPLIT_KEYBOARD          =  yes       # Enable Split Keyboard
RGBLIGHT_ENABLE         =  no
RGB_MATRIX_ENABLE       =  no       # Enable keyboard RGB Matrix
RGB_MATRIX_DRIVER       =  WS2812    # RGB Matrix driver
SRC                    +=  analog.c  # adc driver
JOYSTICK_ENABLE         =  yes       # Enable Joystick
POINTING_DEVICE_ENABLE  =  yes       # Enable Pointing Device
ENCODER_ENABLE          =  yes       # Enable Rotary Encoder
OLED_ENABLE             =  yes       # Enable OLED
OLED_DRIVER             =  SSD1306   # OLED Type
MOUSEKEY_ENABLE  		=  yes       # Enable Mouse keycord
