MOUSEKEY_ENABLE = yes    # Habilita el uso de teclas como Mouse
RGBLIGHT_ENABLE = yes    # Habilita WS2812 RGB para luces de abajo.
OLED_ENABLE     = yes    # Habilita las pantallas OLED
LTO_ENABLE      = yes    # Habilita "Link-Time Optimization", (optimiza código y suele reducir espacio en memoria)
EXTRAKEY_ENABLE = yes    # Habilita las teclas para multimedia
TAP_DANCE_ENABLE = yes   # Habilita las funciones Tap Dance (Doble Click)
RGB_MATRIX_ENABLE = yes  # Hbailita la matriz RGB del teclado

SRC += oled.c

#Configuraciones a considerar para no consumir memoria
BOOTMAGIC_ENABLE  =	no
SLEEP_LED_ENABLE  =	no
NKRO_ENABLE       =	no
BACKLIGHT_ENABLE  =	no
MIDI_ENABLE       =	no
UNICODE_ENABLE    =	no
BLUETOOTH_ENABLE  =	no
AUDIO_ENABLE      =	no
HD44780_ENABLE    =	no
FAUXCLICKY_ENABLE = no
CONSOLE_ENABLE    =	no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESCAPE_ENABLE = no

