# DirectPins

![Promicro Pinout Guide](https://i.imgur.com/LZ194Hf.jpg)

copy of the [ez_maker/directpins/promicro keyboard](https://github.com/qmk/qmk_firmware/tree/b2ded61796aee1f705a222e229c5b55416d93dd0/keyboards/ez_maker/directpins/promicro)

-   Compile: `qmk compile -kb scda/promicro_trackball -km default`
-   Flash: `qmk flash -kb scda/promicro_trackball -km default`

HW setup:

-   current config requires the following pimoroni board connections

| trackball | promicro         | notes                                       |
| --------- | ---------------- | ------------------------------------------- |
| GND       | GND              |
| 3.5V      | VCC              |
| SDA       | SDA / pin 2 / D1 | can be configured as `pin_a` in `info.json` |
| SCL       | SCL / pin 3 / D0 | can be configured as `pin_b` in `info.json` |
| INT       | unknown          | still to figure out                         |
