os_detection_DEFS := -DOS_DETECTION_ENABLE
os_detection_DEFS += -DOS_DETECTION_DEBOUNCE=50

os_detection_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c

os_detection_debug_DEFS := $(os_detection_DEFS) -DOS_DETECTION_DEBUG_ENABLE -DVIA_ENABLE -DEEPROM_CUSTOM -DEEPROM_SIZE=1024
os_detection_debug_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection_debug.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(QUANTUM_PATH)/nvm/eeprom/nvm_os_detection.c \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom.c
