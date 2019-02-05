
 # YMDK NP21

![kp21 &mdash; full grid layout](https://ae01.alicdn.com/kf/HTB1LvJ3grSYBuNjSspiq6xNzpXaO/21-Key-YMDK-Side-printed-Blank-Top-printed-Thick-PBT-ABS-Keycap-For-MX-Switches-Mechanical.jpg)

ps2avrGB based number-pad sold fully assembled by YMDK on Aliexpress.

Keyboard Maintainer: [QMK Community](https://github.com/qmk)

Hardware Supported: Atmega32A

Hardware Availability: [AliExpress](https://www.aliexpress.com/item/21-Key-NPKC-Programmable-Cherry-MX-Kailh-Gateron-Switches-Mechanical-Keyboard-Numpad-Free-shipping/32812732361.html)

	Make example for this keyboard (after setting up your build environment):

	    make ymdk_np21:default:program

	See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

	Note that this is a complete replacement for the firmware, so you won't be
	using Bootmapper Client to change any keyboard settings, since not all the
	USB report options are supported.

	In addition you may need the AVR toolchain and `bootloadHID` ([GitHub repo](https://github.com/whiteneon/bootloadHID)) for flashing:

	For macOS:
	```
	$ brew cask install crosspack-avr
	$ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
	```

	For Linux:
	```
	$ sudo apt install libusb-dev
	$ wget https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz
	$ tar -xzf bootloadHID.2012-12-08.tar.gz
	$ cd bootloadHID.2012-12-08/commandline
	$ make
	$ sudo cp bootloadHID /usr/bin
	```

	In order to use the `./program` script, which can reboot the board into
	the bootloader, you'll need Python 2 with PyUSB installed:

	```
	$ pip install pyusb
	```

	If you prefer (or are having issues with a `program` flash), you can just build it (`make jj40:<keymap-name>` and flash the firmware (`.hex` file) directly with
	`bootloadHID` if you boot the board while holding down `8` (second from top, second from left, with usb plug is at the top) to keep it
	in the bootloader:

	```
	$ make ymdk_np21
	$ bootloadHID -r ymdk_np21_default.hex
	```
  You may have to  sudo to get past the broken pipe message.

	For Windows 10:
	Windows sometimes doesn't recognize the ymdk_np21. The easiest way of flashing a new layout is probably using [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash).
	1. Go to Windows Device Manager and find the keyboard (plug it in while holding down `ESC` (top left key, when the usb plug is at the top)). It can be found under Human Interface Devices or under Keyboards.
	2. Go to properties and the Details tab to find the hardware ID. You want the VID and the PID (code after the underscore). Plug them into HIDBootFlash and hit Find Device.
	3. Use `make ymdk_np21:<keymap-name>` to generate the .hex file in the qmk basis folder. Select the .hex file in HIDBootFlash and press Flash Device.


	## Troubleshooting

	1. Try plugging the board in while pressing `ESC` (usb plug at top, top left key). This will force it
	   to boot only the bootloader without loading the firmware. Once this is
	   done, just reflash the board with the original firmware.
	2. Sometimes USB hubs can act weird, so try connecting the board directly
	   to your computer or plugging/unplugging the USB hub.
	3. If you get an error such as "Resource Unavailable" when attemting to flash
	   on Linux, you may want to compile and run `tools/usb_detach.c`. See `tools/README.md`
	   for more info.

copied almost verbatium from [Keyboard] Add support for jj4x4 numpad/macropad by Kprepublic (#5016)
