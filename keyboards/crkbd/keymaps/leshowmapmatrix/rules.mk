CONVERT_TO = rp2040_ce
BOOTLOADER = rp2040

RGB_LIGHT_ENABLE = no

RGB_MATRIX_SUPPORTED = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
NKRO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

LTO_ENABLE = yes

# Use custom font from keymap directory
OLED_FONT_H = "keyboards/crkbd/keymaps/leshowmapmatrix/glcdfont.c"
