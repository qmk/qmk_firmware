COMMON_DIR = common
PLATFORM_COMMON_DIR = $(COMMON_DIR)/$(PLATFORM_KEY)

TMK_COMMON_SRC +=	\
	$(PLATFORM_COMMON_DIR)/platform.c \
	$(PLATFORM_COMMON_DIR)/suspend.c \
	$(PLATFORM_COMMON_DIR)/timer.c \
	$(PLATFORM_COMMON_DIR)/bootloader.c \

# Use platform provided print if it exists
-include $(TMK_PATH)/$(PLATFORM_COMMON_DIR)/printf.mk

# Search Path
VPATH += $(TMK_PATH)/$(COMMON_DIR)
VPATH += $(TMK_PATH)/$(PLATFORM_COMMON_DIR)
VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)
