#pragma once

#include "quantum.h"

#if defined(KEYBOARD_mode_eighty_m80h)
  #include "m80h.h"
#elif defined(KEYBOARD_mode_eighty_m80s)
  #include "m80s.h"
#endif // Mode80 solderable "S" and hotswap "H" revisions
