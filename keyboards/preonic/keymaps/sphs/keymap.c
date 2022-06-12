#include "win/layers.c"
#include "mac/layers.c"
#include "profile.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* -------------------------------------------------------------------------------------------- */
    /*                                        Windows Layout                                        */
    /* -------------------------------------------------------------------------------------------- */
    [_BSW] = LAYOUT_preonic_grid_win(LAYER_BSW),
    [_NMW] = LAYOUT_preonic_grid_win(LAYER_NMW),
    [_SMW] = LAYOUT_preonic_grid_win(LAYER_SMW),
    [_MKW] = LAYOUT_preonic_grid_win(LAYER_MKW),
    [_NVW] = LAYOUT_preonic_grid_win(LAYER_NVW),
    [_FNW] = LAYOUT_preonic_grid_win(LAYER_FNW),
    [_LLW] = LAYOUT_preonic_grid_win(LAYER_LLW),

    /* -------------------------------------------------------------------------------------------- */
    /*                                         MacOS Layout                                         */
    /* -------------------------------------------------------------------------------------------- */
    [_BSM] = LAYOUT_preonic_grid_mac(LAYER_BSM),
    [_NMM] = LAYOUT_preonic_grid_mac(LAYER_NMM),
    [_SMM] = LAYOUT_preonic_grid_mac(LAYER_SMM),
    [_MKM] = LAYOUT_preonic_grid_mac(LAYER_MKM),
    [_NVM] = LAYOUT_preonic_grid_mac(LAYER_NVM),
    [_FNM] = LAYOUT_preonic_grid_mac(LAYER_FNM),
    [_LLM] = LAYOUT_preonic_grid_mac(LAYER_LLM)
};
