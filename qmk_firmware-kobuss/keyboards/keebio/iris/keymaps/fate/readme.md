# Fate Iris Layout

This keymap is configured for Pro Micro(s) with QMK-DFU bootloader flashed. Please refer to [this guide](https://www.reddit.com/r/olkb/comments/8sxgzb/replace_pro_micro_bootloader_with_qmk_dfu/) for further details on ISP flashing your Pro Micro.

To generate a production-ready .hex file (containing the application and the bootloader), use the production target

    make iris/rev2:fate:production

To replace your Pro Micro with QMK-DFU bootloader along with the keymap, setup your ISP Flasher and avrdude, run (This command assumes you're using SparkFun's Pocket AVR Programmer to program):

    $ avrdude -p m32u4 -P usb -c usbtiny -U flash:w:"iris_rev2_fate_production.hex" -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m -v

Command to replace your Pro Micro with QMK-DFU bootloader only:

    $ avrdude -p m32u4 -P usb -c usbtiny -U flash:w:"iris_rev2_fate_bootloader.hex" -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m -v

The QMK_ESC is mapped to the ESC key in keymap.c; QMK_LED is mapped to TX_LED on the Pro Micro.

    /* QMK DFU configuration */
    #define QMK_ESC_OUTPUT F6
    #define QMK_ESC_INPUT D7
    #define QMK_LED     D5
    #define QMK_SPEAKER C6
