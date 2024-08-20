#QUANTUM_LIB_SRC += analog.c

include keyboards/pcilabs/dapboot/dapboot.mk

MCU_FAMILY = STM32
MCU_SERIES = STM32F1xx

BOARD = STM32_F103_STM32DUINO

SRC += matrix.c lut.c scanfunctions.c custom_analog.c analog.c pcilabs_common.c matrix_common.c

MCU_LDSCRIPT = GD32F303xC-dapboot
BOOTLOADER = custom
SRC += dapboot/bootloader.c

RAW_ENABLE = yes
WAIT_FOR_USB = yes
NO_USB_STARTUP_CHECK = no

CUSTOM_MATRIX = lite

OPT = 2

WEAR_LEVELING_DRIVER = embedded_flash

CFLAGS += -fplan9-extensions
