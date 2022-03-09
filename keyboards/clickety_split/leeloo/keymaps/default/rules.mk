# Overrides from default rules.mk which may be helpful.
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
TAP_DANCE_ENABLE = no       # Enable Tap Dance
COMBO_ENABLE = no           # Enable Combos

# To enable Rotary Encoders
ENCODER_ENABLE = no

# To enable OLED Displays
OLED_ENABLE = no
OLED_DRIVER = SSD1306       # OLED display

# Bootloader selection
BOOTLOADER = caterina       # Pro Micro
#BOOTLOADER = atmel-dfu		# Elite-C

# Enable Link Time Optimization
LTO_ENABLE = yes			# Enable help with smaller firmware size
