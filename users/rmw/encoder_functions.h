#pragma once
#include QMK_KEYBOARD_H
#include "rmw.h"

void enc_move_words(bool cw);
void enc_history_scrubbing(bool cw);
void enc_scrolling(bool cw);
void enc_scrolling_h(bool cw);
void enc_volume_knob(bool cw);
void enc_move_desktop(bool cw);
void enc_zoom(bool cw);
