os_detection_DEFS := -DOS_DETECTION_ENABLE
os_detection_DEFS += -DOS_DETECTION_DEBOUNCE=50
os_detection_DEFS += -DEEPROM_CUSTOM -DEEPROM_SIZE=1024

os_detection_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom.c \
    $(QUANTUM_PATH)/nvm/eeprom/nvm_eeconfig.c

os_detection_reset_DEFS := -DOS_DETECTION_ENABLE -DOS_DETECTION_KEYBOARD_RESET \
    -DOS_DETECTION_DEBOUNCE=50 -DOS_DETECTION_RESET_DEBOUNCE=100 \
    -DOS_DETECTION_DEBUG_ENABLE -DOS_DETECTION_DEBUG_AUTO_STORE -DCONSOLE_ENABLE \
    -DMATRIX_ROWS=2 -DMATRIX_COLS=2 -DEEPROM_CUSTOM -DEEPROM_SIZE=1024 \
    -DVIA_ENABLE -DVIA_EEPROM_MAGIC_ADDR=124 -DVIA_EEPROM_CUSTOM_CONFIG_SIZE=104 \
    -DOS_DETECTION_DEBUG_EEPROM_ADDR=VIA_EEPROM_CUSTOM_CONFIG_ADDR

os_detection_reset_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection_reset.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom.c \
    $(QUANTUM_PATH)/nvm/eeprom/nvm_eeconfig.c \
    $(QUANTUM_PATH)/process_keycode/process_quantum.c

os_detection_reset_override_DEFS := $(os_detection_reset_DEFS) -DOS_DETECTION_SKIP_RESET_KEY=KC_F12 -DOS_DETECTION_SINGLE_REPORT
os_detection_reset_override_SRC := $(os_detection_reset_SRC)

os_detection_reset_guard_DEFS := $(filter-out -DVIA_EEPROM_CUSTOM_CONFIG_SIZE=104,$(os_detection_reset_DEFS)) \
    -DOS_DETECTION_BOOT_LOOP_GUARD -DVIA_EEPROM_CUSTOM_CONFIG_SIZE=111 \
    -DOS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR=232
os_detection_reset_guard_SRC := $(os_detection_reset_SRC)

os_detection_split_DEFS := $(os_detection_DEFS) -DSPLIT_KEYBOARD -DSPLIT_DETECTED_OS_ENABLE -DMATRIX_ROWS=2 -DMATRIX_COLS=2
os_detection_split_SRC := \
    $(QUANTUM_PATH)/os_detection/tests/os_detection_split.cpp \
    $(QUANTUM_PATH)/os_detection.c \
    $(PLATFORM_PATH)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c \
    $(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom.c \
    $(QUANTUM_PATH)/nvm/eeprom/nvm_eeconfig.c
