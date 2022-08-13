CONSOLE_ENABLE = yes

# Project specific files
SRC += \
    utils.c \
    rgb/rgb_handler.c \
    oled/oled_handler.c \
    oled/renderers/bongocat.c \
    oled/renderers/logo.c \
    lib/ds3231/ds3231.c \

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
KEYMAP_PATH := $(dir $(MKFILE_PATH))
ifneq ("$(wildcard $(KEYMAP_PATH)/keys.h)","")
    SRC += oled/renderers/lockscreen.c \
        oled/renderers/otp.c \
        otp/otp.c \
        otp/password_validator.c \
        lib/security/sha1/sha1.c \
        lib/security/sha256/sha256.c \
        lib/security/aes128/aes128.c
endif
    
   
QUANTUM_LIB_SRC += i2c_master.c