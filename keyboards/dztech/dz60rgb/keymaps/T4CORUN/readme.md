# T4CORUN DZ60RGB V2

- This is my keymap for a [DZ60RGB V2](https://kbdfans.com/products/dz60rgb-hot-swap-custom-keyboard-pcb)
- I bought the keyboard after their .1 revision so it has weird instructions. I can still use QMK Toolbox to flash it
- This is mostly a standard keyboard I will use to game on
- QMK Compile Command:

	```Makefile
	qmk compile -kb dztech/dz60rgb/v2_1 -km T4CORUN
	```

## Changelog

2021-12-12

- Initial keymap for this board
- Implemented wrappers. Laid it out so it is somewhat close to my planck and corne. Tweaked my wrappers.h file to make num rows and function key rows.
- Enabled Grave Escape
