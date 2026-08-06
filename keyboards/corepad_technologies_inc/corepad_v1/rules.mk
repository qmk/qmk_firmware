# MCU / bootloader are inferred from keyboard.json (processor/board/bootloader).

# bootmagic / extrakey / nkro / oled / rgblight are all declared under
# "features" in keyboard.json - don't redeclare them here, it just
# produces "specified in both" warnings.
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

LTO_ENABLE = yes
