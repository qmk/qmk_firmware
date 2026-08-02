# MCU / bootloader are inferred from keyboard.json (processor/board/bootloader),
# but are listed here too for clarity on older toolchains.
MCU = RP2040
BOOTLOADER = rp2040

# bootmagic / extrakey / nkro / oled / rgblight are all declared under
# "features" in keyboard.json - don't redeclare them here, it just
# produces "specified in both" warnings.
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

# OLED (SSD1306 128x32 over I2C)
I2C_DRIVER = I2CD1

# Onboard WS2812 RGB LED (XIAO RP2040, GP12) - "vendor" uses RP2040's PIO
# based WS2812 driver.
WS2812_DRIVER = vendor

LTO_ENABLE = yes
