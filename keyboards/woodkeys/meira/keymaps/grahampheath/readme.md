# Graham's Meira.

Don't expect this to work for you unaltered! For the record, these are my notes, not a guide for you :-)

## Known issues:
Anything over 28k will begin to overwrite the boot loader, which is a pain!

Be sure to check file size with:
```
avr-size meira_promicro_grahampheath.hex
```

## Sounds
I've added a [8ohm 0.5W speaker](http://a.co/6MIKZSy), its a bit large, but it fits in approximately the same space as the ProMicro. I soldered directly to  PC6 and GND.

As the Meira code stood, adding sound increased the hex beyond what the boot loader could handle, so I had to dial way back on features that I wasnt using, like backlighting and RGB support. I also removed function keys, though I think you could restore some of these features, you certainly can't restore all of them and still fit with a boot loader.

## Build

Built for the ProMicro with:
```
make meira/promicro:grahampheath
```

Build and upload with, which is cool because it will sense your port.
```
make meira/promicro:grahampheath:avrdude
```

Program a hex directly with:
```
avrdude -p atmega32u4 -P /dev/tty.usbmodem14111 -c avr109 -v -e -D -U flash:w:meira_promicro_grahampheath.hex
```

If you use an AVRISP you will be program a hex without a boot loader:
```
avrdude -p atmega32u4 -P /dev/tty.usbmodem14111 -c avrisp -v -e -U flash:w:meira_promicro_grahampheath.hex
```

## Bricked
Did you overwrite your boot loader?

I did...

I used an [Ardunio as an ISP](https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader), and was able to program various boot loaders. Ultimately it seemed like this was the right combo:

[ProMicro pinout](https://cdn.sparkfun.com/assets/9/c/3/c/4/523a1765757b7f5c6e8b4567.png)

[Wiring](https://forum.arduino.cc/index.php?PHPSESSID=467mm69btif69hdj5e3gil5465&action=dlattach;topic=363341.0;attach=145820): [via u/dmjlambert](https://forum.arduino.cc/index.php?topic=363341.0)

ProMicro boot loader hex is called `Caterina-promicro16.hex` and is stored on [Sparkfun's GitHub](https://github.com/sparkfun/Arduino_Boards)

```
avrdude -c avrisp -p m32u4 -P /dev/tty.usbmodem14141 -v -e -U flash:w:Caterina-promicro16.hex -U efuse:w:0xcb:m -U hfuse:w:0xd8:m -U lfuse:w:0xff:m
```
