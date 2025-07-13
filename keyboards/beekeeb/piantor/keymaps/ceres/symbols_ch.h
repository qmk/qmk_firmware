#pragma once

/*
 * symbols_ch.h  —  Swiss-Italian raw keycode enum for QMK
 * --------------------------------------------------------
 * Definizione dei codici esadecimali (raw) per i simboli del
 * layout Swiss-IT (ISO-CH). Questi valori possono essere usati
 * direttamente nei keymap o nelle combo come `SYM_*`.
 *
 * Formato 0xMKKK:
 * - M    = modificatori (Shift=0x2, AltGr=0x14, AltGr+Shift=0x16)
 * - KKK  = HID Usage ID base
 */


	/* 	
	Ricordato che per lo swiss layout esiste l'header file  keymap_swiss_fr.h (pare esista anche la variante keymap_swiss_de.h)  
	che implementa tutti i codici necessare allo swiss layout.
	*/


enum symbol_keycodes {
    SYM_LPAR    = 0x0225,   // (  Shift+8
    SYM_RPAR    = 0x0226,   // )  Shift+9
    SYM_AMP     = 0x0223,   // &  Shift+6
    SYM_BSLASH  = 0x1464,   /* \\  AltGr+< (KC_NUBS=0x64) */
    SYM_PERC    = 0x0222,   // %  Shift+5
    SYM_UNDERSC = 0x0238,   // _  Shift+Minus
    SYM_LCBR    = 0x1434,   // {  AltGr+' (KC_QUOT=0x34)
    SYM_RCBR    = 0x1432,   // }  AltGr+NonUS-# (KC_NUHS=0x32)
    SYM_PIPE    = 0x1424,   // |  AltGr+7
    SYM_DQUOTE  = 0x021F,   // " Shift+2
    SYM_DEGREE  = 0x1235,   // °  AltGr+4
    SYM_LBRC    = 0x142F,   // [  AltGr+Ü (KC_DIAER=0x2F)
    SYM_RBRC    = 0x1430,   // ]  AltGr+¨ (KC_CIRC dead key=0x30)
    SYM_LT      = 0x0064,   // <  KC_NUBS
    SYM_GT      = 0x0264,   // >  Shift+KC_NUBS
    SYM_EQUAL   = 0x1227,   // =  Shift+0
};