#pragma once

#include "quantum.h"

/**************************************************
** Include headers specific to keyboard revision **
***************************************************/
#ifdef KEYBOARD_preonic_rev1
  #include "rev1.h"
#endif

#ifdef KEYBOARD_preonic_rev2
  #include "rev2.h"
#endif

#ifdef KEYBOARD_preonic_rev3
  #include "rev3.h"
#endif


/**************************************************
** Layout macros aliases common to all revisions **

        Name of Alias      Matrix Name:
        -----------------  ------------------- ****/
#define LAYOUT_ortho_5x12  LAYOUT_preonic_grid
