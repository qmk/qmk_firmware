# Charybdis (6x4, 5x3 Nano)

An ergonomic keyboard with integrated trackball.

Engineered to be a full mouse replacement solution with high-quality, custom-developed components.

There are 6x4 and 5x3 Nano versions.

* Keyboard Maintainer: [Bastard Keyboards](https://github.com/Bastardkb/)
* Hardware Supported: elite-C V4
* Hardware Availability: [Bastard Keyboards](https://bastardkb.com/)

See each keyboard folder for make examples.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

See the [keyboard build instructions](https://docs.bastardkb.com)

# Customizing your Charybdis

## Defining your own keymap

The default keymap is a modified miryoku-qwerty.

To define a new layout, you can either work from scrath, or use the wrappers. 
In this case, you only need to redefine the base layer, and can use the rest of the miryoku layers without redefining them.

See the `keymap.c` in the `keymaps/default` folder for an example.

## Homerow mod config

If using homerow mods, you can choose different homerow mods configurations (GASC, AGCS....) by adding a wraper around your base layer.

See the `keymap.c` in the `keymaps/default` folder for an example.

Available configurations are: SCGA, GASC, GACS, CAGS, SACG, GCAS.


## Custom DPI

By default the Charybdis comes with a broad range of DPI options, which you can change dynamically.

Add the `DPI_CONFIG` keycode in your keymap to switch up or down in the options (it is included in the default keymap).

You can also define a custom DPI range in your keymap's `config.h` file:

```c
#    define CHARYBDIS_DPI_OPTIONS \
        { 2000, 2200, 2400, 2600, 2800, 3000, 3200  }
```

## Dragscroll

When holding the `MOUSE` layer key, you can hold the dragscroll key to transform the trackball into a scrolling wheel.

Add the `DRAG_SCROLL` keycode in your keymap to trigger drag scroll on hold (it is included in the default keymap).


By default the drag scroll key will enable drag scroll on hold, and disable it on release.

If you prefer the key to toggle drag scroll on/off, you can do so like this in your keymap's `config.h` file:
```c
#define CHARYBDIS_DRAGSCROLL_TOGGLE
```

### Dragscroll speed

You can have either a set speed for the scrolling, or have it depend on your mouse speed.

By default the scrolling speed is fixed and set to 100 DPI, you can modifiy it in your keymap's `config.h` file:
```c
#define CHARYBDIS_DRAGSCROLL_DPI 200
```

If you want to set the scroll speed as dependent of your DPI:
```c
#define CHARYBDIS_DRAGSCROLL_VARIABLE
#define CHARYBDIS_DRAGSCROLL_MULTIPLIER 0.2 // Optional, DPI multiplier
```


## Sniping

When holding the `MOUSE` layer key, sniping mode is triggered. This slows down the cursor for better accuracy.

Add the `SNIPER_CONFIG` keycode in your keymap to switch up or down in the options (it is included in the default keymap).

You can also define a custom DPI range in your keymap's `config.h` file:

```c
#define CHARYBDIS_SNIPER_OPTIONS \
        { 200, 300, 400, 500 }
```

By default the auto sniping layer is 4 (`MOUSE` layer), you can redefine it as so:

```c
#define CHARYBDIS_AUTO_SNIPER_LAYER 5
```

You can also use the `SNIPING` keycode to your keymap, that will activate sniping mode on hold.
