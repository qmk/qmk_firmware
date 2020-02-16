# kc60se

* Keyboard Maintainer: [Blake C. Lewis](https://github.com/BlakeCLewis), [MechMerlin](https://www.github.com/mechmerlin)

Hardware Supported: KC60SE

Hardware Availability: PCB is nolonger available

## Description:
  * 60% keyboard PCB;
  * supports ANSI, ISO, and HHKB layouts.


### Enter the Bootloader
  * As delivered, BOOTMAGIC_ENABLE = yes:
    * unplug keyboard;
    * while holding down 'Space' 'B', plug in USB cable and continue to hold for 8 seconds;
    * 'lsusb' should report 'Atmel Corp. atmega32u4 DFU bootloader' instead of 'feed 6060';
    * in bootloader LEDs are off &amp; keyboard does not work.
  * New firmware, BOOTMAGIC_ENABLE = lite:
    * holding down esc while pluging in usb.
  * Hardware way: 
    * momentary jump pads 5 &amp; 6 to enter bootloader;

### Compile the default keymap:
    make kc60se:default

### See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

### NKRO
  * N or 6 Key Rollover NKRO/6KRO
  * navigating bios of computer may require 6KRO
  * default keymap has fn(T) mapped to toggle NKRO/6KRO
  * test: press 8 keys at same time, if 6, then 6KRO, if 8, then NKRO

### DIP switches enable/disable GUI keys, the second keys from the ends on the bottom row:
  * K41/K4C are WIN/GUI and will disrupt games;
  * this can be done by mapping a key to toggle these keys

 ```
  dip      keys
 #1  #2  K41 K4C
  1   1   1   1    both keys enabled
  1   0   0   1
  0   1   1   0
  0   0   0   0    both keys disabled
  ```
### ISP header next to the Atmega32u4:
  * if you can't get into bootloader, while keyboard is on, momentary jump pad 5 to pad 6

  ```
  2 4 6
  : : :
  1 3 5
  ```
  ```
  1 - B3      MISO, column 13, square pad
  2 - VCC
  3 - B1      SCLK, column 7
  4 - B2      MOSI, caplock led
  5 - Reset   | momentary jump 5 and 6
  6 - Ground  | to enter Bootloader
  ```
