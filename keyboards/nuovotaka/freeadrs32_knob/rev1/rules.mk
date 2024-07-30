# Duplex matrix.
CUSTOM_MATRIX = lite
SRC += lib/duplexmatrix/duplexmatrix.c

# To support OLED
OLED_ENABLE = yes
SRC += lib/oledkit/oledkit.c    #

# Include common library
SRC += lib/freeadrs32/freeadrs32.c

# Disable other features to squeeze firmware size
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
