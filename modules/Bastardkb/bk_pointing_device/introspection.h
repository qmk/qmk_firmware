#pragma once

/*
    Previously we defined the keycodes in keyboard space.
    We switched to module space, which means the keycodes defined start at a different range.
    For legacy reasons, we manually define the keycodes here, so that we may stay backward compatible.
*/

#define DPI_MOD 0x7E00
#define DPI_RMOD 0x7E01
#define S_D_MOD 0x7E02
#define S_D_RMOD 0x7E03
#define SNIPING 0x7E04
#define SNP_TOG 0x7E05
#define DRGSCRL 0x7E06
#define DRG_TOG 0x7E07