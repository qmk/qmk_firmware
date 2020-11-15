# Cumpad
<img src="http://keebs.lfgberg.org/Images/IMG_0211.jpg" alt="Cumpad" />
<img src="http://keebs.lfgberg.org/Images/PB130119.JPG" alt="Cumpad PCB" />

### Pinout
| rows        | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
| ----------- | --- | --- | --- | --- | --- | --- | --- | --- |
| qmk pin     | F4  | F5  | F6  | B5  | B4  | E6  | C6  | D7  |

| columns     | 0   | 1   | 2   |
| ----------- | --- | --- | --- |
| qmk pin     | F7  | B3  | B1  |


Make example for this keyboard (after setting up your build environment):

    compile -kb lfgberg/cumpad -km default

Make via compatible firmware (after setting up your build environment):

    compile -kb lfgberg/cumpad -km via

Bootmagic is enabled.  Press the key at (0,0) while plugging the keyboard in to jump to bootloader.

* Keyboard Maintainer: [Lfgberg](https://github.com/lfgberg)
* Hardware Availability: GB when applicable

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
