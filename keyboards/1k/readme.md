# 1k

![1k](https://booth.pximg.net/aaeb2dda-e169-44c0-ba5a-5b42cc5c2627/i/3504781/c1708a8a-061b-4a6c-907d-72d0eab47d4a.png)

1% Custom mechanical keyboard. ATtiny85 powered, with 1*WS2812 LED, and the micronucleus bootloader.

**Note**: Due to limited firmware space, a _**lot**_ of features have to be disabled to get a functioning QMK based keyboard.

* Keyboard Maintainer: [MakotoKurauchi](https://github.com/MakotoKurauchi)
* Hardware Supported: 1k
* Hardware Availability: [booth](https://ninep.booth.pm/items/3504781)

Make example for this keyboard (after setting up your build environment):

    make 1k:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing
### Prerequisites

```bash
git clone https://github.com/micronucleus/micronucleus.git
cd micronucleus/commandline/
sudo make install
```

On Linux, you’ll need proper privileges to access the MCU. You can either use sudo when flashing firmware, or place [these files](https://github.com/micronucleus/micronucleus/blob/master/commandline/49-micronucleus.rules) in /etc/udev/rules.d/. Once added run the following:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

### Instructions

```bash
make 1k:default:flash

# or directly with...
micronucleus --run <firmware.hex>
```

### Recovery

* [Original Firmware](https://github.com/xiudi/Attiny85_vusb_pad_test)
* [Bootloader Repair](https://digistump.com/wiki/digispark/tutorials/proisp)
