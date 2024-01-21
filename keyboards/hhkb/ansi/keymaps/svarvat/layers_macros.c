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
    && (keycode != KC_TAB)
    && (keycode != KC_UP)
    && (keycode != KC_DOWN)
    && (keycode != KC_LEFT)
    && (keycode != KC_RIGHT)
    && (keycode != MA_LTHUMBD)
    && (keycode != MA_LTHUMBE)
    && (keycode != KC_LSFT)) {
        isCtlTabStarted = false;
        unregister_mods(MOD_MASK_CTRL);
        if ((keycode == KC_ENT)
        || (keycode == MA_ENTX2)
        || (keycode == MA_ENTX4)) {
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
    && (keycode != S(KC_I))
    && (keycode != S(KC_J))
    && (keycode != S(KC_K))
    && (keycode != S(KC_L))
    && (keycode != KC_LSFT)) {
        isAltTabStarted = false;
        unregister_code16(KC_LALT);
        if ((keycode == KC_ENT)
        || (keycode == MA_ENTX2)
        || (keycode == MA_ENTX4)) {
            return false;
        }
    }
    if (isSftTabStarted
    && (keycode != KC_TAB)
    && (keycode != KC_I)
    && (keycode != KC_J)
    && (keycode != KC_K)
    && (keycode != KC_L)
    && (keycode != S(KC_I))
    && (keycode != S(KC_J))
    && (keycode != S(KC_K))
    && (keycode != S(KC_L))) {
        isSftTabStarted = false;
        unregister_code16(KC_LSFT);
        if ((keycode == KC_ENT)
        || (keycode == MA_ENTX2)
        || (keycode == MA_ENTX4)) {
            return false;
        }
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
            if ((mod_state & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT) && record->event.pressed) {
                isCapswordStarted = true;
                layer_on(LA_CAPSLOCK);
                return false;
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
        default:
            return true;
    }
}
bool processKeycodeIfLCapslock(uint16_t keycode, keyrecord_t* record) {
    if (isCapswordStarted &&
    (keycode == KC_SPC
    || keycode == KC_UP
    || keycode == KC_DOWN
    || keycode == KC_HOME
    || keycode == KC_END
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
        case S(KC_I):
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
        case S(KC_J):
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
        case S(KC_K):
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
        case S(KC_L):
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
//        case MA_CIRC:
//            if (record->event.pressed) {
//                if (!(isDeadKeyTremaStarted) && mod_state && MOD_MASK_SHIFT) {isDeadKeyTremaStarted=true;}
//                else if (!isDeadKeyCircStarted) {isDeadKeyCircStarted=true;}
//            }
//            return false;
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
//    }
//    if (isDeadKeyCircStarted) {isDeadKeyCircStarted=false;}
//    if (isDeadKeyTremaStarted) {isDeadKeyTremaStarted=false;}
        default:
            return true;
    }
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
        case KC_DOWN:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_DOWN);
                } else if (isSftTabStarted) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    register_code16(KC_LSFT);
                } else {
                    mouseDown = true;
                }
            } else {
                mouseDown = false;
            }
            return false;
        case KC_UP:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_UP);
                } else if (isSftTabStarted) {
                    tap_code16(KC_TAB);
                } else {
                    mouseUp = true;
                }
            } else {
                mouseUp = false;
            }
            return false;
        case KC_LEFT:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_LEFT);
                } else if (isSftTabStarted) {
                    tap_code16(KC_TAB);
                } else {
                    mouseLeft = true;
                }
            } else {
                mouseLeft = false;
            }
            return false;
        case KC_RIGHT:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_RIGHT);
                } else if (isSftTabStarted) {
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    register_code16(KC_LSFT);
                } else {
                    mouseRight = true;
                }
            } else {
                mouseRight = false;
            }
            return false;
        case KC_END:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN5);
            }
            return false;
        case KC_HOME:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN4);
            }
            return false;
        default:
            return true;
    }
}
bool processKeycodeIfLPinky(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LPINKY:
            if (!(record->event.pressed)) {
                layer_off(LA_LPINKY);
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
        case KC_UP:
            if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT) && IS_LAYER_OFF(LA_LTHUMB) && record->event.pressed) {
                unregister_code16(KC_LSFT);
                tap_code16(KC_DOWN);
                register_code16(KC_LSFT);
                return false;
            }
            return true;
        case FR_EQL:
            if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT) && record->event.pressed) {
                unregister_code16(KC_LSFT);
                tap_code16(FR_EQL);
                tap_code16(FR_RABK);
                register_code16(KC_LSFT);
                return false;
            }
            return true;
        case FR_MINS:
            if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT) && record->event.pressed) {
                unregister_code16(KC_LSFT);
                tap_code16(FR_MINS);
                tap_code16(FR_RABK);
                register_code16(KC_LSFT);
                return false;
            }
            return true;
        default:
            return true;
    }
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
        default:
            return true;
    }
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
            if (isCtlTabStarted && record->event.pressed) {
                register_code16(KC_LSFT);
                tap_code16(KC_TAB);
                unregister_code16(KC_LSFT);
                return false;
            }
            return true;
        case KC_DOWN:
            if (isCtlTabStarted && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            }
            return true;
        case KC_LEFT:
            if (isCtlTabStarted && record->event.pressed) {
                register_code16(KC_LSFT);
                tap_code16(KC_TAB);
                unregister_code16(KC_LSFT);
                return false;
            } else if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_LEFT);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_RGHT:
            if (isCtlTabStarted && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            } else if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_RGHT);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_PGUP:
            if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_HOME);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_PGDN:
            if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_END);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_BSPC:
            if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_BSPC);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_DEL:
            if (IS_LAYER_ON(LA_LPINKY) && record->event.pressed) {
                register_code16(KC_LCTL);
                tap_code16(KC_DEL);
                unregister_code16(KC_LCTL);
                return false;
            }
            return true;
        case KC_TAB:
            if (!isCtlTabStarted && record->event.pressed) {
                isCtlTabStarted = true;
                register_mods(MOD_MASK_CTRL);
                tap_code16(KC_TAB);
                return false;
            }
            return true;
        default:
            return true;
    }
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
                isWeakLaMouseStarted = false;
                layer_off(LA_LTHUMBMS);
                layer_off_lmouse();
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                isMouseX2Started = true;
                if (!isWeakLaMouseStarted) {
                    layer_on_weak_layer(LA_LTHUMBDWEAK);
                }
            } else {
                isMouseX2Started = false;
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                isMouseX4Started = true;
                if (!isWeakLaMouseStarted) {
                    layer_on_weak_layer(LA_LTHUMBEWEAK);
                }
            } else {
                isMouseX4Started = false;
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
        case KC_MS_BTN1:
            if (isWeakLaMouseStarted) {
                return true;
            } else {
                if (record->event.pressed) {
                    tap_code16(KC_AUDIO_VOL_UP);
                }
            }
            return false;
        case KC_MS_BTN3:
            if (isWeakLaMouseStarted) {
                return true;
            } else {
                if (record->event.pressed) {
                    tap_code16(KC_AUDIO_VOL_DOWN);
                }
            }
            return false;
        case KC_TAB:
            if (!isCtlTabStarted && record->event.pressed) {
                isCtlTabStarted = true;
                register_mods(MOD_MASK_CTRL);
                tap_code16(KC_TAB);
            }
            return true;
        case KC_UP:
            if (isCtlTabStarted && record->event.pressed) {
                register_code16(KC_LSFT);
                tap_code16(KC_TAB);
                unregister_code16(KC_LSFT);
                return false;
            }
            return true;
        case KC_DOWN:
            if (isCtlTabStarted && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            }
            return true;
        case KC_LEFT:
            if (isCtlTabStarted && record->event.pressed) {
                register_code16(KC_LSFT);
                tap_code16(KC_TAB);
                unregister_code16(KC_LSFT);
                return false;
            }
            return true;
        case KC_RIGHT:
            if (isCtlTabStarted && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            }
            return true;
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
        default:
            return true;
    }
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
        default:
            return true;
    }
}
bool processKeycodeIfLThumbEWeak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                if (isLThumbMoPristine && isLThumbWeakPristine) {
                    layer_on(LA_LTHUMBESTRONG);
                }
                layer_off_weak_layer(LA_LTHUMBEWEAK);
                layer_off_mo_layer(LA_LTHUMBEMO);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBE:
            if (IS_LAYER_ON(LA_LTHUMBMS)) {
                if (record->event.pressed) {
                    if (isLThumbWeakPristine
                    && !mouseDown
                    && !mouseUp
                    && !mouseRight
                    && !mouseLeft) {
                        isLThumbWeakPristine = false;
                        tap_code16(C(KC_Q));
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
                return true;
            } else {
                if (record->event.pressed) {
                    layer_on(LA_LTHUMBEMO);
                    if (isLThumbWeakPristine) {
                        tap_code16(C(KC_Q));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
                return false;
            }
        case MA_LTHUMBD:
        case MA_LTHUMB1:
        case MA_LTHUMB2:
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBEWEAK);
            }
            return true;
        default:
            isLThumbWeakPristine = false;
            return true;
    }
}
bool processKeycodeIfLThumbDWeak(uint16_t keycode, keyrecord_t* record) {
    if (!switch_ctl_tab_off(keycode)) {return false;}
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                if(isLThumbMoPristine && isLThumbWeakPristine) {
                    layer_on(LA_LTHUMBDSTRONG);
                }
                layer_off_weak_layer(LA_LTHUMBDWEAK);
                layer_off_mo_layer(LA_LTHUMBDMO);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
                inMemoryPreviousWeakLayer = 0;
            }
            return false;
        case MA_LTHUMBD:
            if (IS_LAYER_ON(LA_LTHUMBMS)) {
                if (record->event.pressed) {
                    if (isLThumbWeakPristine
                    && !mouseDown
                    && !mouseUp
                    && !mouseRight
                    && !mouseLeft) {
                        isLThumbWeakPristine = false;
                        tap_code16(G(KC_UP));
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
                return true;
            } else {
                if (record->event.pressed) {
                    layer_on(LA_LTHUMBDMO);
                    if (isLThumbWeakPristine) {
                        tap_code16(G(KC_UP));
                        isLThumbWeakPristine = false;
                    } else {
                        isLThumbWeakPristine = true;
                    }
                }
                return false;
            }
        case MA_LTHUMBE:
        case MA_LTHUMB1:
        case MA_LTHUMB2:
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_off_weak_layer(LA_LTHUMBDWEAK);
            }
            return true;
        default:
            isLThumbWeakPristine = false;
            return true;
    }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(C(A(KC_E)));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                }
                return true;
            }
        case MA_LTHUMBD:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(C(A(KC_D)));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                }
                return true;
            }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(C(A(KC_2)));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                }
                return true;
            }
        case MA_LTHUMB3:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(C(A(KC_3)));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB1WEAK);
                }
                return true;
            }
        default:
            isLThumbWeakPristine = false;
            return true;
    }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(RCS(KC_E));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                }
                return true;
            }
        case MA_LTHUMBD:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(RCS(KC_D));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                }
                return true;
            }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(RCS(KC_1));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                }
                return true;
            }
        case MA_LTHUMB3:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(RCS(KC_3));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB2WEAK);
                }
                return true;
            }
        default:
            isLThumbWeakPristine = false;
            return true;
    }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(LALT(KC_E));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                }
                return true;
            }
        case MA_LTHUMBD:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(LALT(KC_D));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                }
                return true;
            }
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
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(LALT(KC_1));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                }
                return true;
            }
        case MA_LTHUMB2:
            if (isLThumbWeakPristine) {
                if (record->event.pressed) {
                    isLThumbWeakPristine = false;
                    tap_code16(LALT(KC_2));
                }
                return false;
            } else {
                if (record->event.pressed) {
                    layer_off_weak_layer(LA_LTHUMB3WEAK);
                }
                return true;
            }
        default:
            isLThumbWeakPristine = false;
            return true;
    }
}
bool processKeycodeIfLThumbEStrong(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBE:
            return false;
        case MA_SUPER:
            register_mods(MOD_MASK_CTRL);
            editModeLThumbStrongStarted = true;
            return false;
        case MA_NONE:
            if (editModeLThumbStrongStarted) {
                unregister_mods(MOD_MASK_CTRL);
                editModeLThumbStrongStarted = false;
            }
            layer_off(LA_LTHUMBESTRONG);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLThumbStrongStarted) {
                unregister_mods(MOD_MASK_CTRL);
                editModeLThumbStrongStarted = false;
            }
            layer_off(LA_LTHUMBESTRONG);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLThumbStrongStarted) {
                    unregister_mods(MOD_MASK_CTRL);
                    editModeLThumbStrongStarted = false;
                }
                layer_off(LA_LTHUMBESTRONG);
            }
            return true;
    }
}
bool processKeycodeIfLThumbDStrong(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBD:
            return false;
        case MA_SUPER:
            register_mods(MOD_MASK_CTRL);
            editModeLThumbStrongStarted = true;
            return false;
        case MA_NONE:
            if (editModeLThumbStrongStarted) {
                unregister_mods(MOD_MASK_CTRL);
                editModeLThumbStrongStarted = false;
            }
            layer_off(LA_LTHUMBDSTRONG);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLThumbStrongStarted) {
                unregister_mods(MOD_MASK_CTRL);
                editModeLThumbStrongStarted = false;
            }
            layer_off(LA_LTHUMBDSTRONG);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLThumbStrongStarted) {
                    unregister_mods(MOD_MASK_CTRL);
                    editModeLThumbStrongStarted = false;
                }
                layer_off(LA_LTHUMBDSTRONG);
            }
            return true;
    }
}

