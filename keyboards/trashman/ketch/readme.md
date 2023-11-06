# Ketch

![Ketch](https://i.imgur.com/eCIrvJBl.png)

A pcb designed to be compatible with older minivan cases as well as support most minivan layouts (+ a few new ones).
The ketch supports the following physical layouts:
![Image of supported ketch layouts](https://trashman.wiki/layouts/ketch/ketch-all_extra_condensed.png)

Ketch was also explicitly designed to use port D for all column pins in order to support matrix scanning via a portscan rather than individually scanning each pin. This has been implemented here via a custom matrix, so enjoy your slightly more efficient matrix scanning. :P

The PCB has exposed pads for triggering a reset. If you are looking at the bottom of the PCB, the pads are on the left chunk of the board between the usb port and the controller, right next to the bottom of the right-most homerow key (typically enter).

More information can be found on the [trashman wiki](https://trashman.wiki/pcbs/ketch)

* Keyboard Maintainer: [Jetpacktuxedo](https://github.com/jetpacktuxedo)
* Hardware Supported: Ketch PCB, Sketch PCB
* Hardware Availability: [Trash Man Keyboards](https://trashman.club/)

Make example for this keyboard (after setting up your build environment):

    make trashman/ketch:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
