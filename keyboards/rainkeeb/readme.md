# rainkeeb

![rainkeeb](https://i.imgur.com/GpVBRMw.jpg)

My first custom mech design. 4x10(ish), pro micro based, unibody, split, ortho (any more adjectives?), with OLED and (optional) rotary encoder.

![Default layout](https://i.imgur.com/rCOwsoy.png)
This is the default layout, at least the base layer. By default the OLED displays "rainkeeb" at the top in case you forget what you're typing on, a layer indicator below that (Default, Raised, Alt), and a WPM counter below that. Encoder toggles Play/Pause on click on the Default and Raised layers, and is supposed to RESET into flash-mode on the Alt layer but that's not working for some reason. Clockwise turn increases volume, scrolls down, and scrolls right on the Default, Raise, and Alt layers respectively. Counterclockwise does the opposite of the clockwise turns, you get the picture.

* Keyboard Maintainer: [rain](https://github.com/rainsff)

Make example for this keyboard (after setting up your build environment):

    make rainkeeb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).