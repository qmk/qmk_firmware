# custom bootloader
OPT_DEFS += -DBOOTLOADER_SIZE=1862
PROGRAM_CMD = micronucleus --run $(BUILD_DIR)/$(TARGET).hex
