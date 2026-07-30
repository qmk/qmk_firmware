# MAKEFLAGS += -j10

# VPATH += $(TOP_DIR)/keyboards/keymagichorse

# MCU 与 Bootloader
MCU = STM32F411
BOOTLOADER = stm32-dfu

# QMK 标准 Features
# BOOTMAGIC_ENABLE = yes
# MOUSEKEY_ENABLE = yes
# EXTRAKEY_ENABLE = yes
# NKRO_ENABLE = yes
# RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = ws2812

# 无线全部禁用
BLUETOOTH_ENABLE = no
