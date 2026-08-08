# MCU / bootloader are inferred from keyboard.json (processor/board/bootloader).

# bootmagic / extrakey / nkro / oled / rgblight are all declared under
# "features" in keyboard.json - don't redeclare them here, it just
# produces "specified in both" warnings.
MOUSEKEY_ENABLE = no

LTO_ENABLE = yes
