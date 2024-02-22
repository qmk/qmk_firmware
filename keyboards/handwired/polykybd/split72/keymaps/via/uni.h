#pragma once

#include "lang/named_glyphs.h"

enum unicode_names {
    /*[[[cog
    import cog
    import os
    import string
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
    glyph_index = 1
    glyph_key = sheet[f"A{glyph_index}"].value
    glyph_code = sheet[f"B{glyph_index}"].value
    rev_lookup = {}

    while glyph_key and not glyph_key.startswith("PRIVATE_EMOJI"):
        glyph_key = sheet[f"A{glyph_index}"].value
        glyph_code = sheet[f"B{glyph_index}"].value
        glyph_index = glyph_index + 1

    while glyph_key and glyph_key.startswith("PRIVATE_EMOJI"):
        cog.outl(f'[{idx}] = 0x{glyph_code},')
        glyph_key = sheet[f"A{glyph_index}"].value
        glyph_code = sheet[f"B{glyph_index}"].value
        glyph_index = glyph_index + 1
        idx = idx + 1

    while glyph_key and not glyph_key.startswith("LATIN_00C0"):
        glyph_key = sheet[f"A{glyph_index}"].value
        glyph_code = sheet[f"B{glyph_index}"].value
        glyph_index = glyph_index + 1
    while glyph_key and glyph_key.startswith("LATIN_0"):
        cog.outl(f'[{idx}] = 0x{glyph_code},')
        rev_lookup[glyph_code] = idx
        glyph_key = sheet[f"A{glyph_index}"].value
        glyph_code = sheet[f"B{glyph_index}"].value
        glyph_index = glyph_index + 1
        idx = idx + 1
    #capital sz
    cog.outl(f'[{idx}] = 0x1E9E,')
    rev_lookup["1E9E"] = idx
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
    [140] = 0xC0,
    [141] = 0xC1,
    [142] = 0xC2,
    [143] = 0xC3,
    [144] = 0xC4,
    [145] = 0xC5,
    [146] = 0xC6,
    [147] = 0xC7,
    [148] = 0xC8,
    [149] = 0xC9,
    [150] = 0xCA,
    [151] = 0xCB,
    [152] = 0xCC,
    [153] = 0xCD,
    [154] = 0xCE,
    [155] = 0xCF,
    [156] = 0xD0,
    [157] = 0xD1,
    [158] = 0xD2,
    [159] = 0xD3,
    [160] = 0xD4,
    [161] = 0xD5,
    [162] = 0xD6,
    [163] = 0xD7,
    [164] = 0xD8,
    [165] = 0xD9,
    [166] = 0xDA,
    [167] = 0xDB,
    [168] = 0xDC,
    [169] = 0xDD,
    [170] = 0xDE,
    [171] = 0xDF,
    [172] = 0xE0,
    [173] = 0xE1,
    [174] = 0xE2,
    [175] = 0xE3,
    [176] = 0xE4,
    [177] = 0xE5,
    [178] = 0xE6,
    [179] = 0xE7,
    [180] = 0xE8,
    [181] = 0xE9,
    [182] = 0xEA,
    [183] = 0xEB,
    [184] = 0xEC,
    [185] = 0xED,
    [186] = 0xEE,
    [187] = 0xEF,
    [188] = 0xF0,
    [189] = 0xF1,
    [190] = 0xF2,
    [191] = 0xF3,
    [192] = 0xF4,
    [193] = 0xF5,
    [194] = 0xF6,
    [195] = 0xF7,
    [196] = 0xF8,
    [197] = 0xF9,
    [198] = 0xFA,
    [199] = 0xFB,
    [200] = 0xFC,
    [201] = 0xFD,
    [202] = 0xFE,
    [203] = 0xFF,
    [204] = 0x100,
    [205] = 0x101,
    [206] = 0x102,
    [207] = 0x103,
    [208] = 0x104,
    [209] = 0x105,
    [210] = 0x106,
    [211] = 0x107,
    [212] = 0x108,
    [213] = 0x109,
    [214] = 0x10A,
    [215] = 0x10B,
    [216] = 0x10C,
    [217] = 0x10D,
    [218] = 0x10E,
    [219] = 0x10F,
    [220] = 0x110,
    [221] = 0x111,
    [222] = 0x112,
    [223] = 0x113,
    [224] = 0x114,
    [225] = 0x115,
    [226] = 0x116,
    [227] = 0x117,
    [228] = 0x118,
    [229] = 0x119,
    [230] = 0x11A,
    [231] = 0x11B,
    [232] = 0x11C,
    [233] = 0x11D,
    [234] = 0x11E,
    [235] = 0x11F,
    [236] = 0x120,
    [237] = 0x121,
    [238] = 0x122,
    [239] = 0x123,
    [240] = 0x124,
    [241] = 0x125,
    [242] = 0x126,
    [243] = 0x127,
    [244] = 0x128,
    [245] = 0x129,
    [246] = 0x12A,
    [247] = 0x12B,
    [248] = 0x12C,
    [249] = 0x12D,
    [250] = 0x12E,
    [251] = 0x12F,
    [252] = 0x130,
    [253] = 0x131,
    [254] = 0x132,
    [255] = 0x133,
    [256] = 0x134,
    [257] = 0x135,
    [258] = 0x136,
    [259] = 0x137,
    [260] = 0x138,
    [261] = 0x139,
    [262] = 0x13A,
    [263] = 0x13B,
    [264] = 0x13C,
    [265] = 0x13D,
    [266] = 0x13E,
    [267] = 0x13F,
    [268] = 0x140,
    [269] = 0x141,
    [270] = 0x142,
    [271] = 0x143,
    [272] = 0x144,
    [273] = 0x145,
    [274] = 0x146,
    [275] = 0x147,
    [276] = 0x148,
    [277] = 0x149,
    [278] = 0x14A,
    [279] = 0x14B,
    [280] = 0x14C,
    [281] = 0x14D,
    [282] = 0x14E,
    [283] = 0x14F,
    [284] = 0x150,
    [285] = 0x151,
    [286] = 0x152,
    [287] = 0x153,
    [288] = 0x154,
    [289] = 0x155,
    [290] = 0x156,
    [291] = 0x157,
    [292] = 0x158,
    [293] = 0x159,
    [294] = 0x15A,
    [295] = 0x15B,
    [296] = 0x15C,
    [297] = 0x15D,
    [298] = 0x15E,
    [299] = 0x15F,
    [300] = 0x160,
    [301] = 0x161,
    [302] = 0x162,
    [303] = 0x163,
    [304] = 0x164,
    [305] = 0x165,
    [306] = 0x166,
    [307] = 0x167,
    [308] = 0x168,
    [309] = 0x169,
    [310] = 0x16A,
    [311] = 0x16B,
    [312] = 0x16C,
    [313] = 0x16D,
    [314] = 0x16E,
    [315] = 0x16F,
    [316] = 0x170,
    [317] = 0x171,
    [318] = 0x172,
    [319] = 0x173,
    [320] = 0x174,
    [321] = 0x175,
    [322] = 0x176,
    [323] = 0x177,
    [324] = 0x178,
    [325] = 0x179,
    [326] = 0x17A,
    [327] = 0x17B,
    [328] = 0x17C,
    [329] = 0x17D,
    [330] = 0x17E,
    [331] = 0x1E9E,
    //[[[end]]]
};

/*[[[cog
latin_sheet = wb['latin_sup_ex']
d = dict.fromkeys(string.ascii_uppercase, 0)
d.update(dict.fromkeys(string.ascii_lowercase, 0))

max_variation_index = 0
letter_index = 1
current_letter = latin_sheet[f"A{letter_index}"].value
current_code = latin_sheet[f"B{letter_index+1}"].value
while current_letter:
    variations =  [ ]
    variation_index = 1
    while current_code:
        variations.append(current_code)
        max_variation_index = max(max_variation_index, variation_index)
        variation_index = variation_index + 1
        current_code = latin_sheet[f"{chr(ord('A')+variation_index)}{letter_index+1}"].value

    d.update({current_letter : variations})
    letter_index = letter_index + 2
    current_letter = latin_sheet[f"A{letter_index}"].value
    current_code = latin_sheet[f"B{letter_index+1}"].value

last_letter = latin_sheet[f"A{letter_index-2}"].value
last_index = ord(last_letter)

#cog.outl(f"const int8_t latin_ex_lookup[{last_index+1}] PROGMEM = {{")
#cog.out("  ")
#list_of_keys = list(d.keys())
#for k in range(last_index+1):
#    try:
#        i = list_of_keys.index(str(chr(k)))
#        cog.out(f"{i}")
#    except:
#        cog.out("-1")
#    if k!=last_index:
#        cog.out(", ")
]]]*/
//[[[end]]]
//};

/*[[[cog
cog.outl(f"static const uint16_t* latin_ex_map[26*2][{max_variation_index}] PROGMEM = {{")
idx = 0
for k, values in d.items():
    delim = ", "
    if values == 0:
        values = []
    else:
        values = [f'u"\\x{x}"' for x in values]

    values.extend(["NULL"] *(10- len(values)))
    cog.out("  /")
    cog.out(f"* [{idx}] {ord(k)}/{k} *")
    cog.out(f"/ {{ {delim.join(values)} }}")
    if ord(k)!=last_index:
        cog.outl(",")
    idx = idx + 1
]]]*/
static const uint16_t* latin_ex_map[26*2][10] PROGMEM = {
  /* [0] 65/A */ { u"\xC0", u"\xC1", u"\xC2", u"\xC3", u"\xC4", u"\xC5", u"\xC6", u"\x100", u"\x102", u"\x104" },
  /* [1] 66/B */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [2] 67/C */ { u"\xC7", u"\x106", u"\x108", u"\x10A", u"\x10C", NULL, NULL, NULL, NULL, NULL },
  /* [3] 68/D */ { u"\xD0", u"\x10E", u"\x110", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [4] 69/E */ { u"\xC8", u"\xC9", u"\xCA", u"\xCB", u"\x112", u"\x114", u"\x116", u"\x118", u"\x11A", NULL },
  /* [5] 70/F */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [6] 71/G */ { u"\x11C", u"\x11E", u"\x120", u"\x122", NULL, NULL, NULL, NULL, NULL, NULL },
  /* [7] 72/H */ { u"\x124", u"\x126", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [8] 73/I */ { u"\xEC", u"\xED", u"\xEE", u"\xEF", u"\x129", u"\x12B", u"\x12D", u"\x12F", u"\x131", u"\x133" },
  /* [9] 74/J */ { u"\x134", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [10] 75/K */ { u"\x136", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [11] 76/L */ { u"\x139", u"\x13B", u"\x13D", u"\x13F", u"\x141", NULL, NULL, NULL, NULL, NULL },
  /* [12] 77/M */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [13] 78/N */ { u"\xD1", u"\x143", u"\x145", u"\x147", u"\x14A", NULL, NULL, NULL, NULL, NULL },
  /* [14] 79/O */ { u"\xD2", u"\xD3", u"\xD4", u"\xD5", u"\xD6", u"\x14C", u"\x14E", u"\x150", u"\x152", u"\xD8" },
  /* [15] 80/P */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [16] 81/Q */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [17] 82/R */ { u"\x154", u"\x156", u"\x158", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [18] 83/S */ { u"\x1E9E", u"\x15A", u"\x15C", u"\x15E", u"\x160", NULL, NULL, NULL, NULL, NULL },
  /* [19] 84/T */ { u"\xDE", u"\x162", u"\x164", u"\x166", NULL, NULL, NULL, NULL, NULL, NULL },
  /* [20] 85/U */ { u"\xD9", u"\xDA", u"\xDB", u"\xDC", u"\x168", u"\x16A", u"\x16C", u"\x16E", u"\x170", u"\x172" },
  /* [21] 86/V */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [22] 87/W */ { u"\x174", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [23] 88/X */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [24] 89/Y */ { u"\xDD", u"\x176", u"\x178", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [25] 90/Z */ { u"\x179", u"\x17B", u"\x17D", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [26] 97/a */ { u"\xE0", u"\xE1", u"\xE2", u"\xE3", u"\xE4", u"\xE5", u"\xE6", u"\x101", u"\x103", u"\x105" },
  /* [27] 98/b */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [28] 99/c */ { u"\xE7", u"\x107", u"\x109", u"\x10B", u"\x10D", NULL, NULL, NULL, NULL, NULL },
  /* [29] 100/d */ { u"\xF0", u"\x10F", u"\x111", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [30] 101/e */ { u"\xE8", u"\xE9", u"\xEA", u"\xEB", u"\x113", u"\x115", u"\x117", u"\x119", u"\x11B", NULL },
  /* [31] 102/f */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [32] 103/g */ { u"\x11D", u"\x11F", u"\x121", u"\x123", NULL, NULL, NULL, NULL, NULL, NULL },
  /* [33] 104/h */ { u"\x125", u"\x127", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [34] 105/i */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [35] 106/j */ { u"\x135", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [36] 107/k */ { u"\x137", u"\x138", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [37] 108/l */ { u"\x13A", u"\x13C", u"\x13E", u"\x140", u"\x142", NULL, NULL, NULL, NULL, NULL },
  /* [38] 109/m */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [39] 110/n */ { u"\xF1", u"\x144", u"\x146", u"\x148", u"\x14B", u"\x149", NULL, NULL, NULL, NULL },
  /* [40] 111/o */ { u"\xF2", u"\xF3", u"\xF4", u"\xF5", u"\xF6", u"\x14D", u"\x14F", u"\x151", u"\x153", u"\xF8" },
  /* [41] 112/p */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [42] 113/q */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [43] 114/r */ { u"\x155", u"\x157", u"\x159", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [44] 115/s */ { u"\xDF", u"\x15B", u"\x15D", u"\x15F", u"\x161", NULL, NULL, NULL, NULL, NULL },
  /* [45] 116/t */ { u"\xFE", u"\x163", u"\x165", u"\x167", NULL, NULL, NULL, NULL, NULL, NULL },
  /* [46] 117/u */ { u"\xF9", u"\xFA", u"\xFB", u"\xFC", u"\x169", u"\x16B", u"\x16D", u"\x16F", u"\x171", u"\x173" },
  /* [47] 118/v */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [48] 119/w */ { u"\x175", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [49] 120/x */ { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [50] 121/y */ { u"\xFD", u"\x177", u"\xFF", NULL, NULL, NULL, NULL, NULL, NULL, NULL },
  /* [51] 122/z */ { u"\x17A", u"\x17C", u"\x17E", NULL, NULL, NULL, NULL, NULL, NULL, NULL }
//[[[end]]]
};

/*[[[cog
cog.outl(f"static const uint16_t latin_rev_ex_map[26*2][{max_variation_index}] PROGMEM = {{")
idx = 0
for k, values in d.items():
    delim = ", "
    if values == 0:
        values = []
    else:
        values = [f'{rev_lookup[x]}' for x in values]

    values.extend(["0"] *(10- len(values)))
    cog.out("  /")
    cog.out(f"* [{idx}] {ord(k)}/{k} *")
    cog.out(f"/ {{ {delim.join(values)} }}")
    if ord(k)!=last_index:
        cog.outl(",")
    idx = idx + 1
]]]*/
static const uint16_t latin_rev_ex_map[26*2][10] PROGMEM = {
  /* [0] 65/A */ { 140, 141, 142, 143, 144, 145, 146, 204, 206, 208 },
  /* [1] 66/B */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [2] 67/C */ { 147, 210, 212, 214, 216, 0, 0, 0, 0, 0 },
  /* [3] 68/D */ { 156, 218, 220, 0, 0, 0, 0, 0, 0, 0 },
  /* [4] 69/E */ { 148, 149, 150, 151, 222, 224, 226, 228, 230, 0 },
  /* [5] 70/F */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [6] 71/G */ { 232, 234, 236, 238, 0, 0, 0, 0, 0, 0 },
  /* [7] 72/H */ { 240, 242, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [8] 73/I */ { 184, 185, 186, 187, 245, 247, 249, 251, 253, 255 },
  /* [9] 74/J */ { 256, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [10] 75/K */ { 258, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [11] 76/L */ { 261, 263, 265, 267, 269, 0, 0, 0, 0, 0 },
  /* [12] 77/M */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [13] 78/N */ { 157, 271, 273, 275, 278, 0, 0, 0, 0, 0 },
  /* [14] 79/O */ { 158, 159, 160, 161, 162, 280, 282, 284, 286, 164 },
  /* [15] 80/P */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [16] 81/Q */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [17] 82/R */ { 288, 290, 292, 0, 0, 0, 0, 0, 0, 0 },
  /* [18] 83/S */ { 331, 294, 296, 298, 300, 0, 0, 0, 0, 0 },
  /* [19] 84/T */ { 170, 302, 304, 306, 0, 0, 0, 0, 0, 0 },
  /* [20] 85/U */ { 165, 166, 167, 168, 308, 310, 312, 314, 316, 318 },
  /* [21] 86/V */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [22] 87/W */ { 320, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [23] 88/X */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [24] 89/Y */ { 169, 322, 324, 0, 0, 0, 0, 0, 0, 0 },
  /* [25] 90/Z */ { 325, 327, 329, 0, 0, 0, 0, 0, 0, 0 },
  /* [26] 97/a */ { 172, 173, 174, 175, 176, 177, 178, 205, 207, 209 },
  /* [27] 98/b */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [28] 99/c */ { 179, 211, 213, 215, 217, 0, 0, 0, 0, 0 },
  /* [29] 100/d */ { 188, 219, 221, 0, 0, 0, 0, 0, 0, 0 },
  /* [30] 101/e */ { 180, 181, 182, 183, 223, 225, 227, 229, 231, 0 },
  /* [31] 102/f */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [32] 103/g */ { 233, 235, 237, 239, 0, 0, 0, 0, 0, 0 },
  /* [33] 104/h */ { 241, 243, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [34] 105/i */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [35] 106/j */ { 257, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [36] 107/k */ { 259, 260, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [37] 108/l */ { 262, 264, 266, 268, 270, 0, 0, 0, 0, 0 },
  /* [38] 109/m */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [39] 110/n */ { 189, 272, 274, 276, 279, 277, 0, 0, 0, 0 },
  /* [40] 111/o */ { 190, 191, 192, 193, 194, 281, 283, 285, 287, 196 },
  /* [41] 112/p */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [42] 113/q */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [43] 114/r */ { 289, 291, 293, 0, 0, 0, 0, 0, 0, 0 },
  /* [44] 115/s */ { 171, 295, 297, 299, 301, 0, 0, 0, 0, 0 },
  /* [45] 116/t */ { 202, 303, 305, 307, 0, 0, 0, 0, 0, 0 },
  /* [46] 117/u */ { 197, 198, 199, 200, 309, 311, 313, 315, 317, 319 },
  /* [47] 118/v */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [48] 119/w */ { 321, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [49] 120/x */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* [50] 121/y */ { 201, 323, 203, 0, 0, 0, 0, 0, 0, 0 },
  /* [51] 122/z */ { 326, 328, 330, 0, 0, 0, 0, 0, 0, 0 }
//[[[end]]]
};
