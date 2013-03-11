IWRAP_DIR = protocol/iwrap

OPT_DEFS += -DPROTOCOL_IWRAP

SRC +=	$(IWRAP_DIR)/iwrap.c \
	$(IWRAP_DIR)/suart.S \
	$(IWRAP_DIR)/sendchar_uart.c \
	$(IWRAP_DIR)/uart.c


# Search Path
VPATH += $(TOP_DIR)/protocol/iwrap
