# MCU name and parameters
MCU = RP2040
F_CPU = 125000000
BOOTLOADER = rp2040
PLATFORM = rp2040

# RGB Matrix configuration
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor
RGB_MATRIX_FRAMEBUFFER_EFFECTS = yes
RGB_MATRIX_KEYPRESSES = yes
RGB_MATRIX_TYPING_HEATMAP = yes
RGB_MATRIX_CUSTOM_KB = no
RGB_MATRIX_CUSTOM_USER = no
RGBLIGHT_SLEEP = yes

# Include custom RGB effects
SRC += rgb_effects.c

# Keyboard features
DYNAMIC_MACRO_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
KEY_LOCK_ENABLE = yes
LTO_ENABLE = yes

# Disabled features (to save space and optimize)
DISABLE_ADC = yes
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no
AUDIO_ENABLE = no
LEADER_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# Include paths for QMK firmware headers (required for RP2040)
EXTRAFLAGS += -I"$(QUANTUM_DIR)" -I"$(PLATFORM_DIR)" -I"$(CHIBIOS_DIR)/os/license" -I"$(CHIBIOS_DIR)/os/hal/include" -I"$(CHIBIOS_DIR)/os/hal/ports/$(MCU)" -I"$(CHIBIOS_DIR)/os/hal/ports/$(MCU)/LLD" -I"$(CHIBIOS_DIR)/os/hal/lib/streams" -I"$(CHIBIOS_DIR)/os/kernel/include" -I"$(CHIBIOS_DIR)/os/various"