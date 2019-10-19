# 4 Pack

![4pack](https://i.imgur.com/rioXXq5l.jpg)

A 4 Key macropad PCB

You can find the main blog post about this macropad [here](http://www.40percent.club/2017/07/4-pack.html), also the Gerber files and other documentation is located [here](https://git.40percent.club/di0ib/Misc/src/branch/master/4pack).

I've realized this keyboard was missing a QMK firmware, so I've decided to make one to benefit from QMK.

There were two struggles while I was building this keyboard firmware:

1. The pinout didn't have a matrix, pins were directly connected to the io pins. I've realized for the row value, I needed to use `B0` (ground pin) in this case.
2. Leds' both anode and cathode pins were connected to io pins, so some GPIO commands needed to set them and light them.

While building, I've used header pins directly instead of sockets as mentioned, also, I've used 1k ohm resistors, along with Gateron greens (my favorite cheap macropad switches). These worked out nicely.

Firmware Build: [Arda Kilicdagi](http://github.com/ardakilic)
Hardware Availability: links to where you can find this hardware

Make example for this macropad (after setting up your build environment):

    make 40percentclub/4pack:default:avrdude

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
