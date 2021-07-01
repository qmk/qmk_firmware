# xwhatsit/ibm/fxt_type_2/universal

![xwhatsit/ibm/fxt_type_2/universal](https://deskthority.net/wiki/images/8/84/IBM_XT_top.JPG)

A short description of the keyboard/project

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Supports IBM Model F XT Type 2 keyboards, using one of the xwhatsit controller PCBs supported by the 'universal' driver: the through_hole controller, or one of the SMD Model F controllers.
  Most Model F XT keyboards are type 2, See the Types section of this wiki: https://deskthority.net/wiki/IBM_Personal_Computer_keyboard#Types
  The controllers supported by this firmware are described in these threads:
  https://deskthority.net/viewtopic.php?f=7&t=23406
  https://deskthority.net/viewtopic.php?f=7&t=24597
  This firmware is designed for a keyboard that has been converted in a similar way to the following post: https://deskthority.net/viewtopic.php?t=19522
  The post shows an original xwhatsit controller, however please keep the same general intent with the universal controllers.
  namely wires are connected so that no two row/column wires cross, and the column wires in use are those 12 that are closest to the row-side of the controller.
  This applies if using one of the SMD Model F controller types, or if using the TH controller with a daughtercard.
  If wiring in the TH controller directly, make sure that you skip the 7 columns coming off of the third (optional) shift register, like the daughterboard would do.
* Hardware Availability: Rare collector's item

Make example for this keyboard (after setting up your build environment):

    make xwhatsit/ibm/fxt_type_2/universal:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
