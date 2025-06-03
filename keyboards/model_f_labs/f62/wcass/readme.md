# model_f_labs/f62/wcass

![model_f_labs/f62/wcass](https://images2.imgbox.com/e5/97/1hPUzXct_o.jpg)

## Basic Details

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Supports the brand new Model F reproductions from https://www.modelfkeyboards.com/, using the smaller xwhatsit controller developed by wcass.
* Hardware Availability: https://www.modelfkeyboards.com/

Make example for this keyboard (after setting up your build environment):

    make model_f_labs/f62/wcass:default

See the [build environment setup](https://docs.qmk.fm/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/getting_started_make_guide) for more information. 


## How do you enter the boot loader?

There are three ways to enter the boot loader.
* **Command**: At the same time hold down both shift key and the B key.
               Left Shift + Right Shift + B
* **Keycode in Layout**: Press the key mapped to `QK_BOOT`.
                         The default location is the R key on the second layer.
                         FN + Spacebar + R
* **Physical Reset PCB Pad**: Short pads of the PCB.
                              The description and image below are from the
                              Model F Labs manual web page.

At the very worst you have to open up the keyboard to short PROG on the actual xwhatsit controller (unscrew the 2 controller screws to see the components side of the board, make a connection with a conductive metal object like an uncoated metal paper clip, then connect the USB cable to the controller and within a split second remove the paper clip). Per pandrew:  “You might think that a screwdriver is gonna be enough, but due to surface oxidation it is likely not gonna be good enough. I like to use sharp metal tweezers, because they can dig into the pad a little bit, breaking up the surface oxidation, and I can actually be sure it’s shorting. Apply constant strong pressure on the pads while plugging in the keyboard to make sure they’re perfectly shorted. If you hear the windows USB plug-in sound (assuming the sound effect is enabled), then you know you have succeeded. I’ve even seen people tell me they tried everything to short the pads with, and then I asked them to solder the pads together and it suddenly works. There’s something about the size of those pads, or about the fact that they need to be shorted in the perfect moment when the chip leaves reset, that make people think they are perfectly shorted and yet they aren’t. This affects me too, sometimes it takes me up to 3 tries to get it into bootloader mode. Another thing to double check that you are indeed shorting the PROG pad and not the reset pad. I believe in some versions of the wcass controller there is a reset pad on the opposite side of the board. So don’t be like ‘I see some pads, those must be it’, make sure to be shorting the correct ones.” [1]

![PCB PADS](https://images2.imgbox.com/ef/20/C9zUfX1h_o.jpg)

1. “Brand New Model F and Beam Spring keyboards manual,” Brand New Model F Keyboards, https://www.modelfkeyboards.com/manual/ (accessed Mar. 16, 2024).

