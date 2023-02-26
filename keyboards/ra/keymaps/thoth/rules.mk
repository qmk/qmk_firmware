VPATH += keyboards/gboards
SRC += \
  feature/shift_keys/custom_shift_keys.c

COMBO_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
LEADER_ENABLE = yes
CONSOLE_ENABLE = yes
REPLAY_ENABLED = no
MULTI_ENABLED = no
RAW_ENABLE = yes

EE_CONFIG_FILE = eeprom_driver_stm32.c
