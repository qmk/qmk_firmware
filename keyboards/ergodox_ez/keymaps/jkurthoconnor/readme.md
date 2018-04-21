# Kurth's Ergodox

## Layout Description

A standard QWERTY layout optimized to remove work for the little fingers by transferring it to the thumbs and index fingers. Those with vim motion muscle memory should find the navigation layer familiar. Throughout the design, a premium has been placed on replicating familiar patterns. The less one must think about typing the better.

The base layer (layer 0) is designed to be a familiar layout with little need to retrain muscle memory for the modifiers. As much work as possible has been transferred to the thumbs, with `CR`, `TAB`, `SPACE` and `BK SPACE` grouped in the thumb clusters, and symmetrically placed `SHIFT`, `CTRL` and `ALT`/`ALTGR` duplicated along the left and right hand bottom row to minimize the need for single-hand chording. `(` and `)` are also offloaded to the thumbs with Space Cadet `SHIFT`s. The index fingers capture much of the work typically left to a programmer's little fingers, with the characters `~`, `` ` ``, `[`, `]`, `{`, `}`, `/`, `?`, `\`, `|` all mapped to the index fingers.

The navigation layer (layer 2, right hand) is designed to exploit the familiar vim bindings to `h`, `j`, `k`, `l`. Arrow keys, mouse movements, scrolling and paging are all mapped to the corresponding fingers, with only a row shift necessary to pass from the same direction mousing, line motions, scrolling and paging.


## Building and Flashing Firmware for the ErgoDox EZ

The Ez uses the [Teensy Loader](https://www.pjrc.com/teensy/loader.html).

Linux users need to modify udev rules as described on the [Teensy
Linux page].  Some distributions provide a binary, maybe called
`teensy-loader-cli`.

[Teensy Linux page]: https://www.pjrc.com/teensy/loader_linux.html


### Building Firmware

Build the firmware with `make <keyboardname>:<keymapname>`, in this case, `make ergodox_ez:jkurthoconnor`

This results in a hex file called `ergodox_ez_keymapname.hex`, e.g.`ergodox_ez_jkurthoconnor.hex`


### Flashing the Firmware in the gui Teensy Loader

#### Using 'Manual Mode'

Start the teensy loader.

  - if desired, turn on Verbose mode (via Help Menu)

Load the `.hex` file via 'File Menu / Open Hex File' (or via the page icon).

Press the Reset button by inserting a paperclip gently into the reset hole in the top right corner (or use Reset key)

Download the firmware to the board via 'Operation / Program' (or via the green down arrow)

Reboot the board (via 'Operation / Reboot') if the board did not do so automatically


#### Using ['Auto Mode'](https://www.youtube.com/watch?v=9PyiGUO9_KQ)

Open teensy loader

Load desired hex file

Click auto button or choose auto from operation menu

Press reset button on keyboard


See also the [QMK documentation](https://docs.qmk.fm/newbs.html)
