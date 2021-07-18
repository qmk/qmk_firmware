# MCU name
MCU                 =   atmega32u4
BOOTLOADER          =   atmel-dfu

CUSTOM_MATRIX       =   yes
VIRTSER_ENABLE      =   no
NKRO_ENABLE         =   no
DEBOUNCE_TYPE       =   eager_pr

# Lets try and save some space eh?
MOUSEKEY_ENABLE     =   no
EXTRAKEY_ENABLE     =   no
CONSOLE_ENABLE      =   yes
COMMAND_ENABLE      =   no

VPATH               +=  keyboards/gboards/ 
SRC                 +=  matrix.c g/engine.c config_engine.c
QUANTUM_LIB_SRC     +=  i2c_master.c
OPT_DEFS            +=  -DONLYQWERTY 
LTO_ENABLE          =   yes
