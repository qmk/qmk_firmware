See the [main readme](../readme.md) for more details. 

This is just the rev 1.001-1.004 trackball

# Programming QMK-DFU onto the PloopyCo Trackball (Advanced)

If you would rather have DFU on this board, you can use the QMK-DFU bootloader on the device.  To do so, you want to run: 

    make ploopyco/trackball:default:production

Once you have that, you'll need to [ISP Flash](https://docs.qmk.fm/#/isp_flashing_guide) the chip with the new "production" hex file created (or the production hex), and set the fuses:


| Fuse     | Setting          |
|----------|------------------|
| Low      | `0xDF`           |
| High     | `0xD8` or `0x98` |
| Extended | `0xCB`           |

Original (Caterina) settings: 

| Fuse     | Setting          |
|----------|------------------|
| Low      | `0xFF`           |
| High     | `0xD8`           |
| Extended | `0xFE`           |

If you're using QMK DFU, you'll also need to add `BOOTLOADER=qmk-dfu` to your keymap's rules.mk file, to ensure that the reboot/reset works correctly. Otherwise, it will jump right back into the firmware, like nothing happened.

Additionally, once you've flashed the qmk-dfu bootloader onto your device, you will no longer be able to use the Arduino IDE to flash the board. You'll need to use the command line or QMK Toolbox to flash it. 
