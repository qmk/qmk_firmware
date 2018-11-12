# diverge3

A split 5x7 keyboard with 3 thumb keys. Made by [Unikeyboard](https://unikeyboard.io).

Keyboard Maintainer: [IslandMan93](https://github.com/islandman93)  
Hardware Supported: Pro Micro  
Hardware Availability: [Diverge 3](https://unikeyboard.io/product/diverge/)

Make example for this keyboard (after setting up your build environment):

    make diverge3:default

Or for the [Workman](https://github.com/ojbucao/workman) layout:

    make diverge3:workman

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

# Reflashing Animus
Reflashing the stock firmware is pretty easy. Just follow the same steps in the [original guide](https://imgur.com/a/8UapN). You will have to manually reset the Pro Micro (by shorting the GND and RST pins) during the upload step. Then reapply your keymap through Arbites.