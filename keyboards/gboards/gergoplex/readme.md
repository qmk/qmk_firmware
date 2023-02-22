# GergoPlex

![GergoPlex](https://assets.bigcartel.com/product_images/248890490/IMG_20191114_1406385-01-01.jpeg)

A compact 30% (5x3+3) Split Keyboard from g Heavy Industries

* Keyboard Maintainer: [Jane Bernhardt](https://github.com/germ)
* Hardware Supported: GergoPlex (Kit, Partial, Ready)
* Hardware Availability: [gboards.ca](http://gboards.ca)

## Firmware building

Build using the following command (after setting up your build environment):

```
make gboards/gergoplex:default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Switch `default` with `colemak-dhm` if you prefer to use [Colemak Mod-DH layout](https://colemakmods.github.io/mod-dh/).

## Flashing

Press the small SMD button on the right side board, and run:

```
make gboards/gergoplex:default:flash
```

### Troubleshooting

See [this issue](https://github.com/qmk/qmk_toolbox/issues/58) for solutions if you're seeing:
```
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
```

## Have an idea for a gadget or a keymap?

[Reach out to me!](mailto:jane@gboards.ca) or submit a PR!
