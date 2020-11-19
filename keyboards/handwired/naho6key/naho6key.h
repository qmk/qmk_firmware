#ifndef NAHO6KEY_H
#define NAHO6KEY_H

#include "quantum.h"

// LEFT:  KL0, KL1, KL2
// RIGHT: KR0, KR1, KR2
#define KEYMAP(KL0, KL1, KL2, KR0, KR1, KR2) \
    {                                        \
        {KL0, KL1, KL2}, { KR0, KR1, KR2 }   \
    }

#endif
