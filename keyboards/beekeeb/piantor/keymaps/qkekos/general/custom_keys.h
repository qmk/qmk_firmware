
#pragma once
#include "../__init__.h"

enum blender_keycode {
    US_3ARR = SAFE_RANGE,
    US_3ARL,
    US_3ARU,
    US_3ARD,
    US_LGTG,
    US_QTLY,
    US_SLSR,
    US_CLER,
    US_CWRD,
    US_FNCE,
    US_SNKE,
    US_CAML,
    US_MGTR,
    US_HRTR,
    US_RFSH,
    US_DPAS,
    US_SPAS,
    US_DPRP,
    US_NPRP,

    WN_STEM,
    WN_DIS,
    WN_DISB,
    WN_CHRM,
    WN_TELG,
    WN_WSL,
    WN_TBX,
    WN_PYCH,

    US_AREP,
    US_REP,
};

int custom_keys_pr(uint16_t, keyrecord_t*);
