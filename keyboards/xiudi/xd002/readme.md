# xd002

![xd002](https://cdn.shopify.com/s/files/1/2711/4238/products/xd002_1024x1024.jpg?v=1522134411)

2% Custom mechanical keyboard. ATtiny85 powered, with 2*WS2812 LEDs, and the micronucleus bootloader.

**Note**: Due to limited firmware space, a _**lot**_ of features have to be disabled to get a functioning QMK based keyboard.

* Keyboard Maintainer: [zvecr](https://github.com/zvecr)
* Hardware Supported: xd002
* Hardware Availability: [kprepublic](https://kprepublic.com/products/xd002-xiudi-2-custom-mechanical-keyboard-2-keys-underglow-and-switch-rgb-pcb-programmed-hot-swappable-macro-key-aluminum-case)

Make example for this keyboard (after setting up your build environment):

    make xiudi/xd002:default

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

**Reset Key**: Hold down key nearest to the USB socket while plugging in the keyboard.

```bash
make xiudi/xd002:default:flash

# or directly with...
micronucleus --run <firmware.hex>
```

### Recovery

* [Original Firmware](https://github.com/xiudi/Attiny85_vusb_pad_test)
* [Bootloader Repair](https://digistump.com/wiki/digispark/tutorials/proisp)
