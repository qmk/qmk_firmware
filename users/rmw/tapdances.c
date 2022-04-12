// Useful tapdance functions!

#include "tapdances.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    [SHCAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps, shift_reset)
   ,[TDGUI]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftgui, gui_reset)
   ,[TDGUI2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset)
   ,[SHENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftenter, shift_reset)
   ,[SHNTC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftentercaps, shift_reset)
   ,[GCA]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod_mac, ubermod_reset) // GUI->CTL->ALT
   ,[AGC]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod2_mac, ubermod_reset) // ALT->GUI->CTL
   ,[SGCA]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_and_mac, CASG_reset) // SG->SC->SA
   ,[GUCTL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset) 
   ,[CAG]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod, ubermod_reset) // CTL->ALT->GUI
   ,[ACG]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod2, ubermod_reset) // ALT->GUI->CTL
   ,[SCAG]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_and, CASG_reset) // SG->SC->SA
   ,[DLTR]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, deleter, ubermod_reset) // backspace, backspace, alt backspace, gui backspace
   ,[FRBK2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, forward_back_mac, ubermod_reset)
   ,[CTLALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_all_mac, ubermod_reset) // C->CG->CA->CAG
   ,[CTLAND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_all, ubermod_reset) // C->CA->CG->CAG
   ,[FRBK]   = ACTION_TAP_DANCE_DOUBLE(KC_WWW_BACK,KC_WWW_FORWARD)
};

void caps(qk_tap_dance_state_t *state, void *user_data) // Shift, Caps
{ if (state->count >= 2) {register_code(KC_CAPS); unregister_code(KC_CAPS);}
  else if (state->pressed) {register_mods(MOD_LSFT);} else {set_oneshot_mods(MOD_LSFT);}
  reset_tap_dance(state);
}

void forward_back_mac(qk_tap_dance_state_t *state, void *user_data) // G<-, then G->
{
  if (state->count > 1) {
    tap_code16(G(KC_RGHT));
  }
  else {
    tap_code16(G(KC_LEFT));
  }
  reset_tap_dance(state);
}

void shiftgui(qk_tap_dance_state_t *state, void *user_data) // G->SG
{
  if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LSFT | MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LSFT | MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI);
  }
  reset_tap_dance(state);
}

void guictl(qk_tap_dance_state_t *state, void *user_data) // G->GC
{
  if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI);
  }
  reset_tap_dance(state);
}

void deleter(qk_tap_dance_state_t *state, void *user_data) // bkspc -> delwrd -> delline
{
  if (state->count > 3) {
    tap_code16(G(KC_BSPC));
  }
  else if (state->count > 2) {
    tap_code16(A(KC_BSPC));
  }
  else {
    tap_code(KC_BSPC);
  }
  reset_tap_dance(state);
}

void ubermod(qk_tap_dance_state_t *state, void *user_data) // CTL->ALT->GUI
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LCTL);
  }
  else {
    set_oneshot_mods(MOD_LCTL);
  }
  reset_tap_dance(state);
}

void ubermod_mac(qk_tap_dance_state_t *state, void *user_data) // GUI->CTL->ALT
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI);
  }
  reset_tap_dance(state);
}

void ubermod2(qk_tap_dance_state_t *state, void *user_data) // ALT->CTL->GUI
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LALT);
  }
  else {
    set_oneshot_mods(MOD_LALT);
  }
  reset_tap_dance(state);
}

void ubermod2_mac(qk_tap_dance_state_t *state, void *user_data) // ALT->GUI->CTL
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LALT);
  }
  else {
    set_oneshot_mods(MOD_LALT);
  }
  reset_tap_dance(state);
}

void shift_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_mods(MOD_LSFT);
  // clear_oneshot_mods();
}
void gui_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_mods(MOD_LSFT | MOD_LGUI);
} 
void CAS_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_mods(MOD_LCTL | MOD_LSFT | MOD_LALT);
}
void CASG_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_mods(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI);
  // clear_oneshot_mods();
}
void ubermod_reset(qk_tap_dance_state_t *state, void *user_data) // AKA CAG_reset
{
  unregister_mods(MOD_LCTL | MOD_LALT | MOD_LGUI);
}

void shiftenter(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_code(KC_ENT);
  }
  else if (state->pressed) { 
    register_mods(MOD_LSFT);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

void shiftentercaps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    tap_code(KC_CAPS);
  }
  else if (state->count > 1) {
    tap_code(KC_ENT);
  }
  else if (state->pressed) { 
    register_mods(MOD_LSFT);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

void ctrl_all_mac(qk_tap_dance_state_t *state, void *user_data) // C->CG->CAG
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LALT | MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI | MOD_LALT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI); 
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LCTL);
  }
  else {
    set_oneshot_mods(MOD_LCTL);
  }
  reset_tap_dance(state);
}

void ctrl_all(qk_tap_dance_state_t *state, void *user_data) // C->CA->SC
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LSFT);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LSFT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LALT);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LCTL);
  }
  else {
    set_oneshot_mods(MOD_LCTL);
  }
  reset_tap_dance(state);
}

void alt_all(qk_tap_dance_state_t *state, void *user_data) // A->SA->AC
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LCTL);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LSFT | MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LALT);
  }
  else {
    set_oneshot_mods(MOD_LALT);
  }
  reset_tap_dance(state);
}

void shift_and(qk_tap_dance_state_t *state, void *user_data) // SC->SA->SG
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LSFT | MOD_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI | MOD_LSFT);      
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LSFT | MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT);      
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LCTL | MOD_LSFT);
  }
  else {
    set_oneshot_mods(MOD_LSFT | MOD_LCTL);
  }
  reset_tap_dance(state);
}

void shift_and_mac(qk_tap_dance_state_t *state, void *user_data) // SG->SC->SA
{
  if (state->count > 1) {
    if (state->pressed) { 
      register_mods(MOD_LSFT | MOD_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT); 
    }
  } 
  else if (state->count > 2) {
    if (state->pressed) { 
      register_mods(MOD_LCTL | MOD_LSFT);
    }
    else {
      set_oneshot_mods(MOD_LSFT | MOD_LCTL);
    }
  }
  else if (state->pressed) { 
    register_mods(MOD_LSFT | MOD_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI | MOD_LSFT);      
  }
  reset_tap_dance(state);
}
