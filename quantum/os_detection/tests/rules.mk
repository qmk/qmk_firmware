os_detection_DEFS := -DOS_DETECTION_ENABLE
os_detection_DEFS += -DOS_DETECTION_DEBOUNCE=50

os_detection_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c
