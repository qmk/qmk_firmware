OLED_ENABLE = yes          # Enables the use of OLED displays
OLED_DRIVER = SSD1306
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
NKRO_ENABLE = yes          # Enable N-Key Rollover
ENCODER_ENABLE = no        # Disable Rotary Encoder
SPACE_CADET_ENABLE = no    # Disable Space Cadet Shift
GRAVE_ESC_ENABLE = no      # Disable Grave Escape
MOUSEKEY_ENABLE =  no      # Disable Mousekeys
WPM_ENABLE = yes           # Enable WPM Counter (Works with default wpm files, but works better with vectorstorm updated wpm.c and wpm.h -> https://github.com/vectorstorm/qmk_firmware/tree/wpm_exact)

SRC += oled.c
