OLED_ENABLE = yes          # Enables the use of OLED displays
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
NKRO_ENABLE = yes          # Enable N-Key Rollover
ENCODER_ENABLE = no        # Disable Rotary Encoder
SPACE_CADET_ENABLE = no    # Disable Space Cadet Shift
GRAVE_ESC_ENABLE = no      # Disable Grave Escape
MOUSEKEY_ENABLE =  no      # Disable Mousekeys
WPM_ENABLE = yes           # Enable WPM Counter (Works with default wpm files, but works better with vectorstorm updated wpm.c and wpm.h -> https://github.com/vectorstorm/qmk_firmware/tree/wpm_exact)
KEY_OVERRIDE_ENABLE = yes  # Enable Key Overrides
CONSOLE_ENABLE = no

DEBOUNCE_TYPE = sym_eager_pk

BOOTLOADER = hid           # This Keymap Uses nanoBoot, more info in readme
BOOTLOADER_SIZE = 512
PROGRAM_CMD = 	$(HID_BOOTLOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex

SRC += oled.c
