VPATH += $(DRIVER_PATH)/wireless

wireless_2p4ghz_SRC := \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
	$(DRIVER_PATH)/wireless/wireless_2p4ghz.c \
	$(QUANTUM_PATH)/connection/tests/wireless_2p4ghz_tests.cpp \

wireless_2p4ghz_DEFS := -DWIRELESS_2P4GHZ_ENABLE
