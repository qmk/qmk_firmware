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

Flashing

ps2avr(GB) boards use an atmega32a microcontroller and a different bootloader. It is not flashable using the regular QMK methods.

To put the panc60 into reset, hold left control while plugging in.

Windows:

Download HIDBootFlash.
Place your keyboard into reset.
Press the Find Device button and ensure that your keyboard is found.
Press the Open .hex File button and locate the .hex file you created.
Press the Flash Device button and wait for the process to complete.
macOS:

Install homebrew by typing the following:
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
Install crosspack-avr.
brew cask install crosspack-avr
Install the following packages:
brew install python
brew install pyusb
brew install --HEAD`https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb

Place your keyboard into reset.
Flash the board by typing bootloadHID -r followed by the path to your .hex file.
See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

Go to Windows Device Manager and find the keyboard (plug it in while pressing 'Top Left Key' (USB on top)). It can be found under Human Interface Devices or under Keyboards.
Go to properties and the Details tab to find the hardware ID. You want the VID and the PID (code after the underscore). Plug them into HIDBootFlash and hit Find Device.
Use make ymdk_np21:<keymap-name> to generate the .hex file in the qmk base folder. Select the .hex file in HIDBootFlash and press Flash Device.
