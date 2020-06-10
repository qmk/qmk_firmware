// tapdances.cpp

void tapmod(qk_tap_dance_state_t *state, int taps, uint16_t keycode_tapped, uint16_t keycode_held)
{
  if (state->count >= taps) {
    if (state->pressed) {
      register_code(keycode_held);
    }
    else {
      set_oneshot_mods(keycode_tapped);
    } 
    reset_tap_dance(state);
  }
}

void test(qk_tap_dance_state_t *state, void *user_data)
{
  tapmod(state, 2, KC_CAPS,  KC_LSFT);
  tapmod(state, 1, MOD_LSFT, KC_LSFT);
  reset_tap_dance(state);
}

void caps(qk_tap_dance_state_t *state, void *user_data) // Shift, Caps
{ if (state->count >= 2) {register_code(KC_CAPS); unregister_code(KC_CAPS);}
  else if (state->pressed) {register_code(KC_LSFT);} else {set_oneshot_mods(MOD_LSFT);}
  reset_tap_dance(state);
}

void forward_back_mac(qk_tap_dance_state_t *state, void *user_data) // G<-, then G->
{
  if (state->count > 1) {
    register_code(KC_LGUI);
    register_code(KC_RIGHT);
    unregister_code(KC_RIGHT);
    unregister_code(KC_LGUI);
  }
  else {
    register_code(KC_LGUI);
    register_code(KC_LEFT);
    unregister_code(KC_LEFT);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

void shiftgui(qk_tap_dance_state_t *state, void *user_data) // G->SG
{
  if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LSFT);
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LSFT | MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_code(KC_LGUI);
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
      register_code(KC_LCTL);
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_code(KC_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI);
  }
  reset_tap_dance(state);
}

void deleter(qk_tap_dance_state_t *state, void *user_data) // bkspc -> delwrd -> delline
{
  if (state->count > 3) {
    register_code(KC_LGUI);
    register_code(KC_BSPACE);
    unregister_code(KC_BSPACE);
    unregister_code(KC_LGUI);
  }
  else if (state->count > 2) {
    register_code(KC_LALT);
    register_code(KC_BSPACE);
    unregister_code(KC_BSPACE);
    unregister_code(KC_LALT);
  }
  else if (state->count > 1) {
    register_code(KC_BSPACE);
    unregister_code(KC_BSPACE);
    register_code(KC_BSPACE);
    unregister_code(KC_BSPACE);
  }
  else {
    register_code(KC_BSPACE);
    unregister_code(KC_BSPACE);
  }
  reset_tap_dance(state);
}

void ubermod(qk_tap_dance_state_t *state, void *user_data) // CTL->ALT->GUI
{
  if (state->count > 2) {
    if (state->pressed) { 
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LCTL);
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
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LGUI);
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
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LALT);
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
      register_code(KC_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LCTL);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI);
    }
  }
  else if (state->pressed) { 
    register_code(KC_LALT);
  }
  else {
    set_oneshot_mods(MOD_LALT);
  }
  reset_tap_dance(state);
}

void shift_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LSFT);
  // clear_oneshot_mods();
}
void gui_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LGUI);
  unregister_code(KC_LSFT);
} 
void CAS_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LSFT);
  unregister_code(KC_LCTL);
  unregister_code(KC_LALT);
}
void CASG_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LSFT);
  unregister_code(KC_LCTL);
  unregister_code(KC_LALT);
  unregister_code(KC_LGUI);  
  // clear_oneshot_mods();
}
void ubermod_reset(qk_tap_dance_state_t *state, void *user_data) // AKA CAG_reset
{
  unregister_code(KC_LGUI);
  unregister_code(KC_LCTL);
  unregister_code(KC_LALT);
}

void shiftenter(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    register_code  (KC_ENT);
    unregister_code(KC_ENT);
  }
  else if (state->pressed) { 
    register_code(KC_LSFT);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

void shiftentercaps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    register_code  (KC_CAPS);
    unregister_code(KC_CAPS);
  }
  else if (state->count > 1) {
    register_code  (KC_ENT);
    unregister_code(KC_ENT);
  }
  else if (state->pressed) { 
    register_code(KC_LSFT);
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
      register_code(KC_LCTL);
      register_code(KC_LGUI);
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI | MOD_LALT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LCTL);
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LGUI); 
    }
  }
  else if (state->pressed) { 
    register_code(KC_LCTL);
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
      register_code(KC_LCTL);
      register_code(KC_LSFT);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LSFT);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LCTL);
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LCTL | MOD_LALT);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LCTL);
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
      register_code(KC_LALT);
      register_code(KC_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LCTL);
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LSFT);
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LALT);
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
      register_code(KC_LSFT);
      register_code(KC_LGUI);
    }
    else {
      set_oneshot_mods(MOD_LGUI | MOD_LSFT);      
    }
  }
  else if (state->count > 1) {
    if (state->pressed) { 
      register_code(KC_LSFT);
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT);      
    }
  }
  else if (state->pressed) { 
    register_code(KC_LSFT);
    register_code(KC_LCTL);
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
      register_code(KC_LSFT);
      register_code(KC_LALT);
    }
    else {
      set_oneshot_mods(MOD_LALT | MOD_LSFT); 
    }
  } 
  else if (state->count > 2) {
    if (state->pressed) { 
      register_code(KC_LSFT);
      register_code(KC_LCTL);
    }
    else {
      set_oneshot_mods(MOD_LSFT | MOD_LCTL);
    }
  }
  else if (state->pressed) { 
    register_code(KC_LSFT);
    register_code(KC_LGUI);
  }
  else {
    set_oneshot_mods(MOD_LGUI | MOD_LSFT);      
  }
  reset_tap_dance(state);
}



// void adjust_td_1_2(qk_tap_dance_state_t *state, void *user_data)
// {
//   // if statement to set layer variables depending on currently-active layer
//   // if default active, l1 = Excel, l2 = Edit. 
//   // if Excel active, l1 = Edit, l2 = defualt.
//   // if Edit active, l1 = default, l2 = Excel. 
//   switch (state->count) {

//     case 1:

//     break;
    
//     case 2: 

//     break;
//   }
// }

// void gui_all(qk_tap_dance_state_t *state, void *user_data)
// {
//   if (state->count > 3) {
//     if (state->pressed) { 
//       register_code(KC_LGUI);
//       register_code(KC_LALT);
//     }
//     else {
//       set_oneshot_mods(MOD_LGUI | MOD_LALT);
//     }
//   }
//   else if (state->count > 2) {
//     if (state->pressed) { 
//       register_code(KC_LGUI);
//       register_code(KC_LCTL);
//     }
//     else {
//       set_oneshot_mods(MOD_LGUI | MOD_LCTL);
//     }
//   }
//   else if (state->count > 1) {
//     if (state->pressed) { 
//       register_code(KC_LSFT);
//       register_code(KC_LGUI);
//     }
//     else {
//       set_oneshot_mods(MOD_LSFT | MOD_LGUI);
//     }
//   }
//   else if (state->pressed) { 
//     register_code(KC_LGUI);
//   }
//   else {
//     set_oneshot_mods(MOD_LGUI);
//   }
//   reset_tap_dance(state);
// }
