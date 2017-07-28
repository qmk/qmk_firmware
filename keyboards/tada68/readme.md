TADA68 keyboard firmware
========================

1) from the keyboards/tada68 directory run:
```
$ make flashbin
```

2) hit the reset button on the TADA, the lights will start flashing.

3) You'll see a new drive on your computer called TADA68. Backup the original factory `FLASH.BIN` file thats inside it.

4) Delete `FLASH.BIN` from the TADA drive and copy `tada68_default.bin` that was generated at the root of the qmk directory into the TADA drive.

5) Hit ESC on the keyboard. The lights will stop flashing and your firmware is loaded!