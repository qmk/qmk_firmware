
QUANTUM_LIB_SRC += uart.c
MCU_LDSCRIPT = STM32F103xB

DEFERRED_EXEC_ENABLE = yes


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
#OLED_ENABLE = yes
#OLED_TRANSPORT = spi

ENCODER_MAP_ENABLE = yes
# ENCODER_ENABLE = yes

DYNAMIC_KEYMAP_ENABLE = yes


SRC +=   analog.c
#		 smart_ble.c
#		 //
#		 disable_swd.c

DEBOUNCE_TYPE = sym_eager_pr
