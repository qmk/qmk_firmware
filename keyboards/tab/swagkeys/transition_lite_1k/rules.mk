# Build Options
#   change yes to no to disable
#
MCU_LDSCRIPT 		= STM32F103xB_uf2boot
BOARD 				= STM32_F103_STM32DUINO

BOOTLOADER			= uf2boot

SRC += transition_lite_1k_impl.c
SRC += ws2812_custom.c  # RGBLIGHT_ENABLE custom


BACKLIGHT_ENABLE 	= no


SLEEP_LED_ENABLE 	= no

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS 		   += -DCORTEX_ENABLE_WFI_IDLE=TRUE

LTO_ENABLE = yes

DEBOUNCE_TYPE 		= sym_eager_pk 
