# ZooKeeper/ZooP Leon

QMK-supported firmware of Zookeeper's Leon, the solderable PCB for it.

Keyboard Maintainer: ZooP HuangJuanLr(https://github.com/HuangJuanLR)

Make example for this keyboard (after setting up your build environment):

    make zoop/leon/leonh:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

**Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
**Physical reset button**: Briefly press the button on the front left of the PCB
**Keycode in layout**: Press the key mapped to `Reset` if it is available. By default the combination is "MO(1) + Escape"
