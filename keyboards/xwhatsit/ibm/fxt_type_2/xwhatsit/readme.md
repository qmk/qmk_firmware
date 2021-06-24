# xwhatsit/ibm/fxt_type_2/xwhatsit

![xwhatsit/ibm/fxt_type_2/xwhatsit](https://deskthority.net/wiki/images/8/84/IBM_XT_top.JPG)

A short description of the keyboard/project

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Supports IBM Model F XT Type 2 keyboards, using the original Xwhatsit model F rev. 1 or rev. 2 controller PCB.
    Most Model F XT keyboards are type 2, See the Types section of this wiki: https://deskthority.net/wiki/IBM_Personal_Computer_keyboard#Types
    This firmware is designed for a keyboard that has been converted like in the following post: https://deskthority.net/viewtopic.php?t=19522
    Namely wires are connected so that no two row/column wires cross, and the column wires in use are those 12 that are closest to the row-side of the controller.
* Hardware Availability: Rare collector's item

Make example for this keyboard (after setting up your build environment):

    make xwhatsit/ibm/fxt_type_2/xwhatsit:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
