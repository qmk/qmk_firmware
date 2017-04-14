## jd40 mkii keyboard firmware

    Pins:
    MATRIX_ROW_PINS { F0, F1, F5, B4 }
    MATRIX_COL_PINS { F4, D7, B5, B6, C6, C7, D4, D6, D5, D0, D1, D2 }
    RGB_DI_PIN D3	
	
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/jd40 folder. 
Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Amtel Flip to program your .hex file. 
