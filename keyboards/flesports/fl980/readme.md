# FL-Esports FL980

FL980

Keyboard Maintainer: [Alexey Zagorodnikov](https://github.com/iglooom/)
Based on Redragon K556 by: [Adam Honse](https://github.com/CalcProgrammer1)
Hardware Supported: SN32F248BF

For some reason, I can't use the default RGB matrix driver for this keyboard. Tried different options without luck, LEDs always had some glow and incorrect colors, even when should be completely off.
I used the custom driver with PWM on rows instead columns, but for smooth RGB, reading keys performed only twice inside RGB cycle. Good enough for me.

Make example for this keyboard (after setting up your build environment):

    make flesports/fl980:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
