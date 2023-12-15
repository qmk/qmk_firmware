# tkk

![tkk](https://i.imgur.com/gXAjt3Oh.jpeg)

This is 'tkk', a ten key split keyboard wired as a single "row," ten "column" diode-less numpad. I've been dreaming of my own ten key layout since before discovering [ASETIOP](https://asetniop.com/), and [gboard's Ginny](https://www.gboards.ca/) ... but I'm too new to QMK and too rusty with C to figure out how to modify the Ginny's layout / chording engine. So here we are. The tkk [layout](https://imgur.com/a/eQzhSgw) is built around a vaguely DVORAK-ish letter layout (with some adjustments meant to aid memorization), with "modules" for numbers, movement, modifiers, and even mouse keys.

* Keyboard Maintainer: [Joe Fass](https://github.com/jfass)
* Hardware Supported: hand-wired, ten switch diode-less keyboard, using a Teensy 2.0
* Hardware Availability: (forget where I bought the parts, but easy to find)

Make example for this keyboard (after setting up your build environment):

    make handwired/tkk:default

Or:

    qmk compile -kb handwired/tkk -km default

In my build environment (Ubuntu), I needed to unset quite a few environment variables like CONDA\_BACKUP\_LDFLAGS that contained hardware options qmk didn't like, before this succeeded.

Flashing example for this keyboard:

    make handwired/tkk:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

