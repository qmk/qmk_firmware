SRC += features/casemodes.c
# For STM32, serial is usually more stable than i2c for split communication.
SERIAL_DRIVER = usart
MCU_SERIES    = STM32F411

CONSOLE_ENABLE = yes
KEYCODE_STRING_ENABLE = yes

SPLIT_KEYBOARD = yes
MOUSEKEY_ENABLE = yes 
CAPS_WORD_ENABLE = no
COMBO_ENABLE = yes
SEND_STRING_ENABLE = yes

OLED_DRIVER_ENABLE = no
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
LEADER_ENABLE = no