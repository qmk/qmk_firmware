# TADA68 (65% ATMega32U4 PCB)

The TADA68 comes with a custom firmware based on the LUFA mass storage
driver, which mounts the user-accessible portion of the flash storage
as a USB drive. This is prone to failure and can only be accessed by
hitting the physical reset button on the base of the board, which is
relatively accessible in an assembled keyboard.

This keymap has some customisation to work with a TADA68 which has been
ISP-reflashed (using a USBasp or other ISP) to work with the QMK bootloader.

This allows use of dfu-programmer to reflash the firmware in DFU mode, and
bootloader entry and exit with key-combos.

To build the firmware, set up a build environment according to the standard
QMK instructions, then run:

```make tada68:tokyovigilante:production```

which will build the bootloader, user firmware, and the combined image `<keyboard>_<keymap>_production.hex`.

Then run

```avrdude -F -c usbasp -p m32u4 -e -U flash:w:tada68_tokyovigilante_production.hex:a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m -U lock:w:0x3F:m```

to copy it to your board (connected to the USBasp or other programmer, replacing the -c and filename parameters as required). The fuse and lock
bitmaps will enable DFU mode.

Once the board is unplugged and plugged in via USB, the default key-combo to
enter DFU mode is Fn-Meta-R, then Esc to exit. You can then use 
`make tada68:<keymap>:dfu` to build and flash any other custom keymap you 
like, as the qmk-dfu bootloader can only be replaced using the ISP. This keymap is fairly basic, just make sure any replacement one has a RESET command defined (ideally on a non-default layer).

More information can be found in the QMK docs: <https://docs.qmk.fm>
