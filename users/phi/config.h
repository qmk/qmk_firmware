/* common settings */

/* in ergo42, TAPPING_TERM is defined in rev1/config.h */
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif

#define TAPPING_TERM 180

/* Prefer "hold" when "down -> up -> down" (recognized immediately as "tap twice" by default) */
#define TAPPING_FORCE_HOLD

/* Prefer "hold" when "Alt Dn -> A Dn -> A Up -> Alt Up" within the TAPPING_TERM */
#define PERMISSIVE_HOLD
