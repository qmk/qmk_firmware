# Gray COD67

![cod67](imgur.com image replace me!)

The Gray COD67 is a 60% keyboard with a modern and bold design. It features 20 RGB Underglow LED lights and a unique diffuser placement. The COD67 has the most stunning RGB light strip for a custom mechanical keyboard. It also features a center mounted USB C port. 

There were only 75 units made worldwide. 

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Gray COD67 
Hardware Availability: [Zfrontier](https://en.zfrontier.com/products/cod67)  

At this time, flashing ONLY works on Windows systems. 

To put in bootloader mode, hold the `Esc` key while plugging in the USB cable. 

The COD67 will show up as a drive. 

Make example for this keyboard (after setting up your build environment):

    make cod67:default:bin

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Rename the resulting `.bin` file to `cod67.bin`.

Drag and drop `cod67.bin` to the drive, overwriting the previous `cod67.bin` stored on it. 

Press the `Esc` key again to reset the board. You are now ready to type!

## Notes
The backlight pin is attached to a non PWM pin `D4` so backlight is only on/off. 
