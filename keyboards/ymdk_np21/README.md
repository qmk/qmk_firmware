# YMDK NP21

![kp21 &mdash; full grid layout](https://ae01.alicdn.com/kf/HTB1d.txfHsTMeJjSszhq6AGCFXaF.jpg?size=35021&height=662&width=1000&hash=62b3a453686e2154dc51a7af67495e28)

ps2avrGB based number-pad sold fully assembled by YMDK on Aliexpress.

Keyboard Maintainer: [QMK Community](https://github.com/qmk)  
Hardware Supported: Atmega32A
Hardware Availability: [AliExpress](https://www.aliexpress.com/item/21-Key-NPKC-Programmable-Cherry-MX-Kailh-Gateron-Switches-Mechanical-Keyboard-Numpad-Free-shipping/32812732361.html)

Make example for this keyboard (after setting up your build environment):

    make ymdk_np21:default:program

Plugging the board in while pressing 'Top Left Key' (USB on top) will force it to boot bootloader without loading the firmware.

The code for NP21 is a minor edit of jj40.

For Windows 10: Windows sometimes doesn't recognize the NP21. The easiest way of flashing a new layout is probably using [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash).

Go to Windows Device Manager and find the keyboard (plug it in while pressing 'Top Left Key' (USB on top)). It can be found under Human Interface Devices or under Keyboards.
Go to properties and the Details tab to find the hardware ID. You want the VID and the PID (code after the underscore). Plug them into HIDBootFlash and hit Find Device.
Use make ymdk_np21:<keymap-name> to generate the .hex file in the qmk base folder. Select the .hex file in HIDBootFlash and press Flash Device.
