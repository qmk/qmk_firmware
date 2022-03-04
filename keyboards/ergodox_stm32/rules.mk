# MCU name
MCU = STM32F103
MCU_LDSCRIPT = stm32f103_bootloader
BOARD = ST_NUCLEO64_F103RB

# Bootloader selection
BOOTLOADER = custom

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
CUSTOM_MATRIX = yes # Custom matrix file
UNICODE_ENABLE   = yes # Unicode

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
