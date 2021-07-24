#include QMK_KEYBOARD_H

bool _INPUT_JP;

void set_input_mode(bool _mode_jaen){
    _INPUT_JP = _mode_jaen;
    // japanese -> true
    // english  -> false
}

bool input_mode(void){
    return _INPUT_JP;
}
