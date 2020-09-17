#pragma once

#include "quantum.h"

#ifdef KEYBOARD_lfkeyboards_smk65_reva
    #include "reva.h"
#elif KEYBOARD_lfkeyboards_smk65_revb
    #include "revb.h"
#elif KEYBOARD_lfkeyboards_smk65_revf
    #include "revf.h"
#endif
