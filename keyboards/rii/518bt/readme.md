Rii 518BT (Custom USB PCB)
===

This firmware is used with [a custom PCB](https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb) to replace the original, which is Bluetooth-only, in the Rii 518BT. The drop-in replacement provides a USB2.0 interface, better backlighting, and of course supports QMK.

![Rii 518BT](https://raw.githubusercontent.com/tim-eastwood/rii-518bt-usb-qmk-pcb/main/pics/1.png)

The Rii 518bt is an ultra-compact 68-key keyboard.

**Keyboard Maintainer:** [Tim / Tangles](https://github.com/tim-eastwood/QMK-rii-518bt-usb)  
**Hardware Supported:** Rii 518BT with [custom USB/STM32F072 PCB](https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb)
**Hardware Availability:** Build it yourself using any PCBA service using the source files / BoM located at [https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb](https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb)

Purchasing a Rii 518BT is required to obtain the housing, key membrane, and adhesive sheet of dome switches.

---

## Compiling

In [QMK MSYS](https://docs.qmk.fm/newbs_getting_started#set-up-your-environment), run:

```sh
qmk compile -kb rii/518bt -km default
```

## Flashing

To compile and flash directly:

```sh
qmk flash -kb rii/518bt -km default
```

## Resources

- [QMK Build Environment Setup](https://docs.qmk.fm/#/getting_started_build_tools)
- [QMK Make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
- [Complete Newbs Guide](https://docs.qmk.fm/#/newbs)

---

Disclaimer: This is an independent hardware project and is not affiliated with Rii or the original manufacturer.
