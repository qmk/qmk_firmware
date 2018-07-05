TAP_DANCE_ENABLE = yes		# Enable Tap Dance (comment if not being implemented)

#If ProMicro has QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif