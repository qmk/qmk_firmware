# Nifty Numpad

![Nifty Numpad](https://i.imgur.com/jfB8tfKh.png)

Nifty Numpad is a full sized numpad with an extra row and two extra columns of macro keys. It was created because I wanted a companion to my TKL keyboard for work. My main workflow involves heavy use of ECAD programs, so the design was tailored for that, but it is generic enough to be nice for many workflows! 


The main features are:
- Full sized numpad with row of macro/function keys on the top
- Two extra columns of macro keys
- Cherry MX style socketed switches
- Key Backlights
- 3D printable case (FDM or resin)

### Development Information:
* Keyboard Maintainer: [Isaac Rex](https://github.com/Acliad/)
* Hardware Supported: RP2040
* Hardware Availability: See [The GitLab Page](https://gitlab.com/Acliad/nifty-numpad) for full details

Make example for this keyboard (after setting up your build environment):

    make nifty_numpad:default

Flashing example for this keyboard:

    make nifty_numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left) and plug in the keyboard
* **Physical reset button**: Press the `RST` button while holding the `BOOT_SEL` button on the back of the PCB
