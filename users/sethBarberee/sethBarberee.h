#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#ifdef TAP_DANCE_ENABLE // only enable for tap dances
    enum {
        TD_ECAP = 0,
    };

    #define KC_ECAP TD(TD_ECAP)

    typedef struct {
        bool toggled; // store whether we have toggled caps lock
        int toggle_mode; // idk why but maybe do something with this..
        int normal_mode;
    } tap;
#endif

#endif
