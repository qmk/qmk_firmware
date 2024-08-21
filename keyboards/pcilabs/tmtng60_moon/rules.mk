MCU_FAMILY = STM32
MCU_SERIES = STM32F1xx
BOARD = STM32_F103_STM32DUINO

MCU_LDSCRIPT = GD32F303xC-dapboot
BOOTLOADER = custom
SRC += keyboards/pcilabs/pcilabs_common/dapboot/bootloader.c

include keyboards/pcilabs/pcilabs_common/pcilabs_common.mk
include keyboards/pcilabs/pcilabs_common/multiplexer/multiplexer.mk

RAW_ENABLE = yes
WAIT_FOR_USB = yes
NO_USB_STARTUP_CHECK = no

WEAR_LEVELING_DRIVER = embedded_flash

OPT = 2
CFLAGS += -fplan9-extensions

CUSTOM_MATRIX = lite
SRC += matrix.c

