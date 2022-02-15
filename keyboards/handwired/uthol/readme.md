Uthol
===

A handwired 50% (12x5) ortholinear keyboard made by Uthol

Keyboard Maintainer: Uthol

Hardware Supported: Rev1, Rev2, Rev3

Hardware Availability:Me

Use all your cpu cores to compile: 

    export MAKEFLAGS="-j$(nproc) --output-sync"

Make example for this keyboard (after setting up your build environment):

    make handwired/uthol/rev2:default

Install examples:

    make handwired/uthol/rev1:default:flash    # For Uthol Aluminum rev1
    make handwired/uthol/rev2:default:flash    # For Uthol rev2
    make handwired/uthol/rev3:default:flash    # For Uthol rev3

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

