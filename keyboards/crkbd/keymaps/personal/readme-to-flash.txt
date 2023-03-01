how to flash the keyboard

1.- uncomment SPLIT_USB_HANDS and EE_HANDS in config.h and comment MASTER_RIGHT.
2.- make crkbd/rev1:personal:avrdude...
         avrdude-split-left and split-right for left and right side.
3.- revert step one.
4.- connect the right side and flash: make crkbd/rev1:personal:avrdude
