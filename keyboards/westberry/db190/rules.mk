RGB_MATRIX_CUSTOM_USER = yes # Enable custom RGB effect
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash

VPATH += keyboards/westberry/common
SRC += wb32_driver.c
