
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = digital
# Inscrease stack size to avoid crushing of eeprom_update_block()
USE_PROCESS_STACKSIZE = 0x2000
USE_FPU = yes

include keyboards/lemokey/common/analog_matrix/analog_matrix.mk
include keyboards/lemokey/common/wireless/wireless.mk
include keyboards/lemokey/common/lemokey_common.mk

VPATH += $(TOP_DIR)/keyboards/lemokey

OPT_DEFS += -DSHARED_EP_ENABLE -DKEYBOARD_SHARED_EP
OPT_DEFS += -DXINPUT_ENABLE

OPT = 2
