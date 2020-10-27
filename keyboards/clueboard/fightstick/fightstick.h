#pragma once

#include "quantum.h"

// Any changes to the layout names and/or definitions must also be made to info.json


#define LAYOUT( \
       K20,   K00, K01, K02, K03, \
    K23, K22, K10, K11, K12, K13, \
       K21 \
) { \
    { K00, K01, K02, K03 }, \
    { K10, K11, K12, K13 }, \
    { K20, K21, K22, K23 } \
}
