# thewerther configuration
## RGB effects

Only enabled a few effects and modified the `RGB_MATRIX_REACTIVE_SIMPLE` effect to always light up the underglow leds to the chosen color.
The effect can be seen here:
![](https://media.giphy.com/media/l2gz7n045RtSM1ulxV/giphy-downsized-large.gif).

See [here](https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects) for more information on all the possible effects that can be enabled.

## Modified Layout

![ID67 layout](https://i.imgur.com/R0sGkIN.png)

- Added media buttons on second layer.
- Replaced `Tab` with `RAlt` so I can use us-international-nodeadkeys to be able to type special characters.

## Compiling and flashing

Make example for this keyboard (after setting up your build environment):

    make id67:thewerther

Flashing example for this keyboard:

    make id67:thewerther:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the `Escape` key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` (FN+Z).
