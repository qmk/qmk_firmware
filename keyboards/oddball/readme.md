# Oddball

A split keyboard with trackball support.

* Keyboard Maintainer: [Alexander Tulloh](https://github.com/atulloh)
* Hardware Supported: Oddball PCB and plates, and using an [ADNS9800](https://www.tindie.com/products/jkicklighter/adns-9800-laser-motion-sensor/) or a [PMW3360](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/) breakout board for mouse
* Hardware Availability: [atulloh.github.io/oddball](https://atulloh.github.io/oddball)

Make examples for this keyboard (after setting up your build environment):

```
# with ADNS sensor
make oddball/v2:default
```
```
# with PMW sensor
make oddball/v2:pmw3360
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
