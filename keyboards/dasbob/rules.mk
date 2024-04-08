# Bootloader selection
BOOTLOADER = rp2040

# Dasbob Default Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
UNICODE_ENABLE = yes        # Unicode
AUDIO_ENABLE = no           # Disabled as I have opted to omit the buzzer in my build
SPLIT_KEYBOARD = yes        # Use shared split_common code
OLED_ENABLE = no	        # Disabled as I have opted to omit the oled in my build
OLED_DRIVER = ssd1306
WPM_ENABLE = yes
LTO_ENABLE = yes
SERIAL_DRIVER = vendor
AUDIO_DRIVER = pwm_hardware

# Ben Vallack Keymap Specific
TAP_DANCE_ENABLE = no	    # Presently not in use - enable if using ben vallack keymap