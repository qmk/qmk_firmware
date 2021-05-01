# MCU name
MCU = STM32F072

CONSOLE_ENABLE = no
COMMAND_ENABLE = no
ENCODER_ENABLE = no
EXTRAKEY_ENABLE = yes
OLED_DRIVER_ENABLE = no
WPM_ENABLE = no
MOUSEKEY_ENABLE  = yes

# Laptop users may want to enable low-power on idle thread
# OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave