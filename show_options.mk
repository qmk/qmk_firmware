BUILD_OPTION_NAMES = \
  BOOTMAGIC_ENABLE \
  MOUSEKEY_ENABLE \
  EXTRAKEY_ENABLE \
  CONSOLE_ENABLE \
  COMMAND_ENABLE \
  NKRO_ENABLE \
  TERMINAL_ENABLE \
  CUSTOM_MATRIX \
  CUSTOM_DEBOUNCE \
  SPLIT_KEYBOARD \
  DYNAMIC_KEYMAP_ENABLE \
  USB_HID_ENABLE

HARDWARE_OPTION_NAMES = \
  SLEEP_LED_ENABLE \
  BACKLIGHT_ENABLE \
  BACKLIGHT_CUSTOM_DRIVER \
  RGBLIGHT_ENABLE \
  RGBLIGHT_CUSTOM_DRIVER \
  RGB_MATRIX_ENABLE \
  SERIAL_LINK_ENABLE \
  CIE1931_CURVE \
  MIDI_ENABLE \
  BLUETOOTH_ENABLE \
  AUDIO_ENABLE \
  FAUXCLICKY_ENABLE \
  HD44780_ENABLE \
  ENCODER_ENABLE \
  LCD_ENABLE \
  LED_BREATHING_TABLE \
  LED_TABLES \
  POINTING_DEVICE_ENABLE \
  VISUALIZER_ENABLE

OTHER_OPTION_NAMES = \
  UNICODE_ENABLE \
  UCIS_ENABLE \
  UNICODEMAP_ENABLE \
  UNICODE_COMMON \
  API_SYSEX_ENABLE \
  AUTO_SHIFT_ENABLE \
  AUTO_SHIFT_MODIFIERS \
  COMBO_ENABLE \
  KEY_LOCK_ENABLE \
  LEADER_ENABLE \
  PRINTING_ENABLE \
  STENO_ENABLE \
  TAP_DANCE_ENABLE \
  VIRTSER_ENABLE

define NAME_ECHO
	@echo "  $1 = $($1)		# $(origin $1)"

endef

.PHONY: show_build_options0 show_build_options
show_build_options0:
	@echo " KEYBOARD = $(KEYBOARD)"
	@echo " KEYMAP   = $(KEYMAP)"
	@echo " PLATFORM = $(PLATFORM)"
	@echo " FIRMWARE_FORMAT = $(FIRMWARE_FORMAT)"
	@echo
	@echo "Build Options:"
	$(foreach A_OPTION_NAME,$(sort $(BUILD_OPTION_NAMES)),\
		$(call NAME_ECHO,$(A_OPTION_NAME)))

show_build_options: show_build_options0
	@echo
	@echo "If you want to know more, please try 'show_all_features' or 'show_full_features'"
	@echo

.PHONY: show_all_features
show_all_features: show_build_options0
	@echo
	@echo "Hardware Options:"
	$(foreach A_OPTION_NAME,$(sort $(HARDWARE_OPTION_NAMES)),\
		$(if $($(A_OPTION_NAME)),$(call NAME_ECHO,$(A_OPTION_NAME))))
	@echo
	@echo "Other Options:"
	$(foreach A_OPTION_NAME,$(sort $(OTHER_OPTION_NAMES)),\
		$(if $($(A_OPTION_NAME)),$(call NAME_ECHO,$(A_OPTION_NAME))))

.PHONY: show_full_features
show_full_features: show_build_options0
	@echo
	@echo "Hardware Options:"
	$(foreach A_OPTION_NAME,$(sort $(HARDWARE_OPTION_NAMES)),\
		$(call NAME_ECHO,$(A_OPTION_NAME)))
	@echo
	@echo "Other Options:"
	$(foreach A_OPTION_NAME,$(sort $(OTHER_OPTION_NAMES)),\
		$(call NAME_ECHO,$(A_OPTION_NAME)))
