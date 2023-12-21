//bool isDeadKeyCircStarted = false;
//bool isDeadKeyTremaStarted = false;
bool editModeLThumbStrongStarted = false;
bool isCtlTabStarted = false;
bool isAltTabStarted = false;
bool isSftTabStarted = false;
bool isCapswordStarted = false;
bool mouseLeft = false;
bool mouseRight = false;
bool mouseUp = false;
bool mouseDown = false;
bool isMouseX1Started = false;
bool isMouseX2Started = false;
bool isMouseX4Started = false;
bool scrollLeft = false;
bool scrollRight = false;
bool scrollUp = false;
bool scrollDown = false;
bool isScrollX1Started = false;
bool isScrollX2Started = false;
bool isScrollX4Started = false;
bool isWeakLaMouseStarted = false;
bool isLThumbMoPristine = true;
bool isLThumbWeakPristine = true;
uint16_t inMemoryPreviousWeakLayer = 0;
uint16_t inMemoryCurrentWeakLayer = 0;

void layer_on_lmouse(void) {
    layer_on(LA_MOUSE);
    tap_code16(KC_SCROLL_LOCK);
    isMouseX1Started = true;
    isScrollX1Started = true;
}
void layer_off_lmouse(void) {
//  set_auto_mouse_enable(false);
    layer_off(LA_MOUSE);
    tap_code16(KC_SCROLL_LOCK);
    isMouseX1Started = false;
    isScrollX1Started = false;
    isMouseX2Started = false;
    isScrollX2Started = false;
    isMouseX4Started = false;
    isScrollX4Started = false;
    scrollLeft = false;
    scrollUp = false;
    scrollDown = false;
    scrollRight = false;
    mouseDown = false;
    mouseUp = false;
    mouseRight = false;
    mouseLeft = false;
}
void layer_off_mo_layer(uint16_t layer) {
    isLThumbMoPristine = true;
    layer_off(layer);
}
void layer_on_weak_layer(uint16_t layer) {
    inMemoryCurrentWeakLayer = layer;
    layer_on(layer);
}
void layer_off_weak_layer(uint16_t layer) {
    inMemoryPreviousWeakLayer = layer;
    isLThumbWeakPristine = true;
    layer_off(layer);
}
void reverse_weak_layer(bool isLThumbMoPristine) {
    if (isLThumbMoPristine && (inMemoryPreviousWeakLayer != 0)) {
        layer_off(inMemoryCurrentWeakLayer);
        layer_on(inMemoryPreviousWeakLayer);
        isLThumbMoPristine = false;
        isLThumbWeakPristine = false;
    }
}
bool switch_ctl_tab_off(uint16_t keycode) {
    if (isCtlTabStarted
    && (keycode != MA_TAB)
    && (keycode != KC_UP)
    && (keycode != KC_DOWN)
    && (keycode != KC_LEFT)
    && (keycode != KC_RIGHT)
    && (keycode != MA_LTHUMBD)
    && (keycode != MA_LTHUMBE)
    && (keycode != KC_LSFT)) {
        isCtlTabStarted = false;
        unregister_mods(MOD_MASK_CTRL);
        if ((keycode != MA_LTHUMB)
        && (keycode != MA_LTHUMBMS)) {
            return false;
        }
    }
    return true;
}

bool processKeycodeIfLBase(uint16_t keycode, keyrecord_t* record) {
    if (isAltTabStarted
    && (keycode != KC_TAB)
    && (keycode != KC_I)
    && (keycode != KC_J)
    && (keycode != KC_K)
    && (keycode != KC_L)
    && (keycode != MA_LMOUSE)
    && (keycode != KC_LSFT)) {
        isAltTabStarted = false;
        unregister_code16(KC_LALT);
        return false;
    }
    if (isSftTabStarted
    && (keycode != KC_TAB)
    && (keycode != KC_I)
    && (keycode != KC_J)
    && (keycode != KC_K)
    && (keycode != KC_L)
    && (keycode != MA_LMOUSE)) {
        isSftTabStarted = false;
        unregister_code16(KC_LSFT);
        return false;
    }
    switch (keycode) {
        case MA_LTHUMB:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB);
            }
            return false;
        case MA_LPINKY:
            if (record->event.pressed) {
                layer_on(LA_LPINKY);
            }
            return false;
        case MA_LMOUSE:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)
                && (mod_state & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)
                && (mod_state & MOD_BIT(KC_RALT)) == MOD_BIT(KC_RALT)) {
                    reset_keyboard();
                } else {
//                    set_auto_mouse_enable(true);
                    layer_on_lmouse();
                }
            }
            return false;
        case MA_CAPSLOCK:
            if (record->event.pressed) {
                layer_on(LA_CAPSLOCK);
            }
            return false;
        case KC_LSFT:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)) {
                    isCapswordStarted = true;
                    layer_on(LA_CAPSLOCK);
                    return false;
                }
            }
            return true;
        case KC_RSFT:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    isCapswordStarted = true;
                    layer_on(LA_CAPSLOCK);
                    return false;
                }
            }
            return true;
        case KC_I:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_UP);
                    return false;
                } else if (isSftTabStarted) {
                    tap_code16(KC_TAB);
                    return false;
                }
            }
            return true;
        case KC_J:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_LEFT);
                    return false;
                } else if (isSftTabStarted) {
                    tap_code16(KC_TAB);
                    return false;
                }
            }
            return true;
        case KC_K:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_DOWN);
                    return false;
                } else if (isSftTabStarted) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    register_code16(KC_LSFT);
                    return false;
                }
            }
            return true;
        case KC_L:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_RIGHT);
                    return false;
                } else if (isSftTabStarted) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    register_code16(KC_LSFT);
                    return false;
                }
            }
            return true;
        case KC_TAB:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT) && !isAltTabStarted) {
                    isAltTabStarted = true;
                } else if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT) && !isSftTabStarted) {
                    isSftTabStarted = true;
                }
            }
            return true;
        case KC_SLSH:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(ALGR(KC_8));
                    register_code16(KC_LSFT);
                    return false;
                }
            }
            return true;
        case MA_REBOOT:
            clear_keyboard();
            soft_reset_keyboard();
            return false;
    }
    return true;
}
bool processKeycodeIfLMouse(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LMOUSE:
            if (record->event.pressed) {
                layer_off_lmouse();
            }
            return false;
        case MA_LTHUMBMS:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBMS);
            } else {
                layer_off(LA_LTHUMBMS);
            }
            return false;
        case MA_MS_BTN1_TAP:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN1);
            }
            return false;
        case MA_MS_BTN2_TAP:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN2);
            }
            return false;
        case MA_MS_WH_DOWN:
            if (record->event.pressed) {
                scrollDown = true;
            } else {
                scrollDown = false;
            }
            return false;
        case MA_MS_WH_UP:
            if (record->event.pressed) {
                scrollUp = true;
            } else {
                scrollUp = false;
            }
            return false;
        case MA_DOWN:
            if (record->event.pressed) {
                mouseDown = true;
            } else {
                mouseDown = false;
            }
            return false;
        case MA_UP:
            if (record->event.pressed) {
                mouseUp = true;
            } else {
                mouseUp = false;
            }
            return false;
        case MA_LEFT:
            if (record->event.pressed) {
                mouseLeft = true;
            } else {
                mouseLeft = false;
            }
            return false;
        case MA_RIGHT:
            if (record->event.pressed) {
                mouseRight = true;
            } else {
                mouseRight = false;
            }
            return false;
        case MA_END:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN5);
            }
            return false;
        case MA_HOME:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN4);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLCapslock(uint16_t keycode, keyrecord_t* record) {
    if (isCapswordStarted &&
    (keycode == KC_SPC
    || keycode == KC_UP
    || keycode == KC_DOWN
    || keycode == MA_HOME
    || keycode == MA_END
    || keycode == KC_ENT
    || keycode == KC_RSFT
    || keycode == KC_LSFT)) {
        if (record->event.pressed) {
            isCapswordStarted = false;
            layer_off(LA_CAPSLOCK);
        }
    }
    switch (keycode) {
        case MA_CAPSLOCK:
        case MA_CAPSWORD:
            if (record->event.pressed) {
                isCapswordStarted = false;
                layer_off(LA_CAPSLOCK);
            }
            return false;
        case MA_CIRC:
//            if (record->event.pressed) {
//                if (!(isDeadKeyTremaStarted) && mod_state && MOD_MASK_SHIFT) {isDeadKeyTremaStarted=true;}
//                else if (!isDeadKeyCircStarted) {isDeadKeyCircStarted=true;}
//            }
            return false;
//        case MA_CAPSE:
//            if (record->event.pressed) {
//                if (isDeadKeyTremaStarted) {
//                    tap_code16(X(ETREMA));
//                    isDeadKeyTremaStarted=false;
//                } else if (isDeadKeyCircStarted) {
//                    register_code16(KC_RALT);
//                    tap_code16(S(X(ECIRC)));
//                    unregister_code16(KC_RALT);
//                    isDeadKeyCircStarted=false;
//                } else {
//                    register_code16(KC_RALT);
//                    tap_code16(X(ECIRC));
////                    tap_code16(S(KC_E));
//                    unregister_code16(KC_RALT);
//                }
//            }
//            return false;
//        case MA_CAPSA:
//            if (record->event.pressed) {
//                if (isDeadKeyTremaStarted) {
//                    tap_code16(X(ATREMA));
//                    isDeadKeyTremaStarted=false;
//                }
//                else if (isDeadKeyCircStarted) {
//                    tap_code16(X(ACIRC));
//                    isDeadKeyCircStarted=false;
//                }
//                else {tap_code16(S(KC_Q));}
//            }
//            return false;
//        case MA_CAPSI:
//            if (record->event.pressed) {
//                if (isDeadKeyTremaStarted) {
//                    tap_code16(X(ITREMA));
//                    isDeadKeyTremaStarted=false;
//                }
//                else if (isDeadKeyCircStarted) {
//                    tap_code16(X(ICIRC));
//                    isDeadKeyCircStarted=false;
//                }
//                else {tap_code16(S(KC_I));}
//            }
//            return false;
//        case MA_CAPSU:
//            if (record->event.pressed) {
//                if (isDeadKeyTremaStarted) {
//                    tap_code16(X(UTREMA));
//                    isDeadKeyTremaStarted=false;
//                }
//                else if (isDeadKeyCircStarted) {
//                    tap_code16(X(UCIRC));
//                    isDeadKeyCircStarted=false;
//                }
//                else {tap_code16(S(KC_U));}
//            }
//            return false;
    }
//    if (isDeadKeyCircStarted) {isDeadKeyCircStarted=false;}
//    if (isDeadKeyTremaStarted) {isDeadKeyTremaStarted=false;}
    return true;
}
bool processKeycodeIfLPinky(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LPINKY:
            if (!(record->event.pressed)) {
                layer_off(LA_LPINKY);
            }
            return false;
        case MA_ENT:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
            }
            return false;
        case MA_DELLINE:
            if (record->event.pressed) {
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                register_code16(KC_LSFT);
                tap_code16(KC_END);
                tap_code16(KC_RGHT);
                unregister_code16(KC_LSFT);
                tap_code16(KC_DEL);
            }
            return false;
        case MA_JUMPTAB:
            if (!(record->event.pressed)) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_UP);
                    tap_code16(KC_HOME);
                    tap_code16(KC_HOME);
                    tap_code16(KC_DEL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(KC_HOME);
                    tap_code16(KC_HOME);
                    tap_code16(KC_TAB);
                    tap_code16(KC_DOWN);
                }
            }
            return false;
        case MA_ESC:
            if (record->event.pressed) {
                tap_code16(KC_ESC);
            }
            return false;
        case MA_UP:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_DOWN);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(KC_UP);
                }
            }
            return false;
        case MA_BSPC:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
            }
            return false;
        case MA_0:
            if (record->event.pressed) {
                tap_code16(FR_0);
            }
            return false;
        case MA_1:
            if (record->event.pressed) {
                tap_code16(FR_1);
            }
            return false;
        case MA_2:
            if (record->event.pressed) {
                tap_code16(FR_2);
            }
            return false;
        case MA_3:
            if (record->event.pressed) {
                tap_code16(FR_3);
            }
            return false;
        case MA_4:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_5);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_4);
                }
            }
            return false;
        case MA_5:
            if (record->event.pressed) {
                tap_code16(FR_5);
            }
            return false;
        case MA_6:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_MINS);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_6);
                }
            }
            return false;
        case MA_7:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_NUBS);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_7);
                }
            }
            return false;
        case MA_8:
            if (record->event.pressed) {
                tap_code16(FR_8);
            }
            return false;
        case MA_9:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(S(FR_LABK));
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_9);
                }
            }
            return false;
        case MA_EQL:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(FR_EQL);
                    tap_code16(FR_RABK);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_EQL);
                }
            }
            return false;
        case MA_MINS:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LSFT);
                    tap_code16(FR_MINS);
                    tap_code16(FR_RABK);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16(FR_MINS);
                }
            }
            return false;
        case MA_ASTR:
            if (record->event.pressed) {
                tap_code16(FR_ASTR);
            }
            return false;
        case MA_DOT:
            if (record->event.pressed) {
                tap_code16(FR_DOT);
            }
            return false;
        case MA_PLUS:
            if (record->event.pressed) {
                tap_code16(FR_PLUS);
            }
            return false;
        case MA_SLSH:
            if (record->event.pressed) {
                tap_code16(FR_SLSH);
            }
            return false;
        case MA_SPC:
            if (record->event.pressed) {
                tap_code16(KC_SPC);
            }
            return false;
        case MA_DEL:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
            }
            return false;
        case MA_F1:
            if (record->event.pressed) {
                tap_code16(KC_F1);
            }
            return false;
        case MA_F2:
            if (record->event.pressed) {
                tap_code16(KC_F2);
            }
            return false;
        case MA_F3:
            if (record->event.pressed) {
                tap_code16(KC_F3);
            }
            return false;
        case MA_F4:
            if (record->event.pressed) {
                tap_code16(KC_F4);
            }
            return false;
        case MA_F5:
            if (record->event.pressed) {
                tap_code16(KC_F5);
            }
            return false;
        case MA_F6:
            if (record->event.pressed) {
                tap_code16(KC_F6);
            }
            return false;
        case MA_F7:
            if (record->event.pressed) {
                tap_code16(KC_F7);
            }
            return false;
        case MA_F8:
            if (record->event.pressed) {
                tap_code16(KC_F8);
            }
            return false;
        case MA_F9:
            if (record->event.pressed) {
                tap_code16(KC_F9);
            }
            return false;
        case MA_F10:
            if (record->event.pressed) {
                tap_code16(KC_F10);
            }
            return false;
        case MA_F11:
            if (record->event.pressed) {
                tap_code16(KC_F11);
            }
            return false;
        case MA_F12:
            if (record->event.pressed) {
                tap_code16(KC_F12);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfRThumb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_BACKTICK:
            if (record->event.pressed) {
                tap_code16(FR_GRV);
                // timer = timer_read();
                tap_code16(KC_SPC);
            }
            return false;
        case MA_TILD:
            if (record->event.pressed) {
                tap_code16(FR_TILD);
                tap_code16(KC_SPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumb(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBDMO);
                layer_on_weak_layer(LA_LTHUMBDWEAK);
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBEMO);
                layer_on_weak_layer(LA_LTHUMBEWEAK);
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_on_weak_layer(LA_LTHUMB1WEAK);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
        case MA_LMOUSE:
            if (record->event.pressed) {
                layer_off(LA_LTHUMB);
                layer_on(LA_LTHUMBMS);
                layer_on_lmouse();
                isWeakLaMouseStarted = true;
            }
            return false;
        case KC_UP:
            if (record->event.pressed) {
                if (isCtlTabStarted) {
                    register_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    unregister_code16(KC_LSFT);
                    return false;
                }
            }
            return true;
        case KC_DOWN:
            if (record->event.pressed) {
                if (isCtlTabStarted) {
                    tap_code16(KC_TAB);
                    return false;
                }
            }
            return true;
        case KC_LEFT:
            if (record->event.pressed) {
                if (isCtlTabStarted) {
                    register_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    unregister_code16(KC_LSFT);
                    return false;
                } else if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_LEFT);
                    unregister_code16(KC_LCTL);
                    return false;
                }
            }
            return true;
        case KC_RGHT:
            if (record->event.pressed) {
                if (isCtlTabStarted ) {
                    tap_code16(KC_TAB);
                    return false;
                } else if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_RGHT);
                    unregister_code16(KC_LCTL);
                    return false;
                }
            }
            return true;
        case MA_HOME:
            if (record->event.pressed) {
                tap_code16(KC_HOME);
                return false;
            }
            return true;
        case MA_END:
            if (record->event.pressed) {
                tap_code16(KC_END);
                return false;
            }
            return true;
        case MA_PGUP:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_HOME);
                    unregister_code16(KC_LCTL);
                } else {
                    tap_code16(KC_PGUP);
                }
                return false;
            }
            return true;
        case MA_PGDN:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_END);
                    unregister_code16(KC_LCTL);
                } else {
                    tap_code16(KC_PGDN);
                }
                return false;
            }
            return true;
        case KC_BSPC:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_BSPC);
                    unregister_code16(KC_LCTL);
                    return false;
                }
            }
            return true;
        case KC_DEL:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LPINKY)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_DEL);
                    unregister_code16(KC_LCTL);
                    return false;
                }
            }
            return true;
        case MA_TAB:
            if (record->event.pressed) {
                if (!isCtlTabStarted) {
                    isCtlTabStarted = true;
                    register_mods(MOD_MASK_CTRL);
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(KC_TAB);
                }
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbMs(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                isWeakLaMouseStarted = false;
                layer_off(LA_LTHUMBMS);
                isMouseX2Started = false;
                isScrollX2Started = false;
                isMouseX4Started = false;
                isScrollX4Started = false;
                scrollLeft = false;
                scrollUp = false;
                scrollDown = false;
                scrollRight = false;
                mouseDown = false;
                mouseUp = false;
                mouseRight = false;
                mouseLeft = false;
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMBMS);
                isWeakLaMouseStarted = false;
                layer_off_lmouse();
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                isMouseX2Started = true;
                layer_on_weak_layer(LA_LTHUMBDWEAK);
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                isMouseX4Started = true;
                layer_on_weak_layer(LA_LTHUMBEWEAK);
            }
            return false;
        case KC_MS_BTN1:
            if (isWeakLaMouseStarted) {
                return true;
            } else {
                if (record->event.pressed) {
                    tap_code16(KC_AUDIO_VOL_UP);
                    return false;
                }
            }
            return false;
        case KC_MS_BTN3:
            if (isWeakLaMouseStarted) {
                return true;
            } else {
                if (record->event.pressed) {
                    tap_code16(KC_AUDIO_VOL_DOWN);
                    return false;
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    register_code16(KC_MS_BTN3);
                } else {
                    layer_on_weak_layer(LA_LTHUMB1WEAK);
                }
            } else if (isWeakLaMouseStarted) {
                unregister_code16(KC_MS_BTN3);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
        case MA_TAB:
            if (record->event.pressed) {
                if (!isCtlTabStarted) {
                    isCtlTabStarted = true;
                    register_mods(MOD_MASK_CTRL);
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(KC_TAB);
                }
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbEMo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBE:
            if (!(record->event.pressed)) {
                layer_off_mo_layer(LA_LTHUMBEMO);
            }
            return false;
        case MA_UPX4:
            if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_DOWNX4:
            if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_LEFTX4:
            if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_RIGHTX4:
            if (record->event.pressed) {
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_DELX4:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_ENTX4:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_BSPCX4:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbDMo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBD:
            if (!(record->event.pressed)) {
                layer_off_mo_layer(LA_LTHUMBDMO);
            }
            return false;
        case MA_UPX2:
            if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_DOWNX2:
            if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_LEFTX2:
            if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_RIGHTX2:
            if (record->event.pressed) {
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_DELX2:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_ENTX2:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
        case MA_BSPCX2:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                reverse_weak_layer(isLThumbMoPristine);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbEWeak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_off_mo_layer(LA_LTHUMBEMO);
                inMemoryPreviousWeakLayer = 0;
                if (isWeakLaMouseStarted) {
                    layer_off_lmouse();
                    isWeakLaMouseStarted = false;
                }
                if (isLThumbMoPristine) {
                    layer_on(LA_LTHUMBESTRONG);
                } else {
                    layer_off(LA_LTHUMBMS);
                    layer_off(LA_LTHUMB);
                }
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX4Started = true;
                    if (isLThumbWeakPristine && !isMouseX1Started) {
                        tap_code16(C(KC_Q));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                } else {
                    layer_on(LA_LTHUMBEMO);
                    if (isLThumbWeakPristine) {
                        tap_code16(C(KC_Q));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
            } else {
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX4Started = false;
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_on_weak_layer(LA_LTHUMBDWEAK);
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX2Started = true;
                } else {
                    layer_on(LA_LTHUMBDMO);
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_on_weak_layer(LA_LTHUMB1WEAK);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
    }
    isLThumbWeakPristine = false;
    return true;
}
bool processKeycodeIfLThumbDWeak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_off_mo_layer(LA_LTHUMBDMO);
                inMemoryPreviousWeakLayer = 0;
                if (isWeakLaMouseStarted) {
                    layer_off_lmouse();
                    isWeakLaMouseStarted = false;
                }
                if(isLThumbMoPristine) {
                    layer_on(LA_LTHUMBDSTRONG);
                } else {
                    layer_off(LA_LTHUMBMS);
                    layer_off(LA_LTHUMB);
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX2Started = true;
                    if (isLThumbWeakPristine && !isMouseX1Started) {
                        tap_code16(RSG(KC_D));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                } else {
                    layer_on(LA_LTHUMBDMO);
                    if (isLThumbWeakPristine) {
                        tap_code16(RSG(KC_D));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
            } else {
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX2Started = false;
                }
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_on_weak_layer(LA_LTHUMBEWEAK);
                if (IS_LAYER_ON(LA_LTHUMBMS)) {
                    isMouseX4Started = true;
                } else {
                    layer_on(LA_LTHUMBEMO);
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_on_weak_layer(LA_LTHUMB1WEAK);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
    }
    isLThumbWeakPristine = false;
    return true;
}
bool processKeycodeIfLThumb1Weak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off_weak_layer(LA_LTHUMB1WEAK);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(C(A(KC_E)));
                } else {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                    layer_on_weak_layer(LA_LTHUMBEWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX4Started = true;
                    } else {
                        layer_on(LA_LTHUMBEMO);
                    }
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(C(A(KC_D)));
                } else {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                    layer_on_weak_layer(LA_LTHUMBDWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX2Started = true;
                    } else {
                        layer_on(LA_LTHUMBDMO);
                    }
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    isLThumbWeakPristine = false;
                    tap_code16(C(A(KC_1)));
                } else {
                    isLThumbWeakPristine = true;
                }
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB1WEAK);
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB1WEAK);
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
    }
    isLThumbWeakPristine = false;
    return true;
}
bool processKeycodeIfLThumb2Weak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off_weak_layer(LA_LTHUMB2WEAK);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(RCS(KC_E));
                } else {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                    layer_on_weak_layer(LA_LTHUMBEWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX4Started = true;
                    } else {
                        layer_on(LA_LTHUMBEMO);
                    }
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(RCS(KC_D));
                } else {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                    layer_on_weak_layer(LA_LTHUMBDWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX2Started = true;
                    } else {
                        layer_on(LA_LTHUMBDMO);
                    }
                }
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    isLThumbWeakPristine = false;
                    tap_code16(RCS(KC_2));
                } else {
                    isLThumbWeakPristine = true;
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB2WEAK);
                layer_on_weak_layer(LA_LTHUMB1WEAK);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB2WEAK);
                layer_on_weak_layer(LA_LTHUMB3WEAK);
            }
            return false;
    }
    isLThumbWeakPristine = false;
    return true;
}
bool processKeycodeIfLThumb3Weak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off_weak_layer(LA_LTHUMB3WEAK);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(LALT(KC_E));
                } else {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                    layer_on_weak_layer(LA_LTHUMBEWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX4Started = true;
                    } else {
                        layer_on(LA_LTHUMBEMO);
                    }
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    tap_code16(LALT(KC_D));
                } else {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                    layer_on_weak_layer(LA_LTHUMBDWEAK);
                    if (IS_LAYER_ON(LA_LTHUMBMS)) {
                        isMouseX2Started = true;
                    } else {
                        layer_on(LA_LTHUMBDMO);
                    }
                }
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                if (isLThumbWeakPristine) {
                    isLThumbWeakPristine = false;
                    tap_code16(LALT(KC_3));
                } else {
                    isLThumbWeakPristine = true;
                }
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB3WEAK);
                layer_on_weak_layer(LA_LTHUMB1WEAK);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMB3WEAK);
                layer_on_weak_layer(LA_LTHUMB2WEAK);
            }
            return false;
    }
    isLThumbWeakPristine = false;
    return true;
}
bool processKeycodeIfLThumbEStrong(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBE:
            return false;
        case KC_SPC:
            register_mods(MOD_MASK_CTRL);
            editModeLThumbStrongStarted = true;
            return false;
        case MA_NONE:
            if (editModeLThumbStrongStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDSTRONG);
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (editModeLThumbStrongStarted) {unregister_mods(MOD_MASK_CTRL);}
            layer_off(LA_LTHUMBESTRONG);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLThumbStrongStarted) {unregister_mods(MOD_MASK_CTRL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBESTRONG);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLThumbStrongStarted) {unregister_mods(MOD_MASK_CTRL);}
                if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
                else {layer_off(LA_LTHUMB);}
                layer_off(LA_LTHUMBESTRONG);
            }
            return true;
    }

}
bool processKeycodeIfLThumbDStrong(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBD:
            return false;
        case KC_SPC:
            register_code16(KC_RCTL);
            editModeLThumbStrongStarted = true;
            return false;
        case MA_NONE:
            if (editModeLThumbStrongStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDSTRONG);
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (editModeLThumbStrongStarted) {unregister_code16(KC_RCTL);}
            layer_off(LA_LTHUMBDSTRONG);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLThumbStrongStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDSTRONG);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLThumbStrongStarted) {unregister_code16(KC_RCTL);}
                if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
                else {layer_off(LA_LTHUMB);}
                layer_off(LA_LTHUMBDSTRONG);
            }
            return true;
    }
}

