USER_NAME := T4CORUN
LTO_ENABLE = yes

BOOTMAGIC_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
NKRO_ENABLE = yes

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = no

# disable options to save space on controller. Limit 28K
# the following options are enabled by default in common_features.mk
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no

# these are disabled by default in common_features.mk and have to be enabled
DYNAMIC_MACRO_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no

# My Custom Paremeters
ONESHOTKEY_ENABLE = no
KEYLOG_ENABLE = no
