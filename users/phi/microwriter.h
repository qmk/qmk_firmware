#include "quantum.h"

enum finger_index {
    MW_PINKY = 0,
    MW_RING,
    MW_MIDDLE,
    MW_INDEX,
    MW_THUMB,
    MW_FUNCTION
};

bool process_microwriter (enum finger_index, keyrecord_t*);
