#pragma once

#include "bottilabo.h"

#define _STR(X) #X
#define INCLUDEFILE(STR) _STR(STR)
#define _CONCATSTR(X,Y) #X #Y
#define ADDNAME(STR) _CONCATSTR(STR,_NAME)


#ifndef KBD
    #define KBD KBD_HARMONIZE
#endif

#define KBDFILE INCLUDEFILE(KBD)
#include KBDFILE

#include "harmonize.c"

#undef _STR
#undef INCLUDEFILE
#undef _CONCATSTR
#undef ADDNAME
