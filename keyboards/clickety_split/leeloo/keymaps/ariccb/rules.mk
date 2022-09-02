# Overrides from default rules.mk
MOUSEKEY_ENABLE = yes         # Mouse keys
EXTRAKEY_ENABLE = yes         # Audio control and System control
TAP_DANCE_ENABLE = no         # Enable Tap Dance
COMBO_ENABLE = yes            # Enable Combos
BACKLIGHT_ENABLE = no	      # Backlighting
DEBOUNCE_TYPE = sym_defer_g   # Debouncing - trying to stop double space bar from being hit

COMMAND_ENABLE = no
CONSOLE_ENABLE = no

RGBLIGHT_ENABLE = no

# PS2_MOUSE_ENABLE = yes
# PS2_USE_INT = yes

# To enable Rotary Encoders
ENCODER_ENABLE = yes

# To enable OLED Displays
OLED_ENABLE = yes
OLED_DRIVER = SSD1306       # OLED displayS

# Bootloader selection
BOOTLOADER = caterina       # Pro Micro

# Enable Link Time Optimization
LTO_ENABLE = yes			# Enable help with smaller firmware size

SRC += features/select_word.c
SRC += features/caps_word.c
SRC += features/layer_lock.c

# SRC += features/autocorrection.c