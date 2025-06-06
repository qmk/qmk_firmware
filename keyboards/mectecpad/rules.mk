# MCU and board definitions
MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040
VIA_ENABLE = yes
RP2040_PWM_ENABLE = yes
FLASH_SIZE = 2MB         # Replace with your flash memory size

# Features to optimize firmware size
LTO_ENABLE = yes         # Enable Link Time Optimization for smaller firmware
EXTRAFLAGS += -Os        # Optimize for size

VIA_ENABLE = yes          # Enable VIA support