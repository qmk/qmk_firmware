#pragma once
#include QMK_KEYBOARD_H

// Needs to be active on the OS side as well
// https://docs.qmk.fm/#/feature_unicode?id=input-modes

enum unicode_names {
    aGRV,
    AGRV,
    aUML,
    AUML,
    eGRV,
    EGRV,
    eACT,
    EACT,
    iGRV,
    IGRV,
    iCIR,
    ICIR,
    oGRV,
    OGRV,
    oUML,
    OUML,
    uGRV,
    UGRV,
    uUML,
    UUML,
};

const uint32_t PROGMEM unicode_map[] = {
    // KC_A
    [aGRV]  = 0x00E0, // à
    [AGRV]  = 0x00C0, // À
    [aUML]  = 0x00E4, // ä
    [AUML]  = 0x00C4, // Ä
    // KC_E
    [eGRV]  = 0x00E8, // è
    [EGRV]  = 0x00C8, // È
    [eACT]  = 0x00E9, // é
    [EACT]  = 0x00C9, // É
    // KC_I
    [iGRV]  = 0x00EC, // ì
    [IGRV]  = 0x00CC, // Ì
    [iCIR]  = 0x00EE, // î
    [ICIR]  = 0x00CE, // Î
    // KC_O
    [oGRV]  = 0x00F2, // ò
    [OGRV]  = 0x00D2, // Ò
    [oUML]  = 0x00EF, // ö
    [OUML]  = 0x00D6, // Ö
    // KC_U
    [uGRV]  = 0x00F9, // ù
    [UGRV]  = 0x00D9, // Ù
    [uUML]  = 0x00FC, // ü
    [UUML]  = 0x00DC, // Ü
};

// Accents
#define A_GRV XP(aGRV, AGRV)
#define A_UML XP(aUML, AUML)
#define E_GRV XP(eGRV, EGRV)
#define E_ACT XP(eACT, EACT)
#define I_GRV XP(iGRV, IGRV)
#define I_CIR XP(iCIR, ICIR)
#define O_GRV XP(oGRV, OGRV)
#define O_UML XP(oUML, OUML)
#define U_GRV XP(uGRV, UGRV)
#define U_UML XP(uUML, UUML)
