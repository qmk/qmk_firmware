# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_ANNEPRO2_C2D
MCU_STARTUP = ht32f523xx

BOARD = ANNEPRO2_C2D

# Bootloader selection
BOOTLOADER = custom
PROGRAM_CMD = annepro2_tools --boot $(BUILD_DIR)/$(TARGET).bin

# Anne Pro 2D: GPIO and BLE only. Direct-drive RGB is intentionally deferred.
SRC = \
	annepro2_ble_transport.c \
	annepro2_ble_profile.c \
	annepro2_ble_213_slot.c \
	annepro2_ble_parser.c \
	annepro2_ble_state.c
