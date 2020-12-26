#ifndef EIGHTY_H
#define EIGHTY_H

#include "quantum.h"

#if defined(KEYBOARD_mode_eighty_M80H)
  #include "M80H.h"
#elif defined(KEYBOARD_mode_eighty_M80S)
  #include "M80S.h"
#endif // Mode80 solderable "S" and hotswap "H" revisions

#endif
