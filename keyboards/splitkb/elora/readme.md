![Elora](https://i.imgur.com/AUCjyBuh.jpg)

# Elora
The Elora is a 62-key keyboard, based on the Kyria by splitkb.com. It comes preassembled, is compatible with Vial so you don't need to program or compile your firmware, and accepts Myriad modules so you can add cool features with just a screwdriver.

Keyboard Maintainer: [splitkb.com](https://github.com/splitkb)  
Hardware Availability: [splitkb.com](https://splitkb.com).

Make example for this keyboard (after setting up your build environment):

    make splitkb/elora/rev1:default

The keyboard can be flashed by copying the resulting `splitkb_elora_rev1_default.uf2` file onto the `RPI-RP2` flash drive.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
You can enter the bootloader in 3 ways:

* **Reset button**: Double-tap the reset button on the side of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
* **Bootloader reset**: As a last resort, hold down the small "Boot" button near the USB connector while plugging in the keyboard.

# Features
The Elora is an evolved version of the Kyria that comes with a number row, and has an emphasis on ease of use for beginners, as well as being hackable for advanced customers. It comes preassembled: the only tool you need is a screwdriver.

- A comfortable 62 keys, including a number row. It's perfect for beginners who want to feel what a split keyboard feels like without the layout feeling cramped, and a nice option for people who know they frequently use the number row, like typists, gamers, some software engineers and Excel warriors.
- Powered by an RP2040 controller, it’s quick enough to handle anything a keyboard should be able to do… and much more.
- 16 megabytes of flash memory ensure that it’s ready for just about everything. Putting a sped-up movie on an RGB display you’ve wired up to your prototyping Myriad module? Say no more.
- Supports MX switches with preassembled hot-swap sockets. No soldering iron needed. You can solder them to the alternative set of pads if you'd prefer to, though.
- Supports Choc switches by soldering. This does require assembly with tools like a soldering iron. Hot swap is still possible using Mill-Max sockets, which too require soldering.
- Subtle RGB underglow with 6 LEDs per half to personalise the colour of your keyboard. It can be disabled for those who don't want it.
- Supports the tenting puck, which allows you to mount it to most camera tripods so you can place your keyboard at exactly the angle you want it.
- Supports up to one Myriad module per half, so you can add a myriad of available modules without having to solder.
- Supports up to one 128x64 pixel OLED display per half, which doesn't require soldering.
- There's a TRRS jack for foot pedal or external switch support. You can use one such switch per half by default, but the wiring supports up to three external switches per half. Great for accessibility purposes, or just plain fun if you want to hook up a digital foot pedal to your voice chat software, game or whatever else you can think of.
- If you're into soldering, you can put up to three encoders per half on seven predefined locations: near the top of the thumb cluster, at the innermost thumb cluster button, or each location on the outer columns. If you don't want to solder, you can of course still use a rotary encoder Myriad module.

# What's Myriad?

![A collection of Myriad modules](https://i.imgur.com/86u7BLMl.jpg)

Myriad is a system that allows you to plug in modules to add new functionality to your keyboard, all without having to solder. It's an [open standard](https://myriad.splitkb.com/), meaning that anyone will be able to create their own modules, which you can then plug into your keyboard. It's a very capable standard, so we're very curious to see what other modules you will come up with!
