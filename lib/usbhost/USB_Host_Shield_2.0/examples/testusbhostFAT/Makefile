#
# These are set for a mega 1280 + quadram plus my serial patch.
# If you lack quadram, or want to disable LFN, just change _FS_TINY=1 _USE_LFN=0
#
# If your board is a mega 2560 comment out the following two lines
BOARD = mega

BOARD_SUB = mega.menu.cpu.atmega1280
PROGRAMMER = arduino

# ...and then uncomment out the following two lines
#BOARD_SUB = mega.menu.cpu.atmega2560
#PROGRAMMER = wiring

#BOARD = teensypp2
#BOARD = teensy3
#BOARD = teensy31

# set your Arduino tty port here
PORT = /dev/ttyUSB0

EXTRA_FLAGS = -D _USE_LFN=3

# change to 0 if you have quadram to take advantage of caching FAT
EXTRA_FLAGS += -D _FS_TINY=1


EXTRA_FLAGS += -D _MAX_SS=512


# Don't worry if you don't have external RAM, xmem2 detects this situation.
# You *WILL* be wanting to get some kind of external ram on your mega in order to
# do anything that is intense.
EXTRA_FLAGS += -D EXT_RAM_STACK=1
EXTRA_FLAGS += -D EXT_RAM_HEAP=1


# These are no longer needed for the demo to work.
# In the event you need more ram, uncomment these 3 lines.
#EXTRA_FLAGS += -D DISABLE_SERIAL1
#EXTRA_FLAGS += -D DISABLE_SERIAL2
#EXTRA_FLAGS += -D DISABLE_SERIAL3

#
# Advanced debug on Serial3
#

# uncomment the next two to enable debug on Serial3
EXTRA_FLAGS += -D USB_HOST_SERIAL=Serial3
#EXTRA_FLAGS += -D DEBUG_USB_HOST

# The following are the libraries used.
LIB_DIRS += ../../
LIB_DIRS += ../testusbhostFAT/xmem2
LIB_DIRS += ../testusbhostFAT/generic_storage
LIB_DIRS += ../testusbhostFAT/RTClib
LIB_DIRS += $(ARD_HOME)/libraries/Wire
LIB_DIRS += $(ARD_HOME)/libraries/Wire/utility
LIB_DIRS += $(ARD_HOME)/hardware/arduino/$(BUILD_ARCH)/libraries/Wire
LIB_DIRS += $(ARD_HOME)/hardware/arduino/$(BUILD_ARCH)/libraries/Wire/utility
LIB_DIRS += $(ARD_HOME)/hardware/arduino/$(BUILD_ARCH)/libraries/SPI

# And finally, the part that brings everything together for you.
include Arduino_Makefile_master/_Makefile.master
