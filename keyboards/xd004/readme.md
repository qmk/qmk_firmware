XD004
==

4-keys board

![Top View of a XD004 board](https://ae01.alicdn.com/kf/HTB1_G9IX21H3KVjSZFHq6zKppXa0/xd004-xiudi-4-Custom-Mechanical-Keyboard-4-keys-switch-leds-PCB-programmed-hot-swappable-macro-key.jpg)

Keyboard Maintainer: QMK Community  
Hardware Supported: XD004 PCB v1.0  
Hardware Availability: [KPRepublic](https://kprepublic.com/products/xd004-xiudi-4-custom-mechanical-keyboard-4-keys-switch-leds-pcb-programmed-hot-swappable-macro-key-silver-case-micro-port)

To put this board in DFU (firmware update) mode, bridge the last two pins (#5 & 6) of the 6-pin "J2" header on the opposite edge of the board to the USB port"
```
----+
 J2 |
[o] |
(o) |
(o) |
(o) |
(o)-+-\ (These
(o)-+-/  two)
    |
----+
```

To build with a default keymap (not useful at all, have a look at other keymaps):

```make xd004/v1:default```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
