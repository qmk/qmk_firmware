USB_HID_DIR = protocol/usb_hid


#
# USB Host Shield
#
USB_HOST_SHIELD_DIR = $(USB_HID_DIR)/USB_Host_Shield_2.0
USB_HOST_SHIELD_SRC = \
	$(USB_HOST_SHIELD_DIR)/Usb.cpp \
	$(USB_HOST_SHIELD_DIR)/hid.cpp \
	$(USB_HOST_SHIELD_DIR)/usbhub.cpp \
	$(USB_HOST_SHIELD_DIR)/parsetools.cpp \
	$(USB_HOST_SHIELD_DIR)/message.cpp 



#
# Arduino
#
ARDUINO_DIR = $(USB_HID_DIR)/arduino-1.0.1
ARDUINO_CORES_DIR = $(ARDUINO_DIR)/cores/arduino
ARDUINO_CORES_SRC = \
	$(ARDUINO_CORES_DIR)/Print.cpp \
	$(ARDUINO_CORES_DIR)/Stream.cpp

# replaced with override_Serial.c
#	$(ARDUINO_CORES_DIR)/CDC.cpp \
#	$(ARDUINO_CORES_DIR)/HID.cpp \
#	$(ARDUINO_CORES_DIR)/USBCore.cpp \

# replaced with override_wiring.c and common/timer.c
#	$(ARDUINO_CORES_DIR)/wiring.c \



#
# HID parser
#
SRC += $(USB_HID_DIR)/parser.cpp

# replace arduino/CDC.cpp
SRC += $(USB_HID_DIR)/override_Serial.cpp

# replace arduino/wiring.c
SRC += $(USB_HID_DIR)/override_wiring.c
SRC += common/avr/timer.c

SRC += $(USB_HOST_SHIELD_SRC)
SRC += $(ARDUINO_CORES_SRC)


OPT_DEFS += -DARDUINO=101
# Arduino USBCore needs USB_VID and USB_PID.
#OPT_DEFS += -DARDUINO=101 -DUSB_VID=0x2341 -DUSB_PID=0x8036



#
# Search Path
#
VPATH += $(TMK_DIR)/$(USB_HID_DIR)
VPATH += $(TMK_DIR)/$(USB_HOST_SHIELD_DIR)

# for #include "Arduino.h"
VPATH += $(TMK_DIR)/$(ARDUINO_CORES_DIR)

# for #include "pins_arduino.h"
VPATH += $(TMK_DIR)/$(ARDUINO_DIR)/variants/leonardo

# ad hoc workaround for compile problem on Windows:
#    Windows doesn't know difference between common/print.h and arduino/Print.h.
#    On Linux no problem.
#    Change file name common/print.h to console.h ?
VPATH := $(TMK_DIR)/common $(VPATH)
