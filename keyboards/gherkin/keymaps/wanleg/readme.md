![Gherkin Wanleg Layout Image](https://i.imgur.com/mXsgoro.png)

# Gherkin Wanleg Layout
Here is the layout I came up with to preserve a standard QWERTY layout as much as possible, in as few layers as possible for a 30 key board.
I originally set up a few Tap Dance keys, but dropped half of them in favor of chorded versions, since in actual use, they tended to impede typing speed more than their (current) two-key versions.
I've left them in my layout ready for use if anyone wants to try them out:

Legend Name | Single Tap | Double Tap | Hold
--- | --- | --- | ---
*null* | space | enter | shift
*null* | backspace | delete | control
Sft//Cp | shift | caps lock | *null*
Q//Esc | KC_Q | escape | *null*

# Gherkin Flashing
## Linux
The ProMicro doesn't like dfu-programmer, so we have to use AVRdude. What follows below are instructions for Linux taken from https://deskthority.net/workshop-f7/how-to-use-a-pro-micro-as-a-cheap-controller-converter-like-soarer-s-t8448.html

`ls /dev/tty*`

Next, plug in your device and re-run the command, the same as before:

`ls /dev/tty*`

There should be one more output device than was seen previously. For me, it's /dev/ttyACM0.
To flash the device, you need to have AVRdude installed. On Linux, you can do this with your normal package manager.
Once you have AVRdude set up, navigate to the directory with your .hex file in it. Then, run the following:

`avrdude -p atmega32u4 -P YOUR_SERIAL_PORT  -c avr109  -U flash:w:YOUR_FILENAME.hex`

Of course, replace YOUR_SERIAL_PORT with your serial port's device name, and YOUR_FILENAME.hex with the appropriate filename. For me, this line looks like this:

`avrdude -p atmega32u4 -P /dev/ttyACM0  -c avr109  -U flash:w:Soarer_at2usb_v1.12_atmega32u4.hex`

If it says ''device not in sync'' or similar, your device is no longer in bootloader mode. Unplug it, and get it back into bootloader mode like you did in the previous step (or short the reset pin), and try again.
If this still doesn't work, try running the command again as root

`sudo avrdude -p atmega32u4 -P /dev/ttyACM0  -c avr109  -U flash:w:Soarer_at2usb_v1.12_atmega32u4.hex`

## Windows
1. Install the latest version of AVRdude for Windows from http://savannah.nongnu.org/projects/avrdude/  
Test that it installed correctly by running "avrdude" from Command Prompt. It should display a usage message with version information at the end  
2. Open Device Manager and take a look at your "Ports (COM & LPT)" section  
3. Plug in the Gherkin and short the RESET pin on the microcontroller to Ground to put it into bootloader mode. Take note of the new COM device that shows up. After 8 seconds or so the microcontroller will leave bootloader mode and it will disappear from that section  
4. Open Command Prompt and run the following (substituting "com7" with whatever port you saw earlier)  

`avrdude -p atmega32u4 -P com7  -c avr109  -U flash:w:YOURHEX.hex`
