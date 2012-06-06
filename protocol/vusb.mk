OPT_DEFS += -DHOST_VUSB

SRC +=	vusb.c \
	usbdrv.c \
	usbdrvasm.S \
	oddebug.c \
	bootloader_usbasp.c \


ifdef NO_UART
SRC +=	sendchar_null.c
else
SRC +=	sendchar_uart.c \
	uart.c
endif


# Search Path
VPATH += $(COMMON_DIR)/vusb:$(COMMON_DIR)/vusb/usbdrv
