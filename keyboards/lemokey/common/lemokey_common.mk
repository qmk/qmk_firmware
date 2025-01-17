OPT_DEFS += -DFACTORY_TEST_ENABLE

LEMOKEY_COMMON_DIR = common
SRC += \
    $(LEMOKEY_COMMON_DIR)/lemokey_task.c \
    $(LEMOKEY_COMMON_DIR)/lemokey_common.c \
    $(LEMOKEY_COMMON_DIR)/lemokey_raw_hid.c \
    $(LEMOKEY_COMMON_DIR)/factory_test.c

VPATH += $(TOP_DIR)/keyboards/lemokey/$(LEMOKEY_COMMON_DIR)

