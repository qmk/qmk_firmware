SRC += nathancooke7.c
# SRC += features/secrets.c
SRC += features/combos.c
SRC += process_records.c

ifeq ($(strip $(CUSTOM_POINTING_DEVICE)), yes)
	SRC += features/pointing.c
	MOUSEKEY_ENABLE = yes
endif

COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

# save space on MCU by disabling unused features
LTO_ENABLE = yes

BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no
OLED_DRIVER_ENABLE = no
RGB_MATRIX_ENABLE = no
RGB_MATRIX_SUPPORTED = no
RGB_LIGHT_SUPPORTED = no
SPACE_CADET_ENABLE = no
WPM_ENABLE = no
# end save space
