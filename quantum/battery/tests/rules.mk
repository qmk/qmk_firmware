VPATH += $(DRIVER_PATH)/battery

battery_SRC := \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
	$(QUANTUM_PATH)/battery/battery.c \
	$(QUANTUM_PATH)/battery/tests/battery_tests.cpp \
