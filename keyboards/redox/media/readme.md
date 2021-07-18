# The Redox Media Keyboard

I've taken the Redox keyboard and modified the SCAD files as well as the QMK layout to include media and scroll features:
- 3 Media buttons
    - Play / Pause button
    - Next track
    - Mute (previous track on secondary layout)
- Volume knob
- Scroll wheel on the keyboard

For an in-depth report see [my page](https://shiftux.org/making_projects/keyboard.html) and a [video](https://youtu.be/Cwkf7HFcUkY) about the build process, design, printing, programing and assembly.

## IMAGE

### The build
I've used 2 [Sparkfun Pro Micros (5V)](https://www.sparkfun.com/products/12640) and a single hand master setup providing power and serial connection via a TRS jack.

### The pro micro and how to flash it
To try out your pro micro and setup your environment to flash such a device I recommend following [this guide](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all). It will take you through the install and setup and provides a first easy to flash program so you can test your setup quickly.

Whenever you can't program one of the pro micros or the USB-COM port is not found on your computer, it most probably means that is is not in "bootloader mode". What you want to do is connect the GND and RST pin twice to reset the device and put it into bootloader mode (details [here](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/troubleshooting-and-faq#ts-serial)).

To find out how your serial port is called on your computer, you can find it with the following command:
```
ll /dev | grep "tty\."
```
Mine is called `/dev/tty.usbmodem14522301` for example.

### Compiling and flashing

Obviously start by [installing QMK](https://docs.qmk.fm/#/getting_started_build_tools?id=set-up-your-environment).

- Before flashing the firmware you should make sure that it compiles. Thus assuring that your QMK setup works fine and the keyboard and keymap files are correct:
```
qmk compile -kb redox/media -km media-CH
```
The generated files are output to the `.build` directory in the QMK root. You'll want the `.hex` file.

Once you are comfortable flashing your Pro Micros and your setup works continue with the following steps:

- I've had the most success with using the `EE_HANDS` setting and flashing the EEPROM to the left and right halves of the keyboard respectively. To do this start with flashing the EEPROM of the 2 pro micros separately by setting the bootloader flag in the flash command (the pro micro uses the avrdude bootloader):
```
qmk flash -kb redox/media -km media-CH -bl avrdude-split-left
qmk flash -kb redox/media -km media-CH -bl avrdude-split-right
```
Note that you need to reset the pro micro to set it to bootloader mode before you can flash it: connect GND to RST twice in quick succession (750ms), then you have 8 seconds to upload the new eep file.

- For completeness this is the avrdude command with which you could manually do the flashing steps, you might want to use it for debugging. Make sure to set the correct port for flashing (`ll /dev | grep "tty\."`):
```
avrdude -p atmega32u4 -c avr109 -U flash:w:./.build/redox_media_media.hex:i -P /dev/tty.usbmodem14522301
```

### Adapting the keyboard layout

Copy the `keymaps/media-CH` folder to `keymaps/media-<your-layout>` and adapt the `keymap.c` file in there.

I recommend testing the key codes with the [QMK tester](https://config.qmk.fm/#/test) and then adapting the `keymap.c` file accordingly.

Finally compile your new layout from the QMK root with:
```
qmk compile -kb redox/media -km media-<your-layout>
```
and proceed to flashing it equivalent to the above instructions.

### CAD files and additional resources
See [here](https://shiftux.org/making_projects/keyboard.html) for a detailed build description and video.

You can find the CAD and SCAD files, I created here: https://github.com/shiftux/redox-media-keyboard