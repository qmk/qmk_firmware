SRC += wanleg.c tapdances.c

TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes

#If using a ProMicro and it has the QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif

#use alternate settings for boards using ProMicro instead of Micro
#example usage: make 4x4:wanleg PM=yes
ifeq ($(strip $(PM)), yes)
	OPT_DEFS += -DPRO_MICRO
endif

#use alternate settings for boards using "Adafruit Feather 32u4 Bluefruit LE" instead of Micro
#example usage: make 5x5:wanleg BT=yes
ifeq ($(strip $(BT)), yes)
  #opt_defs for alternate pin usage
  OPT_DEFS += -DBLUEFRUIT
  #Adafruit Bluefruit controller settings
  BLUETOOTH = AdafruitBLE
  BLUETOOTH_ENABLE = yes
  F_CPU = 8000000
  CONSOLE_ENABLE = no 		# Console for debug(+400)
  COMMAND_ENABLE = no 		# Commands for debug and configuration
  RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
endif

#move numpad to Left/Centre/Right(default) on 5x15 boards
#example usage: make 4x4:wanleg padc=yes
ifeq ($(strip $(padc)), yes)
	OPT_DEFS += -DPADC
endif
ifeq ($(strip $(padl)), yes)
	OPT_DEFS += -DPADL
endif