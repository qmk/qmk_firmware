show_build_options:
	echo " PLATFORM = $(PLATFORM)"
	echo " FIRMWARE_FORMAT = $(FIRMWARE_FORMAT)"
	echo
	echo Build Options:
	echo "  BOOTMAGIC_ENABLE = $(BOOTMAGIC_ENABLE)"
	echo "  MOUSEKEY_ENABLE = $(MOUSEKEY_ENABLE)"
	echo "  EXTRAKEY_ENABLE = $(EXTRAKEY_ENABLE)"
	echo "  CONSOLE_ENABLE = $(CONSOLE_ENABLE)"
	echo "  COMMAND_ENABLE = $(COMMAND_ENABLE)"
	echo "  SLEEP_LED_ENABLE = $(SLEEP_LED_ENABLE)"
	echo "  NKRO_ENABLE = $(NKRO_ENABLE)"
	echo "  BACKLIGHT_ENABLE = $(BACKLIGHT_ENABLE)"
	echo "  RGBLIGHT_ENABLE = $(RGBLIGHT_ENABLE)"
	echo "  MIDI_ENABLE = $(MIDI_ENABLE)"
	echo "  UNICODE_ENABLE = $(UNICODE_ENABLE)"
	echo "  BLUETOOTH_ENABLE = $(BLUETOOTH_ENABLE)"
	echo "  AUDIO_ENABLE = $(AUDIO_ENABLE)"
	echo "  FAUXCLICKY_ENABLE = $(FAUXCLICKY_ENABLE)"
	echo "  HD44780_ENABLE = $(HD44780_ENABLE)"


show_all_features: show_build_options
	echo
	echo Other Features:
    ifneq ($(API_SYSEX_ENABLE),)
	echo "  API_SYSEX_ENABLE = $(API_SYSEX_ENABLE)"
    endif
    ifneq ($(AUTO_SHIFT_ENABLE),)
	echo "  AUTO_SHIFT_ENABLE = $(AUTO_SHIFT_ENABLE)"
    endif
    ifneq ($(AUTO_SHIFT_MODIFIERS),)
	echo "  AUTO_SHIFT_MODIFIERS = $(AUTO_SHIFT_MODIFIERS)"
    endif
    ifneq ($(BACKLIGHT_CUSTOM_DRIVER),)
	echo "  BACKLIGHT_CUSTOM_DRIVER = $(BACKLIGHT_CUSTOM_DRIVER)"
    endif
    ifneq ($(CIE1931_CURVE),)
	echo "  CIE1931_CURVE = $(CIE1931_CURVE)"
    endif
    ifneq ($(COMBO_ENABLE),)
	echo "  COMBO_ENABLE = $(COMBO_ENABLE)"
    endif
    ifneq ($(CUSTOM_DEBOUNCE),)
	echo "  CUSTOM_DEBOUNCE = $(CUSTOM_DEBOUNCE)"
    endif
    ifneq ($(CUSTOM_MATRIX),)
	echo "  CUSTOM_MATRIX = $(CUSTOM_MATRIX)"
    endif
    ifneq ($(DYNAMIC_KEYMAP_ENABLE),)
	echo "  DYNAMIC_KEYMAP_ENABLE = $(DYNAMIC_KEYMAP_ENABLE)"
    endif
    ifneq ($(ENCODER_ENABLE),)
	echo "  ENCODER_ENABLE = $(ENCODER_ENABLE)"
    endif
    ifneq ($(KEY_LOCK_ENABLE),)
	echo "  KEY_LOCK_ENABLE = $(KEY_LOCK_ENABLE)"
    endif
    ifneq ($(LCD_ENABLE),)
	echo "  LCD_ENABLE = $(LCD_ENABLE)"
    endif
    ifneq ($(LEADER_ENABLE),)
	echo "  LEADER_ENABLE = $(LEADER_ENABLE)"
    endif
    ifneq ($(LED_BREATHING_TABLE),)
	echo "  LED_BREATHING_TABLE = $(LED_BREATHING_TABLE)"
    endif
    ifneq ($(LED_TABLES),)
	echo "  LED_TABLES = $(LED_TABLES)"
    endif
    ifneq ($(POINTING_DEVICE_ENABLE),)
	echo "  POINTING_DEVICE_ENABLE = $(POINTING_DEVICE_ENABLE)"
    endif
    ifneq ($(PRINTING_ENABLE),)
	echo "  PRINTING_ENABLE = $(PRINTING_ENABLE)"
    endif
    ifneq ($(RGBLIGHT_CUSTOM_DRIVER),)
	echo "  RGBLIGHT_CUSTOM_DRIVER = $(RGBLIGHT_CUSTOM_DRIVER)"
    endif
    ifneq ($(RGB_MATRIX_ENABLE),)
	echo "  RGB_MATRIX_ENABLE = $(RGB_MATRIX_ENABLE)"
    endif
    ifneq ($(SERIAL_LINK_ENABLE),)
	echo "  SERIAL_LINK_ENABLE = $(SERIAL_LINK_ENABLE)"
    endif
    ifneq ($(SPLIT_KEYBOARD),)
	echo "  SPLIT_KEYBOARD = $(SPLIT_KEYBOARD)"
    endif
    ifneq ($(STENO_ENABLE),)
	echo "  STENO_ENABLE = $(STENO_ENABLE)"
    endif
    ifneq ($(TAP_DANCE_ENABLE),)
	echo "  TAP_DANCE_ENABLE = $(TAP_DANCE_ENABLE)"
    endif
    ifneq ($(TERMINAL_ENABLE),)
	echo "  TERMINAL_ENABLE = $(TERMINAL_ENABLE)"
    endif
    ifneq ($(UCIS_ENABLE),)
	echo "  UCIS_ENABLE = $(UCIS_ENABLE)"
    endif
    ifneq ($(UNICODEMAP_ENABLE),)
	echo "  UNICODEMAP_ENABLE = $(UNICODEMAP_ENABLE)"
    endif
    ifneq ($(UNICODE_COMMON),)
	echo "  UNICODE_COMMON = $(UNICODE_COMMON)"
    endif
    ifneq ($(USB_HID_ENABLE),)
	echo "  USB_HID_ENABLE = $(USB_HID_ENABLE)"
    endif
    ifneq ($(VIRTSER_ENABLE),)
	echo "  VIRTSER_ENABLE = $(VIRTSER_ENABLE)"
    endif
    ifneq ($(VISUALIZER_ENABLE),)
	echo "  VISUALIZER_ENABLE = $(VISUALIZER_ENABLE)"
    endif
