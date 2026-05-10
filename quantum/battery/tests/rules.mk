VPATH += $(DRIVER_PATH)/battery
VPATH += $(QUANTUM_PATH)/battery

battery_SRC := \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
	$(QUANTUM_PATH)/battery/battery.c \
	$(QUANTUM_PATH)/battery/tests/battery_tests.cpp \

battery_charger_SRC := \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
	$(QUANTUM_PATH)/battery/battery.c \
	$(QUANTUM_PATH)/battery/tests/battery_charger_tests.cpp \

battery_charger_DEFS := -DBATTERY_CHARGER_ENABLE \
                        -DBATTERY_CHARGER_CABLE_PIN=0 \
                        -DBATTERY_CHARGER_CABLE_ACTIVE_HIGH \
                        -DBATTERY_CHARGER_FULL_PIN=0 \
                        -DBATTERY_CHARGER_FULL_ACTIVE_HIGH
