// Copyright 2021 Austin Wang (@Dafondo)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

enum unicode_names {
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011,
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111,
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211,
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311,
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k410, k411
};

const uint32_t PROGMEM unicode_map[] = {
    [k00]=0x9BCF, [k01]=0x9BF5, [k02]=0x9B8E, [k03]=0x9BC7, [k04]=0x9B91, [k05]=0x9B66, [k06]=0x9BD4, [k07]=0x9BC6, [k08]=0x9C2F, [k09]=0x9B87, [k010]=0x9BCF, [k011]=0x9C53, 
    [k10]=0x9C3B, [k11]=0x9C4F, [k12]=0x9C5B, [k13]=0x9C15, [k14]=0x9C27, [k15]=0x9C0D, [k16]=0x9C39, [k17]=0x9C5F, [k18]=0x9B73, [k19]=0x9C08, [k110]=0x9B8D, [k111]=0x9C5A, 
    [k20]=0x9BE8, [k21]=0x9BC9, [k22]=0x9BD2, [k23]=0x9B97, [k24]=0x9BB4, [k25]=0x9BAD, [k26]=0x9BEF, [k27]=0x9BD6, [k28]=0x9BAB, [k29]=0x9C75, [k210]=0x9C06, [k211]=0x9BE2, 
    [k30]=0x9C6A, [k31]=0x9BF1, [k32]=0x9B8A, [k33]=0x9BF3, [k34]=0x9C78, [k35]=0x9BD0, [k36]=0x9BAC, [k37]=0x9BDB, [k38]=0x9C16, [k39]=0x9C31, [k310]=0x9BB9, [k311]=0x9B5B, 
    [k40]=0x9C48, [k41]=0x9C58, [k42]=0x9C45, [k43]=0x9C0C, [k44]=0x9BD4, [k45]=0x9BF0, [k46]=0x9C0A, [k47]=0x9BB8, [k48]=0x9BCA, [k49]=0x9C23, [k410]=0x9C30, [k411]=0x9B6C
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        X(k00), X(k01), X(k02), X(k03), X(k04), X(k05), X(k06), X(k07), X(k08), X(k09), X(k010), X(k011),
        X(k10), X(k11), X(k12), X(k13), X(k14), X(k15), X(k16), X(k17), X(k18), X(k19), X(k110), X(k111),
        X(k20), X(k21), X(k22), X(k23), X(k24), X(k25), X(k26), X(k27), X(k28), X(k29), X(k210), X(k211),
        X(k30), X(k31), X(k32), X(k33), X(k34), X(k35), X(k36), X(k37), X(k38), X(k39), X(k310), X(k311),
        X(k40), X(k41), X(k42), X(k43), X(k44), X(k45), X(k46), X(k47), X(k48), X(k49), X(k410), X(k411)
    )
};
