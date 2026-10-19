# NXP LPC11U35 Onekey

To trigger keypress, short together pins *A16* (PIO0_16) and *A17* (PIO0_17).

Port 0 is `A`, port 1 is `B`.

The chip has no bootloader that QMK can flash through. Hold PIO0_1 low at reset to get the ROM's USB mass storage mode and replace `firmware.bin` with the `.bin` file.
