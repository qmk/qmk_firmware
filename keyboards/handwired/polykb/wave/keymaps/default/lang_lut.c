#include "lang_lut.h"
#include "polyatom.h"
#include "../../../fonts/gfx_used_symbols.h"

static const uint16_t* lang_plane [ALPHA + NUM + ADDITIONAL][NUM_LANG * 3] = {
    //           [  E N G L I S H - U S  ]          [          K O R E A N              ]      [          J A P A N E S E             ]          [               A R A B I C              ]
    //            glyph     shift   caps            glyph           shift           caps         glyph           shift           caps            glyph              shift          caps
    /* KC_A */   {u"a",     u"A",   NULL,           HANGEUL_MIEUM,  NULL,               NULL,   HIRAGANA_TI,    NULL,               NULL,       ARABIC_SHEEN,       NULL,           NULL},
    /* KC_B */   {u"b",     u"B",   NULL,           HANGEUL_YU,     NULL,               NULL,   HIRAGANA_KO,    NULL,               NULL,       ARABIC_LAM_ALEF,    ARABIC_LAM_ALEF_MADDA,NULL},
    /* KC_C */   {u"c",     u"C",   NULL,           HANGEUL_CHIEUCH,NULL,               NULL,   HIRAGANA_SO,    NULL,               NULL,       ARABIC_WAW_HAMZA_A, NULL,           NULL},
    /* KC_D */   {u"d",     u"D",   NULL,           HANGEUL_IEUNG,  NULL,               NULL,   HIRAGANA_SI,    NULL,               NULL,       ARABIC_YEH,         NULL,           NULL},
    /* KC_E */   {u"e",     u"E",   NULL,           HANGEUL_TIKEUT, HANGEUL_SSANGTIKEUT,NULL,   HIRAGANA_I,     HIRAGANA_SMALL_I,   NULL,       ARABIC_THEH,        NULL,           NULL},
    /* KC_F */   {u"f",     u"F",   NULL,           HANGEUL_RIEUL,  NULL,               NULL,   HIRAGANA_HA,    NULL,               NULL,       ARABIC_BEH,         NULL,           NULL},
    /* KC_G */   {u"g",     u"G",   NULL,           HANGEUL_HIEUH,  NULL,               NULL,   HIRAGANA_KI,    NULL,               NULL,       ARABIC_LAM,         NULL,           NULL},
    /* KC_H */   {u"h",     u"H",   NULL,           HANGEUL_O,      NULL,               NULL,   HIRAGANA_KU,    NULL,               NULL,       ARABIC_ALEF,        NULL,           NULL},
    /* KC_I */   {u"i",     u"I",   NULL,           HANGEUL_YA,     NULL,               NULL,   HIRAGANA_RI,    NULL,               NULL,       ARABIC_HEH,         NULL,           NULL},
    /* KC_J */   {u"j",     u"J",   NULL,           HANGEUL_EO,     NULL,               NULL,   HIRAGANA_MA,    NULL,               NULL,       ARABIC_TEH,         NULL,           NULL},
    /* KC_K */   {u"k",     u"K",   NULL,           HANGEUL_A,      NULL,               NULL,   HIRAGANA_NO,    NULL,               NULL,       ARABIC_NOON,        NULL,           NULL},
    /* KC_L */   {u"l",     u"L",   NULL,           HANGEUL_I,      NULL,               NULL,   HIRAGANA_RI,    NULL,               NULL,       ARABIC_MEEM,        NULL,           NULL},
    /* KC_M */   {u"m",     u"M",   NULL,           HANGEUL_EU,     NULL,               NULL,   HIRAGANA_MO,    NULL,               NULL,       ARABIC_WAW,         u",",           NULL},
    /* KC_N */   {u"n",     u"N",   NULL,           HANGEUL_U,      NULL,               NULL,   HIRAGANA_MI,    NULL,               NULL,       ARABIC_ALEF_MAKSURA,NULL,           NULL},
    /* KC_O */   {u"o",     u"O",   NULL,           HANGEUL_AE,     HANGEUL_YAE,        NULL,   HIRAGANA_RA,    NULL,               NULL,       ARABIC_TEH_MARBUTA, NULL,           NULL},
    /* KC_P */   {u"p",     u"P",   NULL,           HANGEUL_E,      HANGEUL_YE,         NULL,   HIRAGANA_SE,    NULL,               NULL,       ARABIC_HAH,         NULL,           NULL},
    /* KC_Q */   {u"q",     u"Q",   NULL,           HANGEUL_PIEUP,  HANGEUL_SSANGPIEUP, NULL,   HIRAGANA_TA,    NULL,               NULL,       ARABIC_DAD,         NULL,           NULL},
    /* KC_R */   {u"r",     u"R",   NULL,           HANGEUL_KIYEOK, HANGEUL_SSANGKIYEOK,NULL,   HIRAGANA_SU,    NULL,               NULL,       ARABIC_QAF,         NULL,           NULL},
    /* KC_S */   {u"s",     u"S",   NULL,           HANGEUL_NIEUN,  NULL,               NULL,   HIRAGANA_TO,    NULL,               NULL,       ARABIC_SEEN,        NULL,           NULL},
    /* KC_T */   {u"t",     u"T",   NULL,           HANGEUL_SIOS,   HANGEUL_SSANGSIOS,  NULL,   HIRAGANA_KA,    NULL,               NULL,       ARABIC_FEH,         NULL,           NULL},
    /* KC_U */   {u"u",     u"U",   NULL,           HANGEUL_YEO,    NULL,               NULL,   HIRAGANA_NA,    NULL,               NULL,       ARABIC_AIN,         NULL,           NULL},
    /* KC_V */   {u"v",     u"V",   NULL,           HANGEUL_PHIEUPH,NULL,               NULL,   HIRAGANA_HI,    NULL,               NULL,       ARABIC_REH,         NULL,           NULL},
    /* KC_W */   {u"w",     u"W",   NULL,           HANGEUL_CIEUC,  HANGEUL_SSANGCIEUC, NULL,   HIRAGANA_TE,    NULL,               NULL,       ARABIC_SAD,         NULL,           NULL},
    /* KC_X */   {u"x",     u"X",   NULL,           HANGEUL_THIEUTH,NULL,               NULL,   HIRAGANA_SA,    NULL,               NULL,       ARABIC_HAMZA,       NULL,           NULL},
    /* KC_Y */   {u"y",     u"Y",   NULL,           HANGEUL_YO,     NULL,               NULL,   HIRAGANA_N,     NULL,               NULL,       ARABIC_GHAIN,       NULL,           NULL},
    /* KC_Z */   {u"z",     u"Z",   NULL,           HANGEUL_KHIEUKH,NULL,               NULL,   HIRAGANA_TU,    HIRAGANA_SMALL_TU,  NULL,       ARABIC_YEH_HAMZA_A, NULL,           NULL},
    /* KC_1 */   {u"1",     u"!",   u"1",           NULL,           NULL,               NULL,   HIRAGANA_NU,    NULL,               NULL,       ARABIC_INDIC_1,     u"!",           ARABIC_INDIC_1},
    /* KC_2 */   {u"2",     u"@",   u"2",           NULL,           NULL,               NULL,   HIRAGANA_HU,    NULL,               NULL,       ARABIC_INDIC_2,     u"@",           ARABIC_INDIC_2},
    /* KC_3 */   {u"3",     u"#",   u"3",           NULL,           NULL,               NULL,   HIRAGANA_A,     HIRAGANA_SMALL_A,   NULL,       ARABIC_INDIC_3,     u"#",           ARABIC_INDIC_3},
    /* KC_4 */   {u"4",     u"$",   u"4",           NULL,           NULL,               NULL,   HIRAGANA_U,     HIRAGANA_SMALL_U,   NULL,       ARABIC_INDIC_4,     u"$",           ARABIC_INDIC_4},
    /* KC_5 */   {u"5",     u"%",   u"5",           NULL,           NULL,               NULL,   HIRAGANA_E,     HIRAGANA_SMALL_E,   NULL,       ARABIC_INDIC_5,     u"%",           ARABIC_INDIC_5},
    /* KC_6 */   {u"6",     u"^",   u"6",           NULL,           NULL,               NULL,   HIRAGANA_O,     HIRAGANA_SMALL_O,   NULL,       ARABIC_INDIC_6,     u"^",           ARABIC_INDIC_6},
    /* KC_7 */   {u"7",     u"&",   u"7",           NULL,           NULL,               NULL,   HIRAGANA_YA,    HIRAGANA_SMALL_YA,  NULL,       ARABIC_INDIC_7,     u"&",           ARABIC_INDIC_7},
    /* KC_8 */   {u"8",     u"*",   u"8",           NULL,           NULL,               NULL,   HIRAGANA_YU,    HIRAGANA_SMALL_YU,  NULL,       ARABIC_INDIC_8,     u"*",           ARABIC_INDIC_8},
    /* KC_9 */   {u"9",     u"(",   u"9",           NULL,           NULL,               NULL,   HIRAGANA_YO,    HIRAGANA_SMALL_YO,  NULL,       ARABIC_INDIC_9,     u"(",           ARABIC_INDIC_9},
    /* KC_0 */   {u"0",     u")",   u"0",           NULL,           NULL,               NULL,   HIRAGANA_WA,    HIRAGANA_WO,        NULL,       ARABIC_INDIC_0,     u")",           ARABIC_INDIC_0},
/*KC_ENTER     */{u"Ent",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL,               NULL,           NULL},  
/*KC_ESCAPE    */{u"Esc",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL,               NULL,           NULL}, 
/*KC_BACKSPACE */{ICON_BACKSPACE,NULL,NULL,         NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL,               NULL,           NULL}, 
/*KC_TAB       */{u"Tab",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL,               NULL,           NULL}, 
/*KC_SPACE     */{ICON_SPACE,NULL,  NULL,           NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL,               NULL,           NULL},  
/*KC_MINUS     */{u"-",     u"_",   u"-",           NULL,           NULL,               NULL,   HIRAGANA_HO,    KH_PSOUNDM,         NULL,       NULL,               NULL,           NULL}, 
/*KC_EQUAL     */{u"=",     u"+",   u"=",           NULL,           NULL,               NULL,   HIRAGANA_HE,    NULL,               NULL,       NULL,               NULL,           NULL},  
/*KC_LBRC      */{u"[",     u"{",   u"[",           NULL,           NULL,               NULL,   KH_VSOUNDM,     LCORNER_BRKT,       NULL,       ARABIC_JEEM,        u"<",           NULL}, 
/*KC_RBRC      */{u"]",     u"}",   u"]",           NULL,           NULL,               NULL,   KH_SEMI_VSOUNDM,RCORNER_BRKT,       NULL,       ARABIC_DAL,         u">",           NULL}, 
/*KC_BACKSLASH */{u"\\",    u"|",   u"\\",          NULL,           NULL,               NULL,   HIRAGANA_MU,    NULL,               NULL,       NULL,               NULL,           NULL},
/*KC_NONUS_HASH*/{u"#",     u"~",   u"#",           NULL,           NULL,               NULL,   NULL,           NULL,               NULL,       NULL/*semi*/,       NULL,           NULL}, 
/*KC_SEMICOLON */{u";",     u":",   u";",           NULL,           NULL,               NULL,   HIRAGANA_RE,    NULL,               NULL,       ARABIC_KAF,         NULL,           NULL},
/*KC_QUOTE     */{u"'",     u"\"",  u"'",           NULL,           NULL,               NULL,   HIRAGANA_KE,    NULL,               NULL,       ARABIC_TAH,/*fix*/  NULL,           NULL}, 
/*KC_GRAVE     */{u"`",     u"~",   u"`",           NULL,           NULL,               NULL,   HIRAGANA_RO,    NULL,               NULL,       ARABIC_THAL,        NULL,           NULL},
/*KC_COMMA     */{u",",     u"<",   u",",           NULL,           NULL,               NULL,   HIRAGANA_NE,    CJK_IDEOG_COMMA,    NULL,       ARABIC_WAW,         u",",           NULL},
/*KC_DOT       */{u".",     u">",   u".",           NULL,           NULL,               NULL,   HIRAGANA_RU,    CJK_IDEOG_FSTOP,    NULL,       ARABIC_ZAIN,        u".",           NULL},
/*KC_SLASH     */{u"/",     u"?",   u"/",           NULL,           NULL,               NULL,   HIRAGANA_ME,    KATAKANA_MIDDLE_DOT,NULL,       ARABIC_ZAH,         ARABIC_QMARK,   NULL}
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
