#ifndef KUATSURE
#define KUATSURE

#include "quantum.h"

void tmux_prefix(void);
void tmux_pane_zoom(void);
void tmux_pane_switch(uint16_t keycode);
void tmux_window_switch(uint16_t keycode);

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 300

#endif
