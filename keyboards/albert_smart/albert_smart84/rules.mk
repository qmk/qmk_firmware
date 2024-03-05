MCU_LDSCRIPT = STM32F103xB

DEFERRED_EXEC_ENABLE = yes


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

ENCODER_MAP_ENABLE = yes
DYNAMIC_KEYMAP_ENABLE = yes

SRC +=   analog.c

DEBOUNCE_TYPE = sym_eager_pr
