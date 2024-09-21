# k8split
![left](https://raw.githubusercontent.com/Ckath/k8split/master/k8split_left.png)
![right](https://raw.githubusercontent.com/Ckath/k8split/master/k8split_right.png)

my personal 8x6(x2) split keyboard, aiming to be a mostly normal keyboard layout with plenty of keys. see the hardware repo for more info.

* Keyboard Maintainer: [Ckath](https://github.com/Ckath)
* Hardware: https://github.com/Ckath/k8split

Make example for this keyboard (after setting up your build environment):

    make handwired/k8split:default

Flashing (both halves are separate keyboards and the default layout is just for debugging):

    # left
    make handwired/k8split:left:flash
    # right
    make handwired/k8split:right:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
