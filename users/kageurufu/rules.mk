SRC += kageurufu.c \
       process_records.c \
       custom_rgb.c

# Link time optimization, should save on firmware size
EXTRAFLAGS += -flto


# Some usual defaults
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
COMMAND_ENABLE = yes
CONSOLE_ENABLE = yes
RGBLIGHT_ENABLE = no
RGBLIGHT_ANIMATIONS = yes
