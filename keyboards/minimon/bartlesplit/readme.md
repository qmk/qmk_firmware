# Bartlesplitt

![Bartlesplit with the hub in the 3x6 setup](https://i.imgur.com/IoMpwylh.png)

Bartlesplit is based on [Cheapino](https://github.com/tompi/cheapino) by Tompi.
The original idea was to build a Cheapino with hot swaps, but it evolved into something more!

At the same time I was working on Bartlesplit, a friend of mine suggested that we try to make a splithub, letting us avoid having the Pro Micro directly on the board.
This is mostly a design choice, making each split less clutered.
We have called the hub [The Japanese Connection](https://github.com/Kyrremann/the-japanese-connection) since it's relying on the Japanese duplex matrix.

One of the main feature of the board is the built-in tenting, so you don't need to make a case to get simple tenting.


* Keyboard Maintainer: [Kyrre Havik](https://github.com/Kyrremann)
* Hardware Supported: Rev 1, Pro Micro
* Hardware Availability: https://github.com/Kyrremann/bartlesplit

Make example for this keyboard (after setting up your build environment):

    make minimon/bartlesplit:default

Flashing example for this keyboard:

    make minimon/bartlesplit:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in shorting the reset pin on Pro Micro on the hub.
