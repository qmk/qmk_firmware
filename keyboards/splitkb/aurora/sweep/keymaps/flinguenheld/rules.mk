LTO_ENABLE = yes
CONVERT_TO = elite_pi

SRC += features/auto_shift.c
SRC += features/combo.c
SRC += features/leader.c
SRC += oled/oled.c

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

MOUSEKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
AUTO_SHIFT_MODIFIERS = no
COMBO_ENABLE = yes
LEADER_ENABLE = yes

# Recommended for space cadet shift
COMMAND_ENABLE = no

UNICODE_ENABLE = yes
SEND_STRING_ENABLE = yes
