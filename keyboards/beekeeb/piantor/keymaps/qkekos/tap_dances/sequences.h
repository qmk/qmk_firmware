
#pragma once
#include "../__init__.h"

void pass_td(tap_dance_state_t *state, void *user_data);
void exlm_td(tap_dance_state_t *state, void *user_data);
void eql_td(tap_dance_state_t *state, void *user_data);
void dqt_td(tap_dance_state_t *state, void *user_data);
void bsls_td(tap_dance_state_t *state, void *user_data);
void unds_td(tap_dance_state_t *state, void *user_data);
void coln_td(tap_dance_state_t *state, void *user_data);
void arr_td(tap_dance_state_t *state, void *user_data);
void eclp_td(tap_dance_state_t *state, void *user_data);
void sall_td(tap_dance_state_t *state, void *user_data);
void md_td(tap_dance_state_t *state, void *user_data);

void quote_line(const char *string);
void select_line(void);
void cut_line(void);
void copy_line(void);
void delete_line(void);

#define triple_sequence_td(t_cs, t_s, t_c, t, d_cs, d_s, d_c, d, s_cs, s_s, s_c, s) \
    if (state->count % 3 == 0) { \
        if (is_shift_held() && is_ctrl_held()) { \
            { t_cs; } \
        } else if (is_shift_held()) { \
            { t_s; } \
        } else if (is_ctrl_held()) { \
            { t_c; } \
        } else { \
            { t; } \
        } \
    } else if (state->count % 3 == 2) { \
        if (is_shift_held() && is_ctrl_held()) { \
            { d_cs; } \
        } else if (is_shift_held()) { \
            { d_s; } \
        } else if (is_ctrl_held()) { \
            { d_c; } \
        } else { \
            { d; } \
        } \
    } else { \
        if (is_shift_held() && is_ctrl_held()) { \
            { s_cs; } \
        } else if (is_shift_held()) { \
            { s_s; } \
        } else if (is_ctrl_held()) { \
            { s_c; } \
        } else { \
            { s; } \
        } \
    }

#define double_sequence_td(d_cs, d_s, d_c, d, s_cs, s_s, s_c, s) \
    if (state->count % 2 == 0) { \
        if (is_shift_held() && is_ctrl_held()) { \
            { d_cs; } \
        } else if (is_shift_held()) { \
            { d_s; } \
        } else if (is_ctrl_held()) { \
            { d_c; } \
        } else { \
            { d; } \
        } \
    } else { \
        if (is_shift_held() && is_ctrl_held()) { \
            { s_cs; } \
        } else if (is_shift_held()) { \
            { s_s; } \
        } else if (is_ctrl_held()) { \
            { s_c; } \
        } else { \
            { s; } \
        } \
    }

#define sequence_td(s_cs, s_s, s_c, s) \
    if (is_shift_held() && is_ctrl_held()) { \
        { s_cs; } \
    } else if (is_shift_held()) { \
        { s_s; } \
    } else if (is_ctrl_held()) { \
        { s_c; } \
    } else { \
        { s; } \
    }
