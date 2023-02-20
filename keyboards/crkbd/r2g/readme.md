# Corne R2G

![r2g](https://cdn.shopify.com/s/files/1/0582/0242/3501/products/HelidoxCorneR2GPCB_1800x1800.png)

An Eddition of the popular CRKBD featuring a full smd assembly

Keyboard Maintainer: [e11i0t23](https://github.com/e11i0t23/), [Mechboards UK](https://mechboards.co.uk)  
Hardware Supported: CRKBD R2G PCB   
Hardware Availability: [Mechboards UK](https://mechboards.co.uk/products/helidox-corne-kit?variant=40391708213453)  

Make example for this keyboard (after setting up your build environment):

```sh
make crkbd/r2g:mb_via
```

Flash example for this keyboard:  
```sh
qmk flash -kb crkbd/r2g -km mb_via
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

These PCBs have a reset on the underside of the PCB next to the TRRS jack to enter in to the bootloader.

Additionally, if you hold down the "Q" or "P" buttons when plugging in that half of the keyboard (per the default QWERTY layout), this will jump to the bootloader and reset the EEPROM (persistent storage).  
