### This Keymap uses the nanoBoot bootloader to maximize available firmware space.

As is, the firmware will be too large if using the standard bootloader.  Removing `DEBOUNCE_TYPE = sym_eager_pk` from the `rules.mk` should get the size under the limit.

If nanoBoot is not going to be used, delete or comment out the following from your `rules.mk`:
```make
BOOTLOADER = hid
BOOTLOADER_SIZE = 512
PROGRAM_CMD = 	$(HID_BOOTLOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
```

nanoBoot can be found here: [nanoBoot](https://github.com/sigprof/nanoBoot) I used the string-descriptors branch as it was the latest update.

To ISP Flash nanoBoot: `avrdude -p atmega32u4 -c avrisp -U flash:w:/Users/DempseyTech/nanoBoot/nanoBoot.hex:i -P /dev/cu.usbmodem123451 -U lfuse:w:0x7F:m -U hfuse:w:0xD6:m -U efuse:w:0xC7:m`

You will need to change the path in the CLI command to match your file structure.

QMK Toolbox will not recognize controllers using nanoBoot, instead use the CLI to flash.

To Flash: `qmk flash -kb splitkb/kyria/rev1 -km john-ezra -bl hid_bootloader`
