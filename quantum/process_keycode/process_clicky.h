#ifndef PROCESS_CLICKY_H
#define PROCESS_CLICKY_H

void clicky_play(void);
bool process_clicky(uint16_t keycode, keyrecord_t *record);

void clicky_freq_up(void);
void clicky_freq_down(void);
void clicky_freq_reset(void);
void clicky_freq_toggle(void);
void clicky_freq_on(void);
void clicky_freq_off(void);

bool is_clicky_on(void);

#endif
