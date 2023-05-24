## Unicomp Mini M with Teensy2.0++ controller & QMK Firmware

### Overview

#### Goals

The goal of this project was to replace the stock control board of the Unicomp Mini M with a programmable one.  The Mini
M was released by [Unicomp](https://www.pckeyboard.com) in Q1 of 2021 and is a re-release of The IBM Model M Space
Saving Keyboard (SSK) with some enhancements.

This guide strives to achieve the following:

* Make completely reversable changes, or in other words, no permanent modifications to the Mini M
* Allow full programmability of the Mini M via QMK
* Be able to flash firmware without having to take the board apart to hit the reset button
* Create a default keymap that works just like the stock keymap shipped from Unicomp, including the toggle-able number
  pad
* Support all LEDs as normal

My guide will go a few steps further:

* Convert the wired connection from USB-A to USB-C
* Install a potentiometer to dim the LEDs if desired

#### Credits

The following resources were instrumental to the success of this project:

* Model M 101/102 write-up located in `qmk_firmware/keyboards/converter/modelm`
* [Model M Subreddit](https://modelm.reddit.com)
* Model M Discord

### Hardware

##### Parts

For a working Mini M with QMK *without* LEDs working, the following parts are necessary:

* 1 Adafruit Perma-Proto Full Sized Breadboard.  Luckily, this board is a perfect fit for the Mini M case!
* 1 Teensy2.0++, with headers soldered on if you can find it
    * 2 20-row x 1 column headers, if you can't find a Teensy with headers already soldered on
* 2 16-pin Ribbon connectors, PCB mount
* Hookup wire.  I used 30AWG wire and while it worked, I should have used 1 gauge (or more) thicker
* A panel mount male USB-B to female USB-C extender

To get the Mini M working with LEDs, you will need:

* 3 1kOhm through-hole resistors

##### Tools

The following were absolutely critical for the project:

* Soldering iron, preferably one with a narrow tip for small connections
* Drill, preferably a hand-held rotary tool (such as a Dremel)
* Wire strippers/cutters
* A sharp knife

Optional, but worth having around:

* Helping-hands, PCB holder, preferably both
* Multi-meter for testing continuity of your connections
* Hot-glue gun for mounting the USB extender to the Perma-Proto

### Assembly

#### Solder Teensy to the Perma-Proto

1. Solder headers to Teensy
2. Solder headers to Perma-Proto

#### Solder ribbon connectors

* Rows on the Perma-Proto that line up with membrane ribbons
* Trim excess under board
* Test continuity

#### Solder in hookup wires

* Ribbon connector used for the right ribbon will need hookup wire to establish connections to the Teensy
* 12 required, 16 if you want full functionality

#### Optional: Solder in resistors

#### Caveat: D6 pin on the Teensy

There are a few ways to mount the Teensy to the Perma-Proto board.  I chose to connect my 16 pin ribbon connector to the
Teensy pins starting at C7 and ending at D2.  If you do this, beware that pin D6 will not work for the purposes of this
project.  It is possible to modify it to make it so, but that is beyond the scope of this guide.

Bypassing D6 is necessary if you mount your ribbon connector as I have just described.  Luckily, it is a simple process!
First, with a sharp knife, sever the connection between your ribbon connector pin that is connected to Teensy D6 pin.  I
would recommend doing this at the closest possible point to the Teensy on the underside of the Perma-Proto board.  Once
that is done, use a remaining point on the Perma-Proto bus for that ribbon connection (that was previously connected to
D6) to add a jumper wire connected to pin B7.  If you are using the firmware files provided in this repository,
everything is already set for this configuration.

### Testing

### Software

#### Build firmware

See qmk documentation on getting your build environment working.

Compile the Mini M firmware files with the default keymap.  It allows for the Mini M to be used with the same
functionality as shipped from the manufacturer.

```bash
$ qmk compile -kb unicomp/mini_m -km default
```

While plugged in, press the reset button on your Teensy and then:

```bash
$ qmk flash -kb unicomp/mini_m -km default
```

If everything works to this point, congratulations!  You now have a programmable Mini M.  If you are using the default
keymap, you can reset your Teensy by pressing Shift+Pause together, eliminating the need to take apart the case in order
to do so.

#### Keymaps

To build your own keymap, create a new directory in `keyboards/unicomp/mini_m/keymaps/<your name>`, copy the files from
`keyboards/unicomp/mini_m/default` into your new directory, and edit them as you wish.  When you are ready to flash your
new keymap to the Mini M, the command will be `qmk flash -kb unicomp/mini_m -kb <your name>`.
