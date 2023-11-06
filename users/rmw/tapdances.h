#pragma once
#include "rmw.h"
#include "process_tap_dance.h"
#include "action.h"

void caps(tap_dance_state_t *state, void *user_data); // Shift, Caps
void forward_back_mac(tap_dance_state_t *state, void *user_data); // G<-, then G->
void shiftgui(tap_dance_state_t *state, void *user_data); // G->SG
void guictl(tap_dance_state_t *state, void *user_data); // G->GC
void deleter(tap_dance_state_t *state, void *user_data); // bkspc -> delwrd -> delline
void ubermod(tap_dance_state_t *state, void *user_data); // CTL->ALT->GUI
void ubermod_mac(tap_dance_state_t *state, void *user_data); // GUI->CTL->ALT
void ubermod2(tap_dance_state_t *state, void *user_data); // ALT->CTL->GUI
void ubermod2_mac(tap_dance_state_t *state, void *user_data); // ALT->GUI->CTL
void shift_reset(tap_dance_state_t *state, void *user_data);
void gui_reset(tap_dance_state_t *state, void *user_data);
void CAS_reset(tap_dance_state_t *state, void *user_data);
void CASG_reset(tap_dance_state_t *state, void *user_data);
void ubermod_reset(tap_dance_state_t *state, void *user_data); // AKA CAG_reset
void shiftenter(tap_dance_state_t *state, void *user_data);
void shiftentercaps(tap_dance_state_t *state, void *user_data);
void ctrl_all_mac(tap_dance_state_t *state, void *user_data); // C->CG->CAG
void ctrl_all(tap_dance_state_t *state, void *user_data); // C->CA->SC
void alt_all(tap_dance_state_t *state, void *user_data); // A->SA->AC
void shift_and(tap_dance_state_t *state, void *user_data); // SC->SA->SG
void shift_and_mac(tap_dance_state_t *state, void *user_data); // SG->SC->SA

enum {
    SHCAP = 0
   ,TDGUI
   ,TDGUI2
   ,SHENT
   ,SHNTC
   ,GUCTL
   ,FRBK
   ,FRBK2
   ,GCA 
   ,AGC 
   ,SGCA
   ,SCAG
   ,CAG
   ,ACG
   ,CTLALL
   ,CTLAND 
   ,DLTR 
};
