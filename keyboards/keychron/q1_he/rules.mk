
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = digital
# Inscrease stack size to avoid crushing of eeprom_update_block()
USE_PROCESS_STACKSIZE = 0x2000
USE_FPU = yes

include keyboards/keychron/common/analog_matrix/analog_matrix.mk
include keyboards/keychron/common/keychron_common.mk
include keyboards/keychron/common/wireless/wireless.mk

VPATH += $(TOP_DIR)/keyboards/keychron
#SRC += $(TOP_DIR)/keyboards/keychron/gpio_uart.c

OPT_DEFS += -DSHARED_EP_ENABLE -DKEYBOARD_SHARED_EP
OPT_DEFS += -DXINPUT_ENABLE

#CDEFS += -lc -lrdimon -u _printf_float
#OPT_DEFS += -DCH_DBG_ENABLE_CHECKS=TRUE  -DCH_DBG_ENABLE_ASSERTS=TRUE -DCH_DBG_SYSTEM_STATE_CHECK=TRUE
#OPT_DEFS += -DCH_DBG_TRACE_MASK=CH_DBG_TRACE_MASK_ALL
#CFLAGS += -Wl,--print-memory-usage

OPT = 2
