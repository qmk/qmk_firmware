# Matrix

A rugged four-button macro pad with a per-key customisable RGB backlight. For more information, see: https://zoid.com.au/matrix/

## Compiling

To compile the firmware with the default keymap, use the following command:

	qmk compile -kb sevencrumbs/matrix -km default

[VIA](https://usevia.app/) is recommended for easily customising the keymap and backlight colour. To compile the firmware with VIA support, use the following command:

	qmk compile -kb sevencrumbs/matrix -km via

## Bootloader

Press and hold all four buttons while connecting the USB cable to erase all settings and enter the bootloader.
