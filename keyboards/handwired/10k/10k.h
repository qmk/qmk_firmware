#pragma once

#include "quantum.h"

#define LAYOUT_1x5(\
    L00, L01, L02, L03, L04,     R04, R03, R02, R01, R00 \
    )\
    {\
        { L00, L01 , L02, L03, L04 },     \
\
        { R00, R01 , R02, R03, R04 }    \
}
