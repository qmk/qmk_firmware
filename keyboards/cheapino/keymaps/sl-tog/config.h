#pragma once

// qmk configurator seems to use these shortcuts that are otherwise not defined
// in the old version of qmk used by cheapino's official fork (so uncomment these if
// not rebased/merged master)
//#define OS_LSFT OSM(MOD_LSFT)
//#define OS_LALT OSM(MOD_LALT)
//#define OS_LGUI OSM(MOD_LGUI)
//#define OS_LCTL OSM(MOD_LCTL)
//#define OS_RSFT OSM(MOD_RSFT)
//#define OS_RALT OSM(MOD_RALT)
//#define OS_RGUI OSM(MOD_RGUI)
//#define OS_RCTL OSM(MOD_RCTL)

#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */

