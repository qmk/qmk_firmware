OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes
VIA_ENABLE = yes
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
ENCODER_ENABLE = yes        # Use rotary encoder
LTO_ENABLE = yes            # Link-time optimization

# Project specific files
SRC += matrix.c \
       common/bitc_led.c \
       big_led.c \
       common/remote_kb.c
QUANTUM_LIB_SRC += uart.c
