SRC += features/oneshot.c

BOOTMAGIC_ENABLE = no
OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
RGBLIGHT_ENABLE = no    # Enable keyboard RGB underglow
COMMAND_ENABLE = no 		# Disables the command feature
COMBO_ENABLE = yes
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
AUDIO_ENABLE = no
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no
BACKLIGHT_ENABLE = no
CAPS_WORD_ENABLE = yes

LAYOUTS = split_3x5_3 split_3x6_3
