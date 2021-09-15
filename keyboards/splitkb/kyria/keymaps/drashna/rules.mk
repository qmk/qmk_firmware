OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION = no

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes          # USB Nkey Rollover
UNICODE_ENABLE = no       # Unicode
KEY_LOCK_ENABLE = no


BOOTLOADER = hid
BOOTLOADER_SIZE = 512
PROGRAM_CMD = 	$(HID_BOOTLOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
# TAP_DANCE_ENABLE = yes

WPM_ENABLE = yes
SWAP_HANDS_ENABLE = yes
