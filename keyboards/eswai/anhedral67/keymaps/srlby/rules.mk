BOOTLOADER = qmk-dfu
COMBO_ENABLE = yes
# RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
UNICODE_ENABLE = yes
MOUSEKEY_ENABLE = yes

SRC +=  naginata_v12.c

EXTRAFLAGS += -flto