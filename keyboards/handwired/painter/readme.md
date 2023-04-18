# painter

Sample code to test displays. **See each individual board for pin information**.
You may need to adjust the display size defined on `painter/keymaps/<display>/config.h` or the SPI config (divisor and mode) on `painter/<mcu>/config.h`

* Keyboard Maintainer: QMK Community
* Hardware Availability: *n/a*

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/painter/<your_board> -km <display>
    

Flashing example for this keyboard:

    qmk flash -kb handwired/painter/<your_board> -km <display>
