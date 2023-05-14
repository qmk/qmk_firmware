SRC += irq.S matrix.c start_core1.c c1_main.c
CUSTOM_MATRIX = lite

OPT_DEFS += -DCRT0_EXTRA_CORES_NUMBER=1

SRC += lib/Pico-PIO-USB/src/pio_usb.c
SRC += lib/Pico-PIO-USB/src/pio_usb_host.c
SRC += lib/Pico-PIO-USB/src/usb_crc.c
VPATH += keyboards/sekigon/keyboard_quantizer/mini/lib/Pico-PIO-USB/src

SRC += lib/tinyusb/src/tusb.c
SRC += lib/tinyusb/src/common/tusb_fifo.c
SRC += lib/tinyusb/src/host/usbh.c
SRC += lib/tinyusb/src/host/hub.c
SRC += lib/tinyusb/src/class/hid/hid_host.c
SRC += lib/tinyusb/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
VPATH += keyboards/sekigon/keyboard_quantizer/mini/lib/tinyusb/src
VPATH += keyboards/sekigon/keyboard_quantizer/mini/lib/tinyusb/src/host
VPATH += keyboards/sekigon/keyboard_quantizer/mini/lib/tinyusb/src/common
VPATH += keyboards/sekigon/keyboard_quantizer/mini/lib/tinyusb/src/class/hid

SRC += lib/pico-sdk/src/rp2_common/hardware_dma/dma.c
SRC += lib/pico-sdk/src/rp2_common/hardware_irq/irq.c
SRC += lib/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S
SRC += lib/pico-sdk/src/rp2_common/hardware_sync/sync.c
SRC += lib/pico-sdk/src/common/pico_sync/mutex.c
SRC += lib/pico-sdk/src/common/pico_sync/critical_section.c
SRC += lib/pico-sdk/src/common/pico_sync/lock_core.c
SRC += lib/pico-sdk/src/common/pico_time/time.c
SRC += lib/pico-sdk/src/common/pico_util/pheap.c
SRC += lib/pico-sdk/src/host/pico_stdlib/stdlib.c
VPATH += lib/pico-sdk/src/rp2_common/hardware_dma/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_uart/include
VPATH += lib/pico-sdk/src/rp2_common/pico_stdio/include
VPATH += lib/pico-sdk/src/rp2_common/pico_multicore/include
VPATH += lib/pico-sdk/src/common/pico_stdlib/include
VPATH += lib/pico-sdk/src/common/pico_time/include
VPATH += lib/pico-sdk/src/common/pico_sync/include
VPATH += lib/pico-sdk/src/common/pico_util/include