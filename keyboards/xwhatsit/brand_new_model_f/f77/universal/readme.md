# xwhatsit/brand_new_model_f/f77/universal

![xwhatsit/brand_new_model_f/f77/universal](https://www.modelfkeyboards.com/wp-content/uploads/2019/11/F62-F77-new.jpg)

A short description of the keyboard/project

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Supports the brand new Model F reproductions from https://www.modelfkeyboards.com/, using one of the (non-default) xwhatsit controller PCBs supported by the 'universal' driver: the through_hole controller, or one of the SMD Model F controllers.
  WARNING: All the keyboards that ship from modelfkeyboards.com come with a "wcass" controller PCB,
  and the controller supported by this QMK subfolder is not compatible with that.
  This subfolder is only useful if you decide to modify your keyboard, and replace the controller PCB
  with a non-default one. Otherwise please choose the "wcass" subfolder.
  The controllers supported by this firmware are described in these threads:
  https://deskthority.net/viewtopic.php?f=7&t=23406
  https://deskthority.net/viewtopic.php?f=7&t=24597
* Hardware Availability: https://www.modelfkeyboards.com/

Make example for this keyboard (after setting up your build environment):

    make xwhatsit/brand_new_model_f/f77/universal:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
