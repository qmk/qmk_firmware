# ANAVI Macro Pad 8

ANAVI Macro Pad 2 is an open source mini mechanical keyboard with 2 keys and backlit. Powered by ATtiny 85 microcontroller and with microUSB connector. Designed with KiCad.

* Keyboard Maintainer: [Leon Anavi](https://github.com/leon-anavi)
* Hardware Supported: ANAVI Macro Pad 2
* Hardware Availability: [PCB Files](https://github.com/AnaviTechnology/anavi-macro-pad-2)

**Note**: Due to limited firmware space, a _**lot**_ of features have to be disabled to get a functioning QMK based keyboard.

Make example for this keyboard (after setting up your build environment):

    make anavi/macropad2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing
### Prerequisites

```bash
git clone https://github.com/micronucleus/micronucleus.git
cd micronucleus/commandline/
sudo make install
```

On GNU/Linux distributions, you will need proper privileges to access the MCU. You can either use `sudo` when flashing firmware, or place [these files](https://github.com/micronucleus/micronucleus/blob/master/commandline/49-micronucleus.rules) in /etc/udev/rules.d/. Once added run the following:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

### Instructions

* Run one of the following commands:

```bash
make anavi/macropad2:default:flash

# or directly with...
micronucleus --run <firmware.hex>
```

* Plug ANAVI Macro Pad 2 to the USB port and the flashing procedure should start

### Recovery

* [Original Firmware](https://github.com/AnaviTechnology/anavi-macro-pad-2/tree/main/bootloader)
* [Bootloader Repair](https://digistump.com/wiki/digispark/tutorials/proisp)
