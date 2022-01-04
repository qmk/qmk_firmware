# XD68

![Kitteh](https://i.imgur.com/qkA5Of5.jpg)

65% board with USB-C, RGB underglow and backlight.  Powered by ATM32U4.

![Top View of XD68 Keyboard](https://i.imgur.com/OLkQQ17.jpg)

* Keyboard Maintainer: QMK Community
* Hardware Supported: XD68
* Hardware Availability: [KPRepublic on AliExpress](http://kprepublic.com/products/xiudi-xd68-pcb-65-custom-mechanical-keyboard-support-tkg-tools-underglow-rgb-pcb-programmed-kle-lots-of-layouts)

Make example for this keyboard (after setting up your build environment):

    make xiudi/xd68:default       
    make xiudi/xd68:default_iso   # default ISO UK layout

## Layouts 

### ANSI

```
,----------------------------------------------------------------.
|Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Home|
|----------------------------------------------------------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |PgUp|
|----------------------------------------------------------------|
|CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgDn|
|----------------------------------------------------------------|
|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|End |
|----------------------------------------------------------------|
|Ctrl|Win |Alt |        Space          |App|Ctrl|FN |Lef|Dow|Rig |
`----------------------------------------------------------------'
```

### ISO-UK

```
,----------------------------------------------------------------.
|Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Home|
|----------------------------------------------------------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |PgUp|
|-------------------------------------------------------    -----|
|CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;| '|  #|Entr|PgDn|
|----------------------------------------------------------------|
|Shift|  \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .| /|Rshift|Up|End |
|----------------------------------------------------------------|
|Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
`----------------------------------------------------------------'
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

