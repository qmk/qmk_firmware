#ifndef PLANCK_H
#define PLANCK_H

#include "quantum.h"

#if defined(KEYBOARD_planck_ez)
  #include "ez.h"
#elif defined(KEYBOARD_planck_light)
  #include "light.h"
#elif defined(KEYBOARD_planck_thk)
  #include "thk.h"
#elif defined(KEYBOARD_planck_rev1)
  #include "rev1.h"
#elif defined(KEYBOARD_planck_rev2)
  #include "rev2.h"
#elif defined(KEYBOARD_planck_rev3)
  #include "rev3.h"
#elif defined(KEYBOARD_planck_rev4)
  #include "rev4.h"
#elif defined(KEYBOARD_planck_rev5)
  #include "rev5.h"
#elif defined(KEYBOARD_planck_rev6)
  #include "rev6.h"
#endif // Planck revisions

#endif
