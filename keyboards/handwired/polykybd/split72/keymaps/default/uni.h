#pragma once

#include "lang/named_glyphs.h"

enum unicode_names {
    /*[[[cog
    import cog
    import os
    from openpyxl import load_workbook
    wb = load_workbook(filename = os.path.join(os.path.abspath(os.path.dirname(cog.inFile)), "lang/lang_lut.xlsx"), data_only=True)
    sheet = wb['named_glyphs']

    idx = 0
    glyph_index = 403
    glyph_key = sheet["A403"].value
    while glyph_key and glyph_key.startswith("PRIVATE_EMOJI"):
        glyph_key = sheet[f"A{glyph_index}"].value
        idx = idx + 1
        glyph_index = glyph_index + 1
    cog.outl(f'UM_A = {idx-1},')
    ]]]*/
    UM_A = 140,
    //[[[end]]]
    UM_AC,
    UM_O,
    UM_OC,
    UM_U,
    UM_UC,
    SZ,
    SZC
};

const uint32_t unicode_map[] PROGMEM = {
    /*[[[cog
    idx = 0
    glyph_index = 403
    glyph_key = sheet["A403"].value
    glyph_code = sheet["B403"].value
    while glyph_key and glyph_key.startswith("PRIVATE_EMOJI"):
        cog.outl(f'[{idx}] = 0x{glyph_code},')

        glyph_index = glyph_index + 1
        glyph_key = sheet[f"A{glyph_index}"].value
        glyph_code = sheet[f"B{glyph_index}"].value
        idx = idx + 1
    ]]]*/
    [0] = 0x1F600,
    [1] = 0x1F601,
    [2] = 0x1F602,
    [3] = 0x1F603,
    [4] = 0x1F604,
    [5] = 0x1F605,
    [6] = 0x1F606,
    [7] = 0x1F607,
    [8] = 0x1F608,
    [9] = 0x1F609,
    [10] = 0x1F60A,
    [11] = 0x1F60B,
    [12] = 0x1F60C,
    [13] = 0x1F60D,
    [14] = 0x1F60E,
    [15] = 0x1F60F,
    [16] = 0x1F610,
    [17] = 0x1F611,
    [18] = 0x1F612,
    [19] = 0x1F613,
    [20] = 0x1F614,
    [21] = 0x1F615,
    [22] = 0x1F616,
    [23] = 0x1F617,
    [24] = 0x1F618,
    [25] = 0x1F619,
    [26] = 0x1F61A,
    [27] = 0x1F61B,
    [28] = 0x1F61C,
    [29] = 0x1F61D,
    [30] = 0x1F61E,
    [31] = 0x1F61F,
    [32] = 0x1F620,
    [33] = 0x1F621,
    [34] = 0x1F622,
    [35] = 0x1F623,
    [36] = 0x1F624,
    [37] = 0x1F625,
    [38] = 0x1F626,
    [39] = 0x1F627,
    [40] = 0x1F628,
    [41] = 0x1F629,
    [42] = 0x1F62A,
    [43] = 0x1F62B,
    [44] = 0x1F62C,
    [45] = 0x1F62D,
    [46] = 0x1F62E,
    [47] = 0x1F62F,
    [48] = 0x1F630,
    [49] = 0x1F631,
    [50] = 0x1F632,
    [51] = 0x1F633,
    [52] = 0x1F634,
    [53] = 0x1F635,
    [54] = 0x1F636,
    [55] = 0x1F637,
    [56] = 0x1F638,
    [57] = 0x1F639,
    [58] = 0x1F644,
    [59] = 0x1F645,
    [60] = 0x1F646,
    [61] = 0x1F647,
    [62] = 0x1F648,
    [63] = 0x1F649,
    [64] = 0x1F64A,
    [65] = 0x1F64B,
    [66] = 0x1F64C,
    [67] = 0x1F64D,
    [68] = 0x1F64E,
    [69] = 0x1F64F,
    [70] = 0x1F440,
    [71] = 0x1F441,
    [72] = 0x1F442,
    [73] = 0x1F443,
    [74] = 0x1F444,
    [75] = 0x1F445,
    [76] = 0x1F446,
    [77] = 0x1F447,
    [78] = 0x1F448,
    [79] = 0x1F449,
    [80] = 0x1F44A,
    [81] = 0x1F44B,
    [82] = 0x1F44C,
    [83] = 0x1F44D,
    [84] = 0x1F44E,
    [85] = 0x1F44F,
    [86] = 0x1F450,
    [87] = 0x1F451,
    [88] = 0x1F452,
    [89] = 0x1F453,
    [90] = 0x1F47B,
    [91] = 0x1F47C,
    [92] = 0x1F47D,
    [93] = 0x1F47E,
    [94] = 0x1F47F,
    [95] = 0x1F480,
    [96] = 0x1F481,
    [97] = 0x1F482,
    [98] = 0x1F483,
    [99] = 0x1F484,
    [100] = 0x1F485,
    [101] = 0x1F489,
    [102] = 0x1F48A,
    [103] = 0x1F48B,
    [104] = 0x1F48C,
    [105] = 0x1F48D,
    [106] = 0x1F48E,
    [107] = 0x1F48F,
    [108] = 0x1F490,
    [109] = 0x1F491,
    [110] = 0x1F492,
    [111] = 0x1F493,
    [112] = 0x1F494,
    [113] = 0x1F495,
    [114] = 0x1F496,
    [115] = 0x1F4A1,
    [116] = 0x1F4A2,
    [117] = 0x1F4A3,
    [118] = 0x1F4A4,
    [119] = 0x1F4A5,
    [120] = 0x1F4A6,
    [121] = 0x1F4A7,
    [122] = 0x1F4A8,
    [123] = 0x1F4A9,
    [124] = 0x1F4AA,
    [125] = 0x1F4AB,
    [126] = 0x1F4AC,
    [127] = 0x1F4AD,
    [128] = 0x1F4AE,
    [129] = 0x1F4AF,
    [130] = 0x1F4B0,
    [131] = 0x1F4B1,
    [132] = 0x1F912,
    [133] = 0x1F913,
    [134] = 0x1F914,
    [135] = 0x1F915,
    [136] = 0x1F916,
    [137] = 0x1F917,
    [138] = 0x1F918,
    [139] = 0x1F919,
    //[[[end]]]
    [UM_A]  = UMLAUT_A_SMALL[0],
    [UM_AC] = UMLAUT_A[0],
    [UM_O]  = UMLAUT_O_SMALL[0],
    [UM_OC] = UMLAUT_O[0],
    [UM_U]  = UMLAUT_U_SMALL[0],
    [UM_UC] = UMLAUT_U[0],
    [SZ]  = ESZETT[0],
    [SZC] = 0x1E9E
};
