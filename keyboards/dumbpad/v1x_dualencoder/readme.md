# dumbpad v1.x dual-encoder

![dumbpad](https://i.imgur.com/s69rdfA.png)

## Single- vs Dual-Encoder Support

The combined Cherry MX/encoder sockets allow single- and dual-encoder configurations.

The only rule when using two encoders is that there cannot be two encoders on the left side at once, or two on the right side.
This table shows where the encoders are in the switch grid ("X" for encoder, "s" for switch):

| C0  | C1  | C2  | C3  | C4  |
|:---:|:---:|:---:|:---:|:---:|
|     |__X__|  s  |  s  |__X__|
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|__X__|__X__|  s  |  s  |__X__|

- The three encoders in columns C0 and C1 are connected to each other
- The two encoders in column C4 are connected to each other

So, if doing dual encoders, one must be in column C4 and the other in either C0 or C1. Three or more encoders will not work.

The following sections describe the configurations that the default keymaps in QMK are designed for.

### Single-Encoder (Default Configuration)

In the default configuration, the encoder is in column 0, the bottom left corner below the Pro Micro. All other sockets are filled with switches.

| C0  | C1  | C2  | C3  | C4  |
|:---:|:---:|:---:|:---:|:---:|
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|__X__|  s  |  s  |  s  |  s  |

![single encoder](https://i.imgur.com/8ZPz1gFl.jpg)

### Dual-Encoder Bottom

One dual-encoder configuration has encoders in the bottom two corners of the 4x4 grid, and switches in the rest of the grid. The socket in column 0 is left empty.

| C0  | C1  | C2  | C3  | C4  |
|:---:|:---:|:---:|:---:|:---:|
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|     |__X__|  s  |  s  |__X__|

![dual-encoder bottom](https://i.imgur.com/QCqKDMSl.jpg)

### Dual-Encoder Top

Another dual-encoder configuration has encoders in the top two corners of the 4x4 grid, and switches in the rest of the grid. The socket in column 0 is left empty.

| C0  | C1  | C2  | C3  | C4  |
|:---:|:---:|:---:|:---:|:---:|
|     |__X__|  s  |  s  |__X__|
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |
|     |  s  |  s  |  s  |  s  |

![dual-encoder top](https://i.imgur.com/Rq6ox2Ol.jpg)

### No-Encoder

You may also choose not to use any rotary encoders if you like!

### Bill Of Materials

- Cherry-style mechanical switches
- EC11 rotary encoder with pushbutton (7-pin) - one or two depending on your desired configuration
- 1n4148 diodes (thru hole) - one per switch and rotary encoder (if using clickable encoder(s))
- 1x Arduino Pro Micro or pin-compatible ATmega32u4-based MCU
- (optional) 3x 3mm LEDs
- (optional) 3x 330 ohm resistors (for limiting current in LEDs)
- (optional) 6mm SPST switch for resetting MCU

* Keyboard Maintainer: [imchipwood](https://github.com/imchipwood)
* Hardware repository: [dumbpad on github](https://github.com/imchipwood/dumbpad)
* PCB Revisions Supported: v1.0_dual

Make example for this keyboard (after setting up your build environment):

    make dumbpad/v1x_dualencoder:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
