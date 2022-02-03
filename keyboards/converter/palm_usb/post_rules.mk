ifdef HARDWARE_SERIAL
  # Untested with palm_usb
  SRC += protocol/serial_uart.c
  OPT_DEFS += -DHARDWARE_SERIAL
else
  SRC += protocol/serial_soft.c
endif
