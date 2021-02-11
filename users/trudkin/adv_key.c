
#ifdef USE_ADVANCED 
typedef struct {
    uint16_t keycode;
    uint8_t  mod;
    uint8_t  layer;
    uint16_t new_action;
} altered_action_t;

static altered_action_t altered_actions[] = {  
    {KC_Z,MOD_MASK_CA,_NUMPAD,0},
    {KC_TAB,MOD_MASK_CA,0,0},
    {KC_C,MOD_MASK_CTRL,0,RCTL(KC_INS)},
    {KC_X,MOD_MASK_CTRL,0,RSFT(KC_DEL)},
    {KC_V,MOD_BIT(KC_LCTRL),0,RSFT(KC_INS)},
    {KC_C,MOD_MASK_GUI,0,RCTL(KC_C)},
};


static uint8_t altered_size = sizeof(altered_actions)/sizeof(altered_action_t);



void extended_action(uint16_t  action){
    switch (action) {
    case KC_TAB: /*This can be anythinp you can code */
        send_string(PSTR("This can be any code, but this is a demo"));
    }
}


bool test_mods(uint8_t mods, uint8_t cur_mods){
    bool v_ret = false;
    switch (mods) {
    case MOD_MASK_CTRL :     
    case MOD_MASK_SHIFT:
    case MOD_MASK_ALT:
    case MOD_MASK_GUI:
        v_ret = cur_mods & mods;
         break;
    case     MOD_MASK_CS: 
        v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_SHIFT;
         break;
    case     MOD_MASK_CA:
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_ALT;
         break;
    case MOD_MASK_CG :
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_GUI;
         break;
    case MOD_MASK_SA :
         v_ret = cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_ALT;
         break;
    case MOD_MASK_SG :
         v_ret = cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_GUI;
         break;
    case MOD_MASK_AG :
         v_ret = cur_mods & MOD_MASK_GUI && cur_mods & MOD_MASK_ALT;
         break;
    case MOD_MASK_CSA:
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_ALT;
         break;
    case MOD_MASK_CSG:
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_GUI;
         break;
    case MOD_MASK_CAG:
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_ALT && cur_mods & MOD_MASK_GUI;
         break;
    case MOD_MASK_SAG:
         v_ret = cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_ALT && cur_mods & MOD_MASK_GUI;
         break;
    case MOD_MASK_CSAG:
         v_ret = cur_mods & MOD_MASK_CTRL && cur_mods & MOD_MASK_ALT && cur_mods & MOD_MASK_SHIFT && cur_mods & MOD_MASK_GUI;
         break;
    default:
        v_ret = cur_mods & mods;
    }
    return v_ret;
}


bool process_altered_action(uint16_t keycode){
    uint8_t temp_mod = mod_config(get_mods());
    uint8_t temp_osm = mod_config(get_oneshot_mods());

    for (int i=0;i<altered_size;++i) {
        if (altered_actions[i].keycode == keycode && test_mods( altered_actions[i].mod, (temp_mod | temp_osm))) {
                clear_mods();
            clear_oneshot_mods();
            if (altered_actions[i].new_action != 0) {
                tap_code16(altered_actions[i].new_action);
            } else if (altered_actions[i].layer != 0) {
                layer_invert(altered_actions[i].layer)  ;             
            } else {    
                extended_action(altered_actions[i].keycode);
            }
            set_mods(temp_mod);
            return false;
        }
    }
    return true;
}
#endif 


// add to proces_records
#ifdef USE_ADVANCED
    default:
        if (get_mods() &&  record->event.pressed) {
        
           return process_altered_action(keycode);
        }
#endif 
