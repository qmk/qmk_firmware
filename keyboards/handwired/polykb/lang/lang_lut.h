//File content partially generated!
//Execute the following command to do so (via cogapp):
//cog -r lang_lut.h
#pragma once
#include "named_glyphs.h"

enum {ALPHA = 26, NUM = 10, ADDITIONAL = 17};
enum lang_layer { 
    /*[[[cog
    import cog
    from openpyxl import load_workbook
    wb = load_workbook(filename = 'lang_lut.xlsx')
    sheet = wb['key_lut']

    lang_index = 0
    lang_key = sheet["B1"].value
    while lang_key:
        if lang_index==0:
            cog.outl(f"\t{lang_key} = 0,")
        else:
            cog.outl(f"\t{lang_key},")
        lang_index = lang_index + 1
        lang_key = sheet[chr(ord('B')+lang_index*3)+"1"].value
    ]]]*/
    LANG_EN = 0,
    LANG_DE,
    LANG_FR,
    LANG_ES,
    LANG_KO,
    LANG_JA,
    LANG_AR,
    //[[[end]]]
    NUM_LANG };

const uint16_t* translate_keycode(uint8_t used_lang, uint16_t keycode, bool shift, bool caps_lock);
