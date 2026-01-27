# crkbd RGB matrix

set up to build on rp2040 mcus

## compile

requries `-e CONVERT_TO=rp2040_ce` except bootloader is already enabled in `leshowmapmatrix` dir

```bash
qmk compile -kb crkbd -km leshowmapmatrix
```

## flash

if using EE_HANDS:

```bash
qmk flash -kb crkbd -km leshowmapmatrix -bl uf2-split-right
qmk flash -kb crkbd -km leshowmapmatrix -bl uf2-split-left
```

mount RPI2 usb device and it should flash
