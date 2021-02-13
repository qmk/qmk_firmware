# DZ60 ISO Keymap

Custom keymap for UK ISO keyboard layouts.
This includes 3 different layers.

-   Layer 0:
    -   Standard ISO layout with main modifier key, for accessing layer 1, to the right of the space bar.
-   Layer 1:
    -   Layer that gives you access to pretty much everything else like the arrow keys.
-   Layer 2;
    -   Standalone layer only for modifying the lighting on the board. Keys for this purpose are mapped in the locations used by the default dz60 layout.
    -   You can access this layer by holding MO(1) (next to the space bar) followed by holding MO(2) which where the Left Alt key is positioned.

![dz60-iso-keymap](https://i.imgur.com/UV0t6aL.png)

Make the kaymap for this keyboard (after setting up your build environment):

    make dz60:tarnjotsingh

Then flash it by running:

    make dz60:tarnjotsingh:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
