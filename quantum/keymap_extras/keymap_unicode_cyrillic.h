#ifndef KEYMAP_CYRILLIC_H
#define KEYMAP_CYRILLIC_H

#include "keymap.h"

/*
 * This is based off of
 * https://en.wikipedia.org/wiki/Cyrillic_script
 *
 * Unicode is iffy, a software implementation is preferred
 */

// Capital                   Char russian/ukrainian/bulgarian
#define CY_A     UC(0x0410) // А  rus ukr bul
#define CY_BE    UC(0x0411) // Б  rus ukr bul
#define CY_VE    UC(0x0412) // В  rus ukr bul
#define CY_GHE   UC(0x0413) // Г  rus ukr bul
#define CY_GHEUP UC(0x0490) // Ґ      ukr
#define CY_DE    UC(0x0414) // Д  rus ukr bul
#define CY_DJE   UC(0x0402) // Ђ
#define CY_GJE   UC(0x0403) // Ѓ
#define CY_IE    UC(0x0415) // Е  rus ukr bul
#define CY_IO    UC(0x0401) // Ё  rus
#define CY_UIE   UC(0x0404) // Є      ukr
#define CY_ZHE   UC(0x0416) // Ж  rus ukr bul
#define CY_ZE    UC(0x0417) // З  rus ukr bul
#define CY_DZE   UC(0x0405) // Ѕ
#define CY_I     UC(0x0418) // И  rus ukr bul
#define CY_B_U_I UC(0x0406) // І      ukr
#define CY_YI    UC(0x0407) // Ї      ukr
#define CY_SRT_I UC(0x0419) // Й  rus ukr bul
#define CY_JE    UC(0x0408) // Ј
#define CY_KA    UC(0x041a) // К  rus ukr bul
#define CY_EL    UC(0x041b) // Л  rus ukr bul
#define CY_LJE   UC(0x0409) // Љ
#define CY_EM    UC(0x041c) // М  rus ukr bul
#define CY_EN    UC(0x041d) // Н  rus ukr bul
#define CY_NJE   UC(0x040a) // Њ
#define CY_O     UC(0x041e) // О  rus ukr bul
#define CY_PE    UC(0x041f) // П  rus ukr bul
#define CY_ER    UC(0x0420) // Р  rus ukr bul
#define CY_ES    UC(0x0421) // С  rus ukr bul
#define CY_TE    UC(0x0422) // Т  rus ukr bul
#define CY_TSHE  UC(0x040b) // Ћ
#define CY_KJE   UC(0x040c) // Ќ
#define CY_U     UC(0x0423) // У  rus ukr bul
#define CY_SRT_U UC(0x040e) // Ў
#define CY_EF    UC(0x0424) // Ф  rus ukr bul
#define CY_HA    UC(0x0425) // Х  rus     bul
#define CY_TSE   UC(0x0426) // Ц  rus ukr bul
#define CY_CHE   UC(0x0427) // Ч  rus ukr bul
#define CY_DZHE  UC(0x040f) // Џ
#define CY_SHA   UC(0x0428) // Ш  rus ukr bul
#define CY_SHCHA UC(0x0429) // Щ  rus ukr bul
#define CY_HSIGN UC(0x042a) // Ъ  rus     bul
#define CY_YERU  UC(0x042b) // Ы  rus
#define CY_SSIGN UC(0x042c) // Ь  rus ukr bul
#define CY_E     UC(0x042d) // Э  rus
#define CY_YU    UC(0x042e) // Ю  rus ukr bul
#define CY_YA    UC(0x042f) // Я  rus ukr bul
// Important Cyrillic non-Slavic letters
#define CY_PALOCHKA UC(0x04c0) // Ӏ
#define CY_SCHWA UC(0x04d8) // Ә
#define CY_GHE_S UC(0x0492) // Ғ
#define CY_ZE_D  UC(0x0498) // Ҙ
#define CY_ES_D  UC(0x04aa) // Ҫ
#define CY_BR_KA UC(0x04a0) // Ҡ
#define CY_ZHE_D UC(0x0496) // Җ
#define CY_KA_D  UC(0x049a) // Қ
#define CY_EN_D  UC(0x04a2) // Ң
#define CY_ENGHE UC(0x04a4) // Ҥ
#define CY_BRD_O UC(0x04e8) // Ө
#define CY_STR_U UC(0x04ae) // Ү
#define CY_S_U_S UC(0x04b0) // Ұ
#define CY_SHHA  UC(0x04ba) // Һ
#define CY_HA_D  UC(0x04b2) // Ҳ


// Small
#define CY_a     UC(0x0430) // a  rus ukr bul
#define CY_be    UC(0x0431) // б  rus ukr bul
#define CY_ve    UC(0x0432) // в  rus ukr bul
#define CY_ghe   UC(0x0433) // г  rus ukr bul
#define CY_gheup UC(0x0491) // ґ      ukr
#define CY_de    UC(0x0434) // д  rus ukr bul
#define CY_dje   UC(0x0452) // ђ
#define CY_gje   UC(0x0453) // ѓ
#define CY_ie    UC(0x0435) // е  rus ukr bul
#define CY_io    UC(0x0451) // ё  rus
#define CY_uie   UC(0x0454) // є      ukr
#define CY_zhe   UC(0x0436) // ж  rus ukr bul
#define CY_ze    UC(0x0437) // з  rus ukr bul
#define CY_dze   UC(0x0455) // ѕ
#define CY_i     UC(0x0438) // и  rus ukr bul
#define CY_b_u_i UC(0x0456) // і      ukr
#define CY_yi    UC(0x0457) // ї      ukr
#define CY_srt_i UC(0x0439) // й  rus ukr bul
#define CY_je    UC(0x0458) // ј
#define CY_ka    UC(0x043a) // к  rus ukr bul
#define CY_el    UC(0x043b) // л  rus ukr bul
#define CY_lje   UC(0x0459) // љ
#define CY_em    UC(0x043c) // м  rus ukr bul
#define CY_en    UC(0x043d) // н  rus ukr bul
#define CY_nje   UC(0x045a) // њ
#define CY_o     UC(0x043e) // о  rus ukr bul
#define CY_pe    UC(0x043f) // п  rus ukr bul
#define CY_er    UC(0x0440) // р  rus ukr bul
#define CY_es    UC(0x0441) // с  rus ukr bul
#define CY_te    UC(0x0442) // т  rus ukr bul
#define CY_tshe  UC(0x045b) // ћ
#define CY_kje   UC(0x045c) // ќ
#define CY_u     UC(0x0443) // у  rus ukr bul
#define CY_srt_u UC(0x045e) // ў
#define CY_ef    UC(0x0444) // ф  rus ukr bul
#define CY_ha    UC(0x0445) // х  rus ukr bul
#define CY_tse   UC(0x0446) // ц  rus ukr bul
#define CY_che   UC(0x0447) // ч  rus ukr bul
#define CY_dzhe  UC(0x045f) // џ
#define CY_sha   UC(0x0448) // ш  rus ukr bul
#define CY_shcha UC(0x0449) // щ  rus ukr bul
#define CY_hsign UC(0x044a) // ъ  rus     bul
#define CY_yeru  UC(0x044b) // ы  rus
#define CY_ssign UC(0x044c) // ь  rus ukr bul
#define CY_e     UC(0x044d) // э  rus
#define CY_yu    UC(0x044e) // ю  rus ukr bul
#define CY_ya    UC(0x044f) // я  rus ukr bul
// Important Cyrillic non-Slavic letters
#define CY_palochka UC(0x04cf) // ӏ
#define CY_schwa UC(0x04d9) // ә
#define CY_ghe_s UC(0x0493) // ғ
#define CY_ze_d  UC(0x0499) // ҙ
#define CY_es_d  UC(0x04ab) // ҫ
#define CY_br_ka UC(0x04a1) // ҡ
#define CY_zhe_d UC(0x0497) // җ
#define CY_ka_d  UC(0x049b) // қ
#define CY_en_d  UC(0x04a3) // ң
#define CY_enghe UC(0x04a5) // ҥ
#define CY_brd_o UC(0x04e9) // ө
#define CY_str_u UC(0x04af) // ү
#define CY_s_u_s UC(0x04b1) // ұ
#define CY_shha  UC(0x04bb) // һ
#define CY_ha_d  UC(0x04b3) // ҳ


// Extra
#define CY_slr_ve UC(0x1c80) // ᲀ CYRILLIC SMALL LETTER ROUNDED VE
#define CY_ll_de  UC(0x1c81) // ᲁ CYRILLIC SMALL LETTER LONG-LEGGED DE
#define CY_ZEMLYA UC(0xa640) // Ꙁ CYRILLIC CAPITAL LETTER ZEMLYA
#define CY_zemlya UC(0xa641) // ꙁ CYRILLIC SMALL LETTER ZEMLYA
#define CY_RV_DZE UC(0xa644) // Ꙅ CYRILLIC CAPITAL LETTER REVERSED DZE
#define CY_rv_DZE UC(0xa645) // ꙅ CYRILLIC SMALL LETTER REVERSED DZE
#define CY_slw_es UC(0x1c83) // ᲃ CYRILLIC SMALL LETTER WIDE ES
#define CY_st_te  UC(0x1c84) // ᲄ CYRILLIC SMALL LETTER TALL TE
#define CY_3l_te  UC(0x1c85) // ᲅ CYRILLIC SMALL LETTER THREE-LEGGED TE
#define CY_thsign UC(0x1c86) // ᲆ CYRILLIC SMALL LETTER TALL HARD SIGN
#define CY_YERUBY UC(0xa650) // Ꙑ CYRILLIC CAPITAL LETTER YERU WITH BACK YER
#define CY_yeruby UC(0xa651) // ꙑ CYRILLIC SMALL LETTER YERU WITH BACK YER
#define CY_RUBL   UC(0x20bd) // ₽
#define CY_NMRO   UC(0x2116) // №

// The letters Zje and Sje are made for other letters and accent marks

#endif
