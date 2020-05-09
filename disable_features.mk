# Unconditionally disable features that a keyboard advertises it doesn't support

ifeq ($(strip $(ADAFRUIT_BLE_SUPPORTED)), no)
    ADAFRUIT_BLE_ENABLE=no
endif

ifeq ($(strip $(AUDIO_SUPPORTED)), no)
    AUDIO_ENABLE=no
endif

ifeq ($(strip $(BACKLIGHT_SUPPORTED)), no)
    BACKLIGHT_ENABLE=no
endif

ifeq ($(strip $(BLUETOOTH_SUPPORTED)), no)
    BLUETOOTH_ENABLE=no
endif

ifeq ($(strip $(DIP_SWITCH_SUPPORTED)), no)
    DIP_SWITCH_ENABLE=no
endif

ifeq ($(strip $(DYNAMIC_KEYMAP_SUPPORTED)), no)
    DYNAMIC_KEYMAP_ENABLE=no
endif

ifeq ($(strip $(ENCODER_SUPPORTED)), no)
    ENCODER_ENABLE=no
endif

ifeq ($(strip $(HAPTIC_SUPPORTED)), no)
    HAPTIC_ENABLE=no
endif

ifeq ($(strip $(HD44780_SUPPORTED)), no)
    HD44780_ENABLE=no
endif

ifeq ($(strip $(IOS_DEVICE_SUPPORTED)), no)
    IOS_DEVICE_ENABLE=no
endif

ifeq ($(strip $(LCD_BACKLIGHT_SUPPORTED)), no)
    LCD_BACKLIGHT_ENABLE=no
endif

ifeq ($(strip $(LCD_SUPPORTED)), no)
    LCD_ENABLE=no
endif

ifeq ($(strip $(OLED_SUPPORTED)), no)
    OLED_ENABLE=no
endif

ifeq ($(strip $(PRINTING_SUPPORTED)), no)
    PRINTING_ENABLE=no
endif

ifeq ($(strip $(PS2_MOUSE_SUPPORTED)), no)
    PS2_MOUSE_ENABLE=no
endif

ifeq ($(strip $(RGBLIGHT_SUPPORTED)), no)
    RGBLIGHT_ENABLE=no
endif

ifeq ($(strip $(RGB_MATRIX_SUPPORTED)), no)
    RGB_MATRIX_ENABLE=no
endif

ifeq ($(strip $(STENO_SUPPORTED)), no)
    STENO_ENABLE=no
endif

ifeq ($(strip $(SWAP_HANDS_SUPPORTED)), no)
    SWAP_HANDS_ENABLE=no
endif

ifeq ($(strip $(VISUALIZER_SUPPORTED)), no)
    VISUALIZER_ENABLE=no
endif

ifeq ($(strip $(WATCHDOG_SUPPORTED)), no)
    WATCHDOG_ENABLE=no
endif

ifeq ($(strip $(XT_SUPPORTED)), no)
    XT_ENABLE=no
endif
