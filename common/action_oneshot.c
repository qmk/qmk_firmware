#include "action_oneshot.h"


#ifndef NO_ACTION_ONESHOT
oneshot_state_t oneshot_state;

void oneshot_start(uint8_t mods)
{
    oneshot_state.mods = mods;
}

void oneshot_cancel(void)
{
    oneshot_state.mods = 0;
}

void oneshot_toggle(void)
{
    oneshot_state.disabled = !oneshot_state.disabled;
}
#endif
