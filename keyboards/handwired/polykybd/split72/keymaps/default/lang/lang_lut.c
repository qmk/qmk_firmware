//File content partially generated!
//Execute the following command to do so (via cogapp):
//cog -r lang_lut.c
#include "lang_lut.h"
#include "polykybd.h"

static const uint16_t* lang_plane [ALPHA + NUM + ADDITIONAL][NUM_LANG * 3] = {
    /*[[[cog
    import cog
    import os
    from openpyxl import load_workbook
    wb = load_workbook(filename = os.path.join(os.path.abspath(os.path.dirname(cog.inFile)), "lang_lut.xlsx"), data_only=True)
    sheet = wb['key_lut']

    #build a list of known glyphs
    named_glyphs = []
    sheet_named_glyphs = wb['named_glyphs']
    for r in range(2,sheet_named_glyphs.max_row+1):
        named_glyphs.append(sheet_named_glyphs.cell(row = r, column = 1).value)

    #build a dict with all languages
    lang_dict = {}
    lang_index = 0
    lang_key = sheet["B1"].value
    while lang_key:
        lang_dict[lang_index] = lang_key
        lang_index = lang_index + 1
        lang_key = sheet.cell(row = 1, column = 2 + lang_index*3).value

    #helper to make the string for a key
    def make_key(text, sub):
        if not text:
            if not sub:
                return "NULL"
            else:
                text = ""
        else:
            if text not in named_glyphs and not str(text).startswith('u"'):
                text = f'u"{text}"'
            if not sub:
                return text

        if sub in named_glyphs or str(sub).startswith('u"'):
            return f'{text} u"\\r\\v\\t" {sub}'
        else:
            return f'{text} u"\\r\\v\\t{sub}"'

    #helper to make all 3 strings (lower, upper, caps) needed for a key and language
    def make_lang_key(idx, row, prepend_comment, append_comma):
        lang_row = ""
        if prepend_comment:
            lang_row = '/' + f'*  {lang_dict[idx] : <9}*' + '/  '
        for case_idx in range(0, 3):
            text = sheet.cell(row = row, column = 2 + idx*3+case_idx).value
            sub = sheet.cell(row = row+1, column = 2 + idx*3+case_idx).value

            composed = make_key(text, sub)
            if case_idx != 2 or append_comma:
                composed = composed + ","
                lang_row = f"{lang_row}{composed:<30}"
            else:
                lang_row = f"{lang_row}{composed}"

        return lang_row

    #create actual language lookup table
    key_index = 2
    key_name = sheet["A2"].value
    glyph_code = sheet["D2"].value
    while key_name:
        cog.out('/' + f'*{key_name : <11}*' + '/ {')

        for idx in lang_dict:
            cog.outl(f'{make_lang_key(idx, key_index, idx>0, idx < lang_index-1)}')
        cog.outl("},")

        key_index = key_index + 2
        key_name = sheet.cell(row = key_index, column = 1).value

    ]]]*/
    /*KC_A       */ {u"a",                         u"A",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  u"q",                         u"Q",                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  u"a" u"\r\v\t" LETTER_AE_SMALL,u"A" u"\r\v\t" LETTER_AE_SMALL,NULL,                         
    /*  LANG_KO  */  HANGEUL_MIEUM,                NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_TI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_SHEEN,                 BACKSLASH,                    ARABIC_SHEEN,                 
    /*  LANG_GR  */  GREEK_SM_ALPHA,               GREEK_ALPHA,                  NULL
    },
    /*KC_B       */ {u"b",                         u"B",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_YU,                   NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_KO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_LAM_ALEF,              ARABIC_LAM_ALEF_MADDA,        NULL,                         
    /*  LANG_GR  */  GREEK_SM_BETA,                GREEK_BETA,                   NULL
    },
    /*KC_C       */ {u"c",                         u"C",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_CHIEUCH,              NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_SO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_WAW_HAMZA_A,           ARABIC_KASRA,                 ARABIC_WAW_HAMZA_A,           
    /*  LANG_GR  */  GREEK_SM_PSI u"\r\v\t" COPYRIGHT_SIGN,GREEK_PSI u"\r\v\t" COPYRIGHT_SIGN,NULL
    },
    /*KC_D       */ {u"d",                         u"D",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_IEUNG,                NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_SI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_YEH,                   u"]",                         ARABIC_YEH,                   
    /*  LANG_GR  */  GREEK_SM_DELTA,               GREEK_DELTA,                  NULL
    },
    /*KC_E       */ {u"e",                         u"E",                         NULL,                         
    /*  LANG_DE  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_FR  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_ES  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_PT  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_IT  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_TR  */  u"e" u"\r\v\t" EURO_SIGN,     u"E" u"\r\v\t" EURO_SIGN,     NULL,                         
    /*  LANG_KO  */  HANGEUL_TIKEUT,               HANGEUL_SSANGTIKEUT,          NULL,                         
    /*  LANG_JA  */  HIRAGANA_I,                   HIRAGANA_SMALL_I,             NULL,                         
    /*  LANG_AR  */  ARABIC_THEH,                  u"\v" ARABIC_DAMMA,           ARABIC_THEH,                  
    /*  LANG_GR  */  GREEK_SM_EPSILON u"\r\v\t" EURO_SIGN,GREEK_EPSILON u"\r\v\t" EURO_SIGN,NULL
    },
    /*KC_F       */ {u"f",                         u"F",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_RIEUL,                NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_HA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_BEH,                   u"[",                         ARABIC_BEH,                   
    /*  LANG_GR  */  GREEK_SM_PHI,                 GREEK_PHI,                    NULL
    },
    /*KC_G       */ {u"g",                         u"G",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_HIEUH,                NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_KI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_LAM,                   NULL,                         NULL,                         
    /*  LANG_GR  */  GREEK_SM_GAMMA,               GREEK_GAMMA,                  NULL
    },
    /*KC_H       */ {u"h",                         u"H",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_O,                    NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_KU,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_ALEF,                  ARABIC_ALEF_HAMZA_A,          ARABIC_ALEF,                  
    /*  LANG_GR  */  GREEK_SM_ETA,                 GREEK_ETA,                    NULL
    },
    /*KC_I       */ {u"i",                         u"I",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  I_DOTLESS_SMALL u"\r\v\ti",   u"I" u"\r\v\ti",              NULL,                         
    /*  LANG_KO  */  HANGEUL_YA,                   NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_RI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_HEH,                   DEVISION_SIGN,                ARABIC_HEH,                   
    /*  LANG_GR  */  GREEK_SM_IOTA,                GREEK_IOTA,                   NULL
    },
    /*KC_J       */ {u"j",                         u"J",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_EO,                   NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_MA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_TEH,                   ARABIC_TATWEEL,               ARABIC_TEH,                   
    /*  LANG_GR  */  GREEK_SM_XI,                  GREEK_XI,                     NULL
    },
    /*KC_K       */ {u"k",                         u"K",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_A,                    NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_NO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_NOON,                  ARABIC_COMMA,                 ARABIC_NOON,                  
    /*  LANG_GR  */  GREEK_SM_KAPPA,               GREEK_KAPPA,                  NULL
    },
    /*KC_L       */ {u"l",                         u"L",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_I,                    NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_RI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_MEEM,                  u"/",                         ARABIC_MEEM,                  
    /*  LANG_GR  */  GREEK_SM_LAMDA,               GREEK_LAMDA,                  NULL
    },
    /*KC_M       */ {u"m",                         u"M",                         NULL,                         
    /*  LANG_DE  */  u"m" u"\r\v\t" MICRO_SIGN,    u"M" u"\r\v\t" MICRO_SIGN,    NULL,                         
    /*  LANG_FR  */  u",",                         u"?",                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_EU,                   NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_MO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_WAW,                   GRAVE_ACCENT,                 ARABIC_WAW,                   
    /*  LANG_GR  */  GREEK_SM_MU,                  GREEK_MU,                     NULL
    },
    /*KC_N       */ {u"n",                         u"N",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_U,                    NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_MI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_ALEF_MAKSURA,          ARABIC_ALEF_MADDA_A,          ARABIC_ALEF_MAKSURA,          
    /*  LANG_GR  */  GREEK_SM_NU,                  GREEK_NU,                     NULL
    },
    /*KC_O       */ {u"o",                         u"O",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_AE,                   HANGEUL_YAE,                  NULL,                         
    /*  LANG_JA  */  HIRAGANA_RA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_TEH_MARBUTA,           MUL_SIGN,                     ARABIC_TEH_MARBUTA,           
    /*  LANG_GR  */  GREEK_SM_OMICRON,             GREEK_OMICRON,                NULL
    },
    /*KC_P       */ {u"p",                         u"P",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_E,                    HANGEUL_YE,                   NULL,                         
    /*  LANG_JA  */  HIRAGANA_SE,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_HAH,                   ARABIC_SEMICOLON,             ARABIC_HAH,                   
    /*  LANG_GR  */  GREEK_SM_PI,                  GREEK_PI,                     NULL
    },
    /*KC_Q       */ {u"q",                         u"Q",                         NULL,                         
    /*  LANG_DE  */  u"q" u"\r\v\t@",              u"Q" u"\r\v\t@",              NULL,                         
    /*  LANG_FR  */  u"a",                         u"A",                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  u"q" u"\r\v\t@",              u"Q" u"\r\v\t@",              NULL,                         
    /*  LANG_KO  */  HANGEUL_PIEUP,                HANGEUL_SSANGPIEUP,           NULL,                         
    /*  LANG_JA  */  HIRAGANA_TA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_DAD,                   u"\v" ARABIC_FATHA,           ARABIC_DAD,                   
    /*  LANG_GR  */  u";",                         u":",                         u";"
    },
    /*KC_R       */ {u"r",                         u"R",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */   u"\r\v\t" ESZETT,             u"\r\v\t" ESZETT,            NULL,                         
    /*  LANG_KO  */  HANGEUL_KIYEOK,               HANGEUL_SSANGKIYEOK,          NULL,                         
    /*  LANG_JA  */  HIRAGANA_SU,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_QAF u"\r\v\t" CURRENCY_SIGN,u"\v" ARABIC_DAMMATAN u"\r\v\t" CURRENCY_SIGN,ARABIC_QAF u"\r\v\t" CURRENCY_SIGN,
    /*  LANG_GR  */  GREEK_SM_RHO u"\r\v\t" REGISTERED_SIGN,GREEK_RHO u"\r\v\t" REGISTERED_SIGN,NULL
    },
    /*KC_S       */ {u"s",                         u"S",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_NIEUN,                NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_TO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_SEEN,                  NULL,                         NULL,                         
    /*  LANG_GR  */  GREEK_SM_SIGMA,               GREEK_SIGMA,                  NULL
    },
    /*KC_T       */ {u"t",                         u"T",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_SIOS,                 HANGEUL_SSANGSIOS,            NULL,                         
    /*  LANG_JA  */  HIRAGANA_KA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_FEH,                   NULL,                         NULL,                         
    /*  LANG_GR  */  GREEK_SM_TAU,                 GREEK_TAU,                    NULL
    },
    /*KC_U       */ {u"u",                         u"U",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_YEO,                  NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_NA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_AIN,                   ACUTE_ACCENT,                 ARABIC_AIN,                   
    /*  LANG_GR  */  GREEK_SM_THETA,               GREEK_THETA,                  NULL
    },
    /*KC_V       */ {u"v",                         u"V",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_PHIEUPH,              NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_HI,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_REH,                   ARABIC_KASRATAN,              ARABIC_REH,                   
    /*  LANG_GR  */  GREEK_SM_OMEGA,               GREEK_OMEGA,                  NULL
    },
    /*KC_W       */ {u"w",                         u"W",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  u"z",                         u"Z",                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_CIEUC,                HANGEUL_SSANGCIEUC,           NULL,                         
    /*  LANG_JA  */  HIRAGANA_TE,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_SAD,                   u"\v" ARABIC_FATHATAN,        ARABIC_SAD,                   
    /*  LANG_GR  */  GREEK_SM_FINAL_SIGMA,         GREEK_DIALYTIKA_TONOS,        GREEK_SM_FINAL_SIGMA
    },
    /*KC_X       */ {u"x",                         u"X",                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_THIEUTH,              NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_SA,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_HAMZA,                 u"\v" ARABIC_SUKUN,           ARABIC_HAMZA,                 
    /*  LANG_GR  */  GREEK_SM_CHI,                 GREEK_CHI,                    NULL
    },
    /*KC_Y       */ {u"y",                         u"Y",                         NULL,                         
    /*  LANG_DE  */  u"z",                         u"Z",                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_YO,                   NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_N,                   NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_GHAIN,                 ARABIC_ALEF_HAMZA_B,          ARABIC_GHAIN,                 
    /*  LANG_GR  */  GREEK_SM_UPSILON u"\r\v\t" YEN_SIGN,GREEK_UPSILON u"\r\v\t" YEN_SIGN,NULL
    },
    /*KC_Z       */ {u"z",                         u"Z",                         NULL,                         
    /*  LANG_DE  */  u"y",                         u"Y",                         NULL,                         
    /*  LANG_FR  */  u"w",                         u"W",                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  HANGEUL_KHIEUKH,              NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_TU,                  HIRAGANA_SMALL_TU,            NULL,                         
    /*  LANG_AR  */  ARABIC_YEH_HAMZA_A,           u"~",                         ARABIC_YEH_HAMZA_A,           
    /*  LANG_GR  */  GREEK_SM_ZETA,                NULL,                         NULL
    },
    /*KC_1       */ {u"1",                         u"!",                         u"1",                         
    /*  LANG_DE  */  u"1",                         u"!",                         NULL,                         
    /*  LANG_FR  */  u"&",                         u"1",                         NULL,                         
    /*  LANG_ES  */  u"1" u"\r\v\t|",              u"!" u"\r\v\t|",              u"1" u"\r\v\t|",              
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  u"1" u"\r\v\t>",              u"!" u"\r\v\t>",              u"1" u"\r\v\t>",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_NU,                  NULL,                         NULL,                         
    /*  LANG_AR  */  u"1" u"\r\v\t" ARABIC_INDIC_1,u"!" u"\r\v\t" ARABIC_INDIC_1,u"1" u"\r\v\t" ARABIC_INDIC_1,
    /*  LANG_GR  */  u"1",                         u"!",                         u"1"
    },
    /*KC_2       */ {u"2",                         u"@",                         u"2",                         
    /*  LANG_DE  */  u"2" u"\r\v\t" SUPER_SCRIPT_2,QUOTE u"\r\v\t" SUPER_SCRIPT_2,NULL,                         
    /*  LANG_FR  */  E_WITH_ACUTE_SMALL u"\r\v\t~",u"2" u"\r\v\t~",              NULL,                         
    /*  LANG_ES  */  u"2" u"\r\v\t@",              QUOTE u"\r\v\t@",             u"2" u"\r\v\t@",              
    /*  LANG_PT  */  u"2" u"\r\v\t@",              QUOTE u"\r\v\t@",             u"2" u"\r\v\t@",              
    /*  LANG_IT  */  u"2",                         QUOTE,                        u"2",                         
    /*  LANG_TR  */  u"2" u"\r\v\t" POUND_SIGN,    u"'" u"\r\v\t" POUND_SIGN,    u"2" u"\r\v\t" POUND_SIGN,    
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_HU,                  NULL,                         NULL,                         
    /*  LANG_AR  */  u"2" u"\r\v\t" ARABIC_INDIC_2,u"@" u"\r\v\t" ARABIC_INDIC_2,u"2" u"\r\v\t" ARABIC_INDIC_2,
    /*  LANG_GR  */  u"2" u"\r\v\t" SUPER_SCRIPT_2,u"@" u"\r\v\t" SUPER_SCRIPT_3,u"2" u"\r\v\t" SUPER_SCRIPT_2
    },
    /*KC_3       */ {u"3",                         u"#",                         u"3",                         
    /*  LANG_DE  */  u"3" u"\r\v\t" SUPER_SCRIPT_3,SECTION u"\r\v\t" SUPER_SCRIPT_3,NULL,                         
    /*  LANG_FR  */  QUOTE u"\r\v\t#",             u"3" u"\r\v\t#",              NULL,                         
    /*  LANG_ES  */  u"3" u"\r\v\t#",              MIDDLE_DOT u"\r\v\t#",        u"3" u"\r\v\t#",              
    /*  LANG_PT  */  u"3" u"\r\v\t" POUND_SIGN,    u"#" u"\r\v\t" POUND_SIGN,    u"3" u"\r\v\t" POUND_SIGN,    
    /*  LANG_IT  */  u"3",                         POUND_SIGN,                   u"3",                         
    /*  LANG_TR  */  u"3" u"\r\v\t#",              u"^" u"\r\v\t#",              u"3" u"\r\v\t#",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_A,                   HIRAGANA_SMALL_A,             NULL,                         
    /*  LANG_AR  */  u"3" u"\r\v\t" ARABIC_INDIC_3,u"#" u"\r\v\t" ARABIC_INDIC_3,u"3" u"\r\v\t" ARABIC_INDIC_3,
    /*  LANG_GR  */  u"3" u"\r\v\t" SUPER_SCRIPT_3,u"#" u"\r\v\tSUPER_SCRIPT_4", u"3" u"\r\v\t" SUPER_SCRIPT_3
    },
    /*KC_4       */ {u"4",                         u"$",                         u"4",                         
    /*  LANG_DE  */  u"4",                         u"$",                         NULL,                         
    /*  LANG_FR  */  u"'" u"\r\v\t{",              u"4" u"\r\v\t{",              NULL,                         
    /*  LANG_ES  */  u"4" u"\r\v\t~",              u"$" u"\r\v\t~",              u"4" u"\r\v\t~",              
    /*  LANG_PT  */  u"4" u"\r\v\t" SECTION,       u"$" u"\r\v\t" SECTION,       u"4" u"\r\v\t" SECTION,       
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  u"4" u"\r\v\t$",              u"+" u"\r\v\t$",              u"4" u"\r\v\t$",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_U,                   HIRAGANA_SMALL_U,             NULL,                         
    /*  LANG_AR  */  u"4" u"\r\v\t" ARABIC_INDIC_4,u"$" u"\r\v\t" ARABIC_INDIC_4,u"4" u"\r\v\t" ARABIC_INDIC_4,
    /*  LANG_GR  */  u"4" u"\r\v\t" POUND_SIGN,    u"$" u"\r\v\t" POUND_SIGN,    u"4" u"\r\v\t" POUND_SIGN
    },
    /*KC_5       */ {u"5",                         u"%",                         u"5",                         
    /*  LANG_DE  */  u"5",                         u"%",                         NULL,                         
    /*  LANG_FR  */  u"(" u"\r\v\t[",              u"5" u"\r\v\t[",              NULL,                         
    /*  LANG_ES  */  u"5" u"\r\v\t" EURO_SIGN,     u"%" u"\r\v\t" EURO_SIGN,     u"5" u"\r\v\t" EURO_SIGN,     
    /*  LANG_PT  */  u"5" u"\r\v\t" EURO_SIGN,     u"%" u"\r\v\t" EURO_SIGN,     u"5" u"\r\v\t" EURO_SIGN,     
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  u"5" u"\r\v\t" HALF_SIGN,     u"%" u"\r\v\t" HALF_SIGN,     u"5" u"\r\v\t" HALF_SIGN,     
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_E,                   HIRAGANA_SMALL_E,             NULL,                         
    /*  LANG_AR  */  u"5" u"\r\v\t" ARABIC_INDIC_5,u"%" u"\r\v\t" ARABIC_INDIC_5,u"5" u"\r\v\t" ARABIC_INDIC_5,
    /*  LANG_GR  */  u"5" u"\r\v\t" SECTION,       u"%" u"\r\v\t" SECTION,       u"5" u"\r\v\t" SECTION
    },
    /*KC_6       */ {u"6",                         u"^",                         u"6",                         
    /*  LANG_DE  */  u"6",                         u"&",                         NULL,                         
    /*  LANG_FR  */  u"-" u"\r\v\t|",              u"6" u"\r\v\t|",              NULL,                         
    /*  LANG_ES  */  u"6" u"\r\v\t" NOT_SIGN,      u"&" u"\r\v\t" NOT_SIGN,      u"6" u"\r\v\t" NOT_SIGN,      
    /*  LANG_PT  */  u"6",                         u"&",                         u"6",                         
    /*  LANG_IT  */  u"6",                         u"&",                         u"6",                         
    /*  LANG_TR  */  u"6",                         u"&",                         u"6",                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_O,                   HIRAGANA_SMALL_O,             NULL,                         
    /*  LANG_AR  */  u"6" u"\r\v\t" ARABIC_INDIC_6,u"^" u"\r\v\t" ARABIC_INDIC_6,u"6" u"\r\v\t" ARABIC_INDIC_6,
    /*  LANG_GR  */  u"6" u"\r\v\t" PILCROW,       u"^" u"\r\v\t" PILCROW,       u"6" u"\r\v\t" PILCROW
    },
    /*KC_7       */ {u"7",                         u"&",                         u"7",                         
    /*  LANG_DE  */  u"7" u"\r\v\t{",              u"/" u"\r\v\t{",              NULL,                         
    /*  LANG_FR  */  E_WITH_GRAVE_SMALL u"\r\v\t" ACUTE_ACCENT,u"7" u"\r\v\t" ACUTE_ACCENT,  NULL,                         
    /*  LANG_ES  */  u"7",                         u"/",                         u"7",                         
    /*  LANG_PT  */  u"7" u"\r\v\t{",              u"/" u"\r\v\t{",              u"7" u"\r\v\t{",              
    /*  LANG_IT  */  u"7",                         u"/",                         u"7",                         
    /*  LANG_TR  */  u"7" u"\r\v\t{",              u"/" u"\r\v\t{",              u"7" u"\r\v\t{",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_YA,                  HIRAGANA_SMALL_YA,            NULL,                         
    /*  LANG_AR  */  u"7" u"\r\v\t" ARABIC_INDIC_7,u"&" u"\r\v\t" ARABIC_INDIC_7,u"7" u"\r\v\t" ARABIC_INDIC_7,
    /*  LANG_GR  */  u"7",                         u"&",                         u"7"
    },
    /*KC_8       */ {u"8",                         u"*",                         u"8",                         
    /*  LANG_DE  */  u"8" u"\r\v\t[",              u"(" u"\r\v\t[",              NULL,                         
    /*  LANG_FR  */  u"_" u"\r\v\t" BACKSLASH,     u"8" u"\r\v\t" BACKSLASH,     NULL,                         
    /*  LANG_ES  */  u"8",                         u"(",                         u"8",                         
    /*  LANG_PT  */  u"8" u"\r\v\t[",              u"(" u"\r\v\t[",              u"8" u"\r\v\t[",              
    /*  LANG_IT  */  u"8",                         u"(",                         u"8",                         
    /*  LANG_TR  */  u"8" u"\r\v\t[",              u"(" u"\r\v\t[",              u"8" u"\r\v\t[",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_YU,                  HIRAGANA_SMALL_YU,            NULL,                         
    /*  LANG_AR  */  u"8" u"\r\v\t" ARABIC_INDIC_8,u"*" u"\r\v\t" ARABIC_INDIC_8,u"8" u"\r\v\t" ARABIC_INDIC_8,
    /*  LANG_GR  */  u"8" u"\r\v\t" CURRENCY_SIGN, u"*" u"\r\v\t" CURRENCY_SIGN, u"8" u"\r\v\t" CURRENCY_SIGN
    },
    /*KC_9       */ {u"9",                         u"(",                         u"9",                         
    /*  LANG_DE  */  u"9" u"\r\v\t]",              u")" u"\r\v\t]",              NULL,                         
    /*  LANG_FR  */  C_WITH_CEDILLA_SMALL u"\r\v\t^",u"9" u"\r\v\t^",              NULL,                         
    /*  LANG_ES  */  u"9",                         u")",                         u"9",                         
    /*  LANG_PT  */  u"9" u"\r\v\t]",              u")" u"\r\v\t]",              u"9" u"\r\v\t]",              
    /*  LANG_IT  */  u"9",                         u")",                         u"9",                         
    /*  LANG_TR  */  u"9" u"\r\v\t]",              u")" u"\r\v\t]",              u"9" u"\r\v\t]",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_YO,                  HIRAGANA_SMALL_YO,            NULL,                         
    /*  LANG_AR  */  u"9" u"\r\v\t" ARABIC_INDIC_9,u"(" u"\r\v\t" ARABIC_INDIC_9,u"9" u"\r\v\t" ARABIC_INDIC_9,
    /*  LANG_GR  */  u"9" u"\r\v\t" BROKEN_BAR,    u"(" u"\r\v\t" BROKEN_BAR,    u"9" u"\r\v\t" BROKEN_BAR
    },
    /*KC_0       */ {ZERO,                         u")",                         ZERO,                         
    /*  LANG_DE  */  ZERO u"\r\v\t}",              EQUALS u"\r\v\t}",            NULL,                         
    /*  LANG_FR  */  A_WITH_GRAVE_SMALL u"\r\v\t@",ZERO u"\r\v\t@",              NULL,                         
    /*  LANG_ES  */  ZERO,                         EQUALS,                       ZERO,                         
    /*  LANG_PT  */  ZERO u"\r\v\t}",              EQUALS u"\r\v\t}",            ZERO u"\r\v\t}",              
    /*  LANG_IT  */  ZERO,                         EQUALS,                       ZERO,                         
    /*  LANG_TR  */  ZERO u"\r\v\t}",              EQUALS u"\r\v\t}",            ZERO u"\r\v\t}",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_WA,                  HIRAGANA_WO,                  NULL,                         
    /*  LANG_AR  */  ZERO u"\r\v\t" ARABIC_INDIC_0,u")" u"\r\v\t" ARABIC_INDIC_0,ZERO u"\r\v\t" ARABIC_INDIC_0,
    /*  LANG_GR  */   u"\r\v\t" DEGREE,            u")" u"\r\v\t" DEGREE,         u"\r\v\t" DEGREE
    },
    /*KC_ENTER   */ {u"Ent",                       NULL,                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  NULL,                         NULL,                         NULL
    },
    /*KC_ESCAPE  */ {u"Esc",                       NULL,                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  NULL,                         NULL,                         NULL
    },
    /*KC_BACKSPACE*/ {ICON_BACKSPACE,               NULL,                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  NULL,                         NULL,                         NULL
    },
    /*KC_TAB     */ {u"Tab",                       NULL,                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  NULL,                         NULL,                         NULL
    },
    /*KC_SPACE   */ {ICON_SPACE,                   NULL,                         NULL,                         
    /*  LANG_DE  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_FR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_ES  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_PT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_IT  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_TR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  NULL,                         NULL,                         NULL
    },
    /*KC_MINUS   */ {u"-",                         u"_",                         u"-",                         
    /*  LANG_DE  */  ESZETT u"\r\v\t" BACKSLASH,   u"?" u"\r\v\t" BACKSLASH,     ESZETT u"\r\v\t" BACKSLASH,   
    /*  LANG_FR  */  u")" u"\r\v\t]",              DEGREE u"\r\v\t]",            NULL,                         
    /*  LANG_ES  */  u"'",                         u"?",                         u"'",                         
    /*  LANG_PT  */  u"'",                         u"?",                         u"'",                         
    /*  LANG_IT  */  u"'" u"\r\v\t^",              u"?" u"\r\v\t^",              u"'" u"\r\v\t^",              
    /*  LANG_TR  */  u"*" u"\r\v\t" BACKSLASH,     u"?" u"\r\v\t" BACKSLASH,     u"*" u"\r\v\t" BACKSLASH,     
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_HO,                  KH_PSOUNDM,                   NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  u"-" u"\r\v\t" PLUS_MINUS,    u"_" u"\r\v\t" PLUS_MINUS,    u"-" u"\r\v\t" PLUS_MINUS
    },
    /*KC_EQUAL   */ {EQUALS,                       u"+",                         EQUALS,                       
    /*  LANG_DE  */  GRAVE_ACCENT,                 ACUTE_ACCENT,                 GRAVE_ACCENT,                 
    /*  LANG_FR  */  EQUALS u"\r\v\t}",            u"+" u"\r\v\t}",              NULL,                         
    /*  LANG_ES  */  INVERTED_EMARK,               INVERTED_QMARK,               INVERTED_EMARK,               
    /*  LANG_PT  */  DBL_ANGLE_QMARK_L,            DBL_ANGLE_QMARK_R,            DBL_ANGLE_QMARK_L,            
    /*  LANG_IT  */  I_WITH_GRAVE_SMALL u"\r\v\t" I_WITH_CIRCUMF_SMALL,I_WITH_ACUTE_SMALL u"\r\v\t" I_WITH_CIRCUMF_SMALL,I_WITH_GRAVE u"\r\v\t" I_WITH_CIRCUMF_SMALL,
    /*  LANG_TR  */  u"-" u"\r\v\t|",              u"_" u"\r\v\t|",              u"-" u"\r\v\t|",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_HE,                  NULL,                         NULL,                         
    /*  LANG_AR  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_GR  */  EQUALS u"\r\v\t" ONE_HALF,    u"+" u"\r\v\t" ONE_HALF,      EQUALS u"\r\v\t" ONE_HALF
    },
    /*KC_LBRC    */ {u"[",                         u"{",                         u"[",                         
    /*  LANG_DE  */  UMLAUT_U_SMALL,               UMLAUT_U,                     NULL,                         
    /*  LANG_FR  */  u"^",                         DIAERESIS,                    NULL,                         
    /*  LANG_ES  */  GRAVE_ACCENT u"\r\v\t[",      u"^" u"\r\v\t[",              GRAVE_ACCENT u"\r\v\t[",      
    /*  LANG_PT  */  u"+" u"\r\v\t" DIAERESIS,     u"*" u"\r\v\t" DIAERESIS,     u"+" u"\r\v\t" DIAERESIS,     
    /*  LANG_IT  */  E_WITH_GRAVE_SMALL u"\r\v\t[",E_WITH_ACUTE_SMALL u"\r\v\t[",E_WITH_GRAVE u"\r\v\t[",      
    /*  LANG_TR  */  G_WITH_BREVE_SMALL u"\r\v\tDIAERESIS ",G_WITH_BREVE u"\r\v\tDIAERESIS ",NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  KH_VSOUNDM,                   LCORNER_BRKT,                 NULL,                         
    /*  LANG_AR  */  ARABIC_JEEM,                  u"}",                         ARABIC_JEEM,                  
    /*  LANG_GR  */  u"[" u"\r\v\t" DBL_ANGLE_QMARK_L,u"{" u"\r\v\t" DBL_ANGLE_QMARK_L,u"[" u"\r\v\t" DBL_ANGLE_QMARK_L
    },
    /*KC_RBRC    */ {u"]",                         u"}",                         u"]",                         
    /*  LANG_DE  */  u"+" u"\r\v\t~",              u"*" u"\r\v\t~",              NULL,                         
    /*  LANG_FR  */  u"$" u"\r\v\t" CURRENCY_SIGN, POUND_SIGN u"\r\v\t" CURRENCY_SIGN,NULL,                         
    /*  LANG_ES  */  u"+" u"\r\v\t]",              u"*" u"\r\v\t]",              u"+" u"\r\v\t]",              
    /*  LANG_PT  */  ACUTE_ACCENT u"\r\v\t]",      GRAVE_ACCENT u"\r\v\t]",      ACUTE_ACCENT u"\r\v\t]",      
    /*  LANG_IT  */  u"+" u"\r\v\t]",              u"*" u"\r\v\t]",              u"+" u"\r\v\t]",              
    /*  LANG_TR  */  UMLAUT_U_SMALL u"\r\v\t~",    UMLAUT_U u"\r\v\t~",          NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  KH_SEMI_VSOUNDM,              RCORNER_BRKT,                 NULL,                         
    /*  LANG_AR  */  ARABIC_DAL,                   u"{",                         ARABIC_DAL,                   
    /*  LANG_GR  */  u"]" u"\r\v\t" DBL_ANGLE_QMARK_R,u"}" u"\r\v\t" DBL_ANGLE_QMARK_R,u"]" u"\r\v\t" DBL_ANGLE_QMARK_R
    },
    /*KC_BACKSLASH*/ {BACKSLASH,                    u"|",                         BACKSLASH,                    
    /*  LANG_DE  */  u"#",                         u"'",                         NULL,                         
    /*  LANG_FR  */  u"*",                         MICRO_SIGN,                   NULL,                         
    /*  LANG_ES  */  C_WITH_CEDILLA_SMALL u"\r\v\t}",C_WITH_CEDILLA u"\r\v\t}",    NULL,                         
    /*  LANG_PT  */  u"~",                         u"^",                         u"~",                         
    /*  LANG_IT  */  U_WITH_GRAVE_SMALL u"\r\v\t" SECTION,U_WITH_ACUTE_SMALL u"\r\v\t" SECTION,U_WITH_GRAVE u"\r\v\t" SECTION,
    /*  LANG_TR  */  u"," u"\r\v\t" GRAVE_ACCENT,  u";" u"\r\v\t" GRAVE_ACCENT,  NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_MU,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_THAL,                  u"\v" ARABIC_SHADDA,          ARABIC_THAL,                  
    /*  LANG_GR  */  BACKSLASH u"\r\v\t" NOT_SIGN, u"|" u"\r\v\t" NOT_SIGN,      BACKSLASH u"\r\v\t" NOT_SIGN
    },
    /*KC_NONUS_HASH*/ {u"#",                         u"~",                         u"#",                         
    /*  LANG_DE  */  u"<" u"\r\v\t|",              u">" u"\r\v\t|",              NULL,                         
    /*  LANG_FR  */  u"<",                         u">",                         NULL,                         
    /*  LANG_ES  */  u"<",                         u">",                         u"<",                         
    /*  LANG_PT  */  u"<",                         u">",                         u"<",                         
    /*  LANG_IT  */  u"<",                         u">",                         u"<",                         
    /*  LANG_TR  */  u"<" u"\r\v\t|",              u">" u"\r\v\t|",              u"<" u"\r\v\t|",              
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_AR  */  BACKSLASH,                    u"|",                         BACKSLASH,                    
    /*  LANG_GR  */  u">",                         u"<",                         u">"
    },
    /*KC_SEMICOLON*/ {u";",                         u":",                         u";",                         
    /*  LANG_DE  */  UMLAUT_O_SMALL,               UMLAUT_O,                     NULL,                         
    /*  LANG_FR  */  u"m",                         u"M",                         NULL,                         
    /*  LANG_ES  */  N_WITH_TILDE_SMALL,           N_WITH_TILDE,                 NULL,                         
    /*  LANG_PT  */  C_WITH_CEDILLA_SMALL,         C_WITH_CEDILLA,               NULL,                         
    /*  LANG_IT  */  O_WITH_GRAVE_SMALL u"\r\v\t@",C_WITH_CEDILLA_SMALL u"\r\v\t@",O_WITH_GRAVE u"\r\v\t@",      
    /*  LANG_TR  */  S_WITH_CEDILLA_SMALL u"\r\v\t" ACUTE_ACCENT,S_WITH_CEDILLA u"\r\v\t" ACUTE_ACCENT,NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_RE,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_KAF,                   u":",                         ARABIC_KAF,                   
    /*  LANG_GR  */  GREEK_TONOS u"\r\v\t" GREEK_DIALYTIKA_TONOS,GREEK_DIALYTIKA u"\r\v\t" GREEK_DIALYTIKA_TONOS,GREEK_TONOS u"\r\v\t" GREEK_DIALYTIKA_TONOS
    },
    /*KC_QUOTE   */ {u"'",                         QUOTE,                        u"'",                         
    /*  LANG_DE  */  UMLAUT_A_SMALL,               UMLAUT_A,                     NULL,                         
    /*  LANG_FR  */  U_WITH_GRAVE,                 u"%",                         NULL,                         
    /*  LANG_ES  */  ACUTE_ACCENT u"\r\v\t{",      DIAERESIS u"\r\v\t{",         ACUTE_ACCENT u"\r\v\t{",      
    /*  LANG_PT  */  MASC_ORDINAL_IND,             FEM_ORDINAL_IND,              MASC_ORDINAL_IND,             
    /*  LANG_IT  */  A_WITH_GRAVE_SMALL u"\r\v\t#",O_WITH_ACUTE_SMALL u"\r\v\t#",A_WITH_GRAVE u"\r\v\t#",      
    /*  LANG_TR  */  u"i",                         I_WITH_DOT,                   NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_KE,                  NULL,                         NULL,                         
    /*  LANG_AR  */  ARABIC_TAH,                   QUOTE,                        ARABIC_TAH,                   
    /*  LANG_GR  */  u"'",                         QUOTE,                        u"'"
    },
    /*KC_GRAVE   */ {GRAVE_ACCENT,                 u"~",                         GRAVE_ACCENT,                 
    /*  LANG_DE  */  u"^",                         DEGREE,                       u"^",                         
    /*  LANG_FR  */  u"\v\xb2",                    SPACE,                        u"\v\xb2",                    
    /*  LANG_ES  */  MASC_ORDINAL_IND u"\r\v\t" BACKSLASH,FEM_ORDINAL_IND u"\r\v\t" BACKSLASH,MASC_ORDINAL_IND u"\r\v\t" BACKSLASH,
    /*  LANG_PT  */  BACKSLASH,                    u"|",                         BACKSLASH,                    
    /*  LANG_IT  */  BACKSLASH,                    u"|",                         BACKSLASH,                    
    /*  LANG_TR  */  QUOTE u"\r\v\t<",             E_WITH_ACUTE u"\r\v\t<",      NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_RO,                  NULL,                         NULL,                         
    /*  LANG_AR  */  u">",                         u"<",                         u">",                         
    /*  LANG_GR  */  GRAVE_ACCENT,                 u"~",                         GRAVE_ACCENT
    },
    /*KC_COMMA   */ {COMMA,                        u"<",                         COMMA,                        
    /*  LANG_DE  */  NULL,                         u";",                         NULL,                         
    /*  LANG_FR  */  u";",                         u".",                         NULL,                         
    /*  LANG_ES  */  u",",                         u";",                         u",",                         
    /*  LANG_PT  */  u",",                         u";",                         u",",                         
    /*  LANG_IT  */  u"," u"\r\v\t" DBL_ANGLE_QMARK_L,u";" u"\r\v\t" DBL_ANGLE_QMARK_L,u"," u"\r\v\t" DBL_ANGLE_QMARK_L,
    /*  LANG_TR  */  UMLAUT_O_SMALL,               UMLAUT_O,                     NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_NE,                  CJK_IDEOG_COMMA,              NULL,                         
    /*  LANG_AR  */  ARABIC_WAW,                   COMMA,                        ARABIC_WAW,                   
    /*  LANG_GR  */  COMMA,                        u"<",                         COMMA
    },
    /*KC_DOT     */ {u".",                         u">",                         u".",                         
    /*  LANG_DE  */  NULL,                         u":",                         NULL,                         
    /*  LANG_FR  */  u":",                         u"/",                         NULL,                         
    /*  LANG_ES  */  u".",                         u":",                         u".",                         
    /*  LANG_PT  */  u".",                         u":",                         u".",                         
    /*  LANG_IT  */  u"." u"\r\v\t" DBL_ANGLE_QMARK_R,u":" u"\r\v\t" DBL_ANGLE_QMARK_R,u"." u"\r\v\t" DBL_ANGLE_QMARK_R,
    /*  LANG_TR  */  C_WITH_CEDILLA_SMALL,         C_WITH_CEDILLA,               NULL,                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_RU,                  CJK_IDEOG_FSTOP,              NULL,                         
    /*  LANG_AR  */  ARABIC_ZAIN,                  u".",                         ARABIC_ZAIN,                  
    /*  LANG_GR  */  u".",                         u">",                         u"."
    },
    /*KC_SLASH   */ {u"/",                         u"?",                         u"/",                         
    /*  LANG_DE  */  u"-",                         u"_",                         u"-",                         
    /*  LANG_FR  */  u"!",                         SECTION,                      NULL,                         
    /*  LANG_ES  */  u"-",                         u"_",                         u"-",                         
    /*  LANG_PT  */  u"-",                         u"_",                         u"-",                         
    /*  LANG_IT  */  u"-" u"\r\v\t" DEGREE,        u"_" u"\r\v\t" DEGREE,        u"-" u"\r\v\t" DEGREE,        
    /*  LANG_TR  */  u".",                         u":",                         u".",                         
    /*  LANG_KO  */  NULL,                         NULL,                         NULL,                         
    /*  LANG_JA  */  HIRAGANA_ME,                  KATAKANA_MIDDLE_DOT,          NULL,                         
    /*  LANG_AR  */  ARABIC_ZAH,                   ARABIC_QMARK,                 ARABIC_ZAH,                   
    /*  LANG_GR  */  u"/",                         u"?",                         u"/"
    },
    //[[[end]]]
};

const uint16_t* translate_keycode(uint8_t used_lang, uint16_t keycode, bool shift, bool caps_lock) {
    if(keycode < KC_A || keycode > KC_SLASH) return NULL;

    uint16_t index = keycode - KC_A;

    const uint16_t* lower_case = lang_plane[index][used_lang*3];
    if(lower_case==NULL) {
        lower_case = lang_plane[index][0]; //english as backup
        used_lang = 0;
    }

    if(caps_lock) {
        const uint16_t* caps_case = lang_plane[index][used_lang*3 + 2];
        if(caps_case!=NULL) {
            if(!shift) {
                return caps_case;
            }
        } else {
           shift = !shift;
        }
    }

    if(shift) {
        const uint16_t* upper_case = lang_plane[index][used_lang*3 + 1];
        if(upper_case!=NULL) {
            return upper_case;
        }
    }
    return lower_case;
}
