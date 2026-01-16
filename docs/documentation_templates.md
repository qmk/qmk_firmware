# Documentation Templates

This page documents the templates you should use when submitting new Keymaps and Keyboards to QMK.

## Keymap `readme.md` Template {#keyboard-readmemd-template}

Most keymaps have an image depicting the layout. You can use [Keyboard Layout Editor](http://keyboard-layout-editor.com) to create an image. Upload it to [Imgur](https://imgur.com) or another hosting service, please do not include images in your Pull Request.

Below the image you should write a short description to help people understand your keymap.

```
![Clueboard Layout Image](https://i.imgur.com/7Capi8W.png)

# Default Clueboard Layout

This is the default layout that comes flashed on every Clueboard. For the most
part it's a straightforward and easy to follow layout. The only unusual key is
the key in the upper left, which sends Escape normally, but Grave when any of
the Ctrl, Alt, or GUI modifiers are held down.
```

## Keyboard `readme.md` Template

```
# Planck

![Planck](https://i.imgur.com/q2M3uEU.jpg)

A compact 40% (12x4) ortholinear keyboard kit made and sold by OLKB and Massdrop. [More info on qmk.fm](https://qmk.fm/planck/)

* Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert)
* Hardware Supported: Planck PCB rev1, rev2, rev3, rev4, Teensy 2.0
* Hardware Availability: [OLKB.com](https://olkb.com), [Massdrop](https://www.massdrop.com/buy/planck-mechanical-keyboard?mode=guest_open)

Make example for this keyboard (after setting up your build environment):

    make planck/rev4:default

Flashing example for this keyboard:

    make planck/rev4:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
```
