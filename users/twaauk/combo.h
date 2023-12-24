#ifndef COMBO_H
#define COMBO_H
#include "virtualkeys.h"

#if defined(COMBO_ENABLE)
const uint16_t PROGMEM combo_yp_to6[] = {VKC_Y, KC_P, COMBO_END};
const uint16_t PROGMEM combo_hj_mcl[] = {KC_H, VKC_1J, COMBO_END};
const uint16_t PROGMEM combo_jk_lcl[] = {VKC_1J, VKC_AK, COMBO_END};
const uint16_t PROGMEM combo_kl_scr[] = {VKC_AK, VKC_CL, COMBO_END};
const uint16_t PROGMEM combo_let_rcl[] = {VKC_CL, VKC_SET, COMBO_END};
const uint16_t PROGMEM combo_lsp_rcl[] = {VKC_CL, VKC_SSP, COMBO_END};
const uint16_t PROGMEM combo_het_to5[] = {KC_H, VKC_SSP, COMBO_END};
const uint16_t PROGMEM combo_wlr_to0[] = {KC_WH_L, KC_WH_R, COMBO_END};
const uint16_t PROGMEM combo_yi_tominus[] = {VKC_Y, KC_I, COMBO_END};


combo_t key_combos[] = {
	COMBO(combo_yp_to6, TO(6)),
#if VENDOR_ID == 0x5957
#if PRODUCT_ID == 0x200 || PRODUCT_ID == 0x400
	COMBO(combo_hj_mcl, KC_MY_BTN3),
	COMBO(combo_jk_lcl, KC_MY_BTN1),
	COMBO(combo_kl_scr, KC_MY_SCR),
	//COMBO(combo_let_rcl, KC_MY_BTN2),
	COMBO(combo_lsp_rcl, KC_MY_BTN2),
#endif
#endif
	COMBO(combo_het_to5, TO(5)),
	COMBO(combo_wlr_to0, TO(0)),
    COMBO(combo_yi_tominus, KC_MINS),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(combo_t);

#endif
#endif
