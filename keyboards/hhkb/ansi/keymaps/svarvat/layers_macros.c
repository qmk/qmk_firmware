bool isLeftThumbEMoStarted = false;
bool isLeftThumbDMoStarted = false;
bool editModeLthumbOslStarted = false;
bool isCtlTabStarted = false;
bool isAltTabStarted = false;
//bool isDeadKeyCircStarted = false;
//bool isDeadKeyTremaStarted = false;
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
bool isCapswordStarted = false;
bool isCtlFStarted = false;

void tap_code16_wrap_lctl(uint16_t keycode) {
    unregister_code16(KC_LCTL);
    tap_code16(keycode);
    register_code16(KC_LCTL);
}

bool processKeycodeIfLBase(uint16_t keycode, keyrecord_t* record) {
    if (isAltTabStarted
    && (keycode != KC_TAB)
    && (keycode != KC_I)
    && (keycode != KC_J)
    && (keycode != KC_K)
    && (keycode != KC_L)
    && (keycode != KC_1)
    && (keycode != MA_LMOUSE)
    && (keycode != KC_LSFT)) {
        isAltTabStarted = false;
        unregister_code16(KC_LALT);
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
                register_code16(KC_LCTL);
            }
            return false;
        case MA_LMOUSE:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)
                && (mod_state & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)
                && (mod_state & MOD_BIT(KC_RALT)) == MOD_BIT(KC_RALT)) {
                    reset_keyboard();
                } else if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_P);
                    unregister_code16(KC_LCTL);
                } else {
//                    set_auto_mouse_enable(true);
                    layer_on(LA_MOUSE);
                    tap_code16(KC_SCROLL_LOCK);
                    isMouseX1Started = true;
                    isScrollX1Started = true;
                }
            }
            return false;
        case MA_CAPSLOCK:
            if (record->event.pressed) {
                layer_on(LA_CAPSLOCK);
            }
            return false;
        case MA_CAPSWORD:
            if (record->event.pressed) {
                isCapswordStarted = true;
                layer_on(LA_CAPSLOCK);
            }
            return false;
        case KC_1:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    register_code16(KC_LCTL);
                    tap_code16(KC_O);
                    unregister_code16(KC_LCTL);
                }
            }
            return true;
        case KC_I:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_UP);
                    return false;
                }
            }
            return true;
        case KC_J:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_LEFT);
                    return false;
                }
            }
            return true;
        case KC_K:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_DOWN);
                    return false;
                }
            }
            return true;
        case KC_L:
            if (record->event.pressed) {
                if (isAltTabStarted) {
                    tap_code16(KC_RIGHT);
                    return false;
                }
            }
            return true;
        case KC_TAB:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT) && !isAltTabStarted) {
                    isAltTabStarted = true;
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
//                set_auto_mouse_enable(false);
                tap_code16(KC_SCROLL_LOCK);
                layer_off(LA_MOUSE);
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
            return false;
        case MA_LTHUMBMS:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBMS);
            } else {
                layer_off(LA_LTHUMBMS);
            }
            return false;
        case MA_MS_BTN1_UNREG:
            if (record->event.pressed) {
                unregister_code16(KC_MS_BTN1);
            }
            return false;
        case MA_MS_BTN1_REG:
            if (record->event.pressed) {
                register_code16(KC_MS_BTN1);
            }
            return false;
        case MA_MS_BTN1_TAP:
            if (record->event.pressed) {
                tap_code16(KC_MS_BTN1);
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
    || keycode == KC_ENT)) {
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
        case MA_LTHUMB:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB);
                layer_off(LA_LPINKY);
            }
            return false;
        case MA_LPINKY:
        case KC_LCTL:
            if (!(record->event.pressed)) {
                layer_off(LA_LPINKY);
                unregister_code16(KC_LCTL);
            }
            return false;
        case MA_ENT:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_ENT);
            }
            return false;
        case MA_0:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_0);
            }
            return false;
        case MA_1:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_1);
            }
            return false;
        case MA_2:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_2);
            }
            return false;
        case MA_3:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_3);
            }
            return false;
        case MA_4:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_5);
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_4);
                }
            }
            return false;
        case MA_5:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_5);
            }
            return false;
        case MA_6:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_MINS);
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_6);
                }
            }
            return false;
        case MA_7:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(KC_NUBS);
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_7);
                }
            }
            return false;
        case MA_8:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_8);
            }
            return false;
        case MA_9:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(S(FR_LABK));
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_9);
                }
            }
            return false;
        case MA_EQL:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(FR_EQL);
                    tap_code16(FR_RABK);
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_EQL);
                }
            }
            return false;
        case MA_MINS:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    unregister_code16(KC_LCTL);
                    unregister_code16(KC_LSFT);
                    tap_code16(FR_MINS);
                    tap_code16(FR_RABK);
                    register_code16(KC_LCTL);
                    register_code16(KC_LSFT);
                } else {
                    tap_code16_wrap_lctl(FR_MINS);
                }
            }
            return false;
        case MA_ASTR:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_ASTR);
            }
            return false;
        case MA_DOT:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_DOT);
            }
            return false;
        case MA_PLUS:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_PLUS);
            }
            return false;
        case MA_SLSH:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(FR_SLSH);
            }
            return false;
        case MA_GE:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LA_MOUSE)) {
                    tap_code16(KC_MS_BTN1);
                } else {
                    tap_code16(G(KC_E));
                }
            }
            return false;
        case MA_F1:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F1);
            }
            return false;
        case MA_F2:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F2);
            }
            return false;
        case MA_F3:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F3);
            }
            return false;
        case MA_F4:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F4);
            }
            return false;
        case MA_F5:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F5);
            }
            return false;
        case MA_F6:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F6);
            }
            return false;
        case MA_F7:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F7);
            }
            return false;
        case MA_F8:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F8);
            }
            return false;
        case MA_F9:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F9);
            }
            return false;
        case MA_F10:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F10);
            }
            return false;
        case MA_F11:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F11);
            }
            return false;
        case MA_F12:
            if (record->event.pressed) {
                tap_code16_wrap_lctl(KC_F12);
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
    if (isCtlTabStarted
    && (keycode != MA_TAB)
    && (keycode != KC_UP)
    && (keycode != KC_DOWN)
    && (keycode != KC_LEFT)
    && (keycode != KC_RIGHT)
    && (keycode != MA_LTHUMBQ)
    && (keycode != MA_LTHUMBW)
    && (keycode != KC_LSFT)) {
        isCtlTabStarted = false;
        unregister_code16(KC_LCTL);
        if (keycode == MA_LTHUMB) {
            layer_off(LA_LTHUMB);
        }
        return false;
    }
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    layer_on(LA_LPINKY);
                }
                layer_off(LA_LTHUMB);
            }
            return false;
        case MA_LTHUMBQ:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBQ);
            } else {
                layer_off(LA_LTHUMBQ);
            }
            return false;
        case MA_LTHUMBW:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBW);
            } else {
                layer_off(LA_LTHUMBW);
            }
            return false;
        case MA_LPINKY:
            if (record->event.pressed) {
                register_code16(KC_LCTL);
            } else {
                unregister_code16(KC_LCTL);
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBEMO);
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBDMO);
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB1MO);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB2MO);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB3MO);
            }
            return false;
        case MA_LMOUSE:
            if (record->event.pressed) {
                layer_off(LA_LTHUMB);
                layer_on(LA_MOUSE);
                layer_on(LA_LTHUMBMS);
                isMouseX1Started = true;
                isScrollX1Started = true;
                isWeakLaMouseStarted = true;
            }
            return false;
        case MA_ESC:
            if (IS_LAYER_ON(LA_LTHUMBEOSL) || IS_LAYER_ON(LA_LTHUMBDOSL)) {
                if (record->event.pressed) {
                    layer_off(LA_LTHUMBEOSL);
                    layer_off(LA_LTHUMBDOSL);
                }
            } else {
                if (record->event.pressed) {
                    tap_code16(KC_ESC);
                }
            }
            return false;
        case KC_UP:
            if (record->event.pressed) {
                if (isCtlTabStarted) {
                    register_code16(KC_LSFT);
                    tap_code16(KC_TAB);
                    unregister_code16(KC_LSFT);
                    return false;
                } else if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16_wrap_lctl(KC_UP);
                    return false;
                }
            }
            return true;
        case KC_DOWN:
            if (record->event.pressed) {
                if (isCtlTabStarted) {
                    tap_code16(KC_TAB);
                    return false;
                } else if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16_wrap_lctl(KC_DOWN);
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
                }
            }
            return true;
        case KC_RGHT:
            if (record->event.pressed) {
                if (isCtlTabStarted ) {
                    tap_code16(KC_TAB);
                    return false;
                }
            }
            return true;
        case MA_HOME:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16_wrap_lctl(KC_HOME);
                } else {
                    tap_code16(KC_HOME);
                }
            }
            return true;
        case MA_END:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16_wrap_lctl(KC_END);
                } else {
                    tap_code16(KC_END);
                }
            }
            return true;
        case MA_PGUP:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16(KC_HOME);
                } else {
                    tap_code16(KC_PGUP);
                }
                return false;
            }
            return true;
        case MA_PGDN:
            if (record->event.pressed) {
                if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                    tap_code16(KC_END);
                } else {
                    tap_code16(KC_PGDN);
                }
                return false;
            }
            return true;
        case MA_TAB:
            if (record->event.pressed) {
                if (!isCtlTabStarted) {
                    isCtlTabStarted = true;
                    register_code16(KC_LCTL);
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
    if (isCtlTabStarted && (keycode != MA_TAB)) {
        isCtlTabStarted = false;
        unregister_code16(KC_LCTL);
        if (keycode == MA_LTHUMBMS || keycode == MA_LTHUMB) {
            layer_off(LA_LTHUMBMS);
        }
        return false;
    }
    switch (keycode) {
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
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
            }
            return false;
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
//                set_auto_mouse_enable(false);
                layer_off(LA_MOUSE);
                layer_off(LA_LTHUMBMS);
                isWeakLaMouseStarted = false;
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
            return false;
        case MA_LTHUMBQ:
            if (record->event.pressed) {
                isMouseX2Started = true;
            } else {
                isMouseX2Started = false;
            }
            return false;
        case MA_LTHUMBW:
            if (record->event.pressed) {
                isMouseX4Started = true;
            } else {
                isMouseX4Started = false;
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    tap_code16(KC_MS_BTN1);
                } else {
                    layer_on(LA_LTHUMBEMO);
                }
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    scrollDown = true;
                } else {
                    layer_on(LA_LTHUMBDMO);
                }
            } else {
                if (isWeakLaMouseStarted) {
                    scrollDown = false;
                }
            }
            return false;
        case MA_CS:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    scrollUp = true;
                } else {
                    tap_code16(C(KC_S));
                }
            } else {
                if (isWeakLaMouseStarted) {
                    scrollUp = false;
                }
            }
            return false;
        case KC_LGUI:
            if (isWeakLaMouseStarted) {
                if (record->event.pressed) {
                    scrollUp = true;
                } else {
                    scrollUp = false;
                }
                return false;
            }
            return true;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB1MO);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB2MO);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB3MO);
            }
            return false;
        case MA_ESC:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    register_code16(KC_MS_BTN3);
                } else if (IS_LAYER_ON(LA_LTHUMBEOSL) || IS_LAYER_ON(LA_LTHUMBDOSL)) {
                    layer_off(LA_LTHUMBEOSL);
                    layer_off(LA_LTHUMBDOSL);
                } else {
                    tap_code16(KC_ESC);
                }
            } else {
                if (isWeakLaMouseStarted) {
                    unregister_code16(KC_MS_BTN3);
                }
            }
            return false;
        case MA_TAB:
            if (record->event.pressed) {
                if (isWeakLaMouseStarted) {
                    register_code16(KC_MS_BTN3);
                } else if (!isCtlTabStarted) {
                    isCtlTabStarted = true;
                    register_code16(KC_LCTL);
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(KC_TAB);
                }
            } else {
                if (isWeakLaMouseStarted) {
                    unregister_code16(KC_MS_BTN3);
                }
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbEMo(uint16_t keycode, keyrecord_t* record) {
    if ((keycode != MA_LTHUMB) & (keycode != MA_LTHUMBMS) & (keycode != MA_LTHUMBE)) {
        isLeftThumbEMoStarted = true;
    }
    if ((keycode != MA_CF)) {
        isCtlFStarted = false;
    }
    switch (keycode) {
        case MA_LTHUMBD:
            if (record->event.pressed) {
                isLeftThumbEMoStarted = false;
                layer_off(LA_LTHUMBEMO);
                layer_on(LA_LTHUMBDMO);
            }
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMBEMO);
                if(!isLeftThumbEMoStarted) {
                    layer_on(LA_LTHUMBEOSL);
                } else {
                    isLeftThumbEMoStarted = false;
                    layer_off(LA_LTHUMBMS);
                    layer_off(LA_LTHUMB);
                }
            }
            return false;
        case MA_SELLINE:
            if (record->event.pressed) {
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                register_code16(KC_LSFT);
                tap_code16(KC_END);
                tap_code16(KC_RGHT);
                unregister_code16(KC_LSFT);
            }
            return false;
        case MA_CF:
            if (record->event.pressed) {
                if (isCtlFStarted) {
                    tap_code16(KC_ENT);
                } else {
                    isCtlFStarted = true;
                    tap_code16(C(KC_F));
                }
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbDMo(uint16_t keycode, keyrecord_t* record) {
    if ((keycode != MA_LTHUMB) & (keycode != MA_LTHUMBMS) & (keycode != MA_LTHUMBD)) {
        isLeftThumbDMoStarted = true;
    }
    switch (keycode) {
        case MA_LTHUMBE:
            if (record->event.pressed) {
                isLeftThumbDMoStarted = false;
                layer_off(LA_LTHUMBDMO);
                layer_on(LA_LTHUMBEMO);
            }
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMBDMO);
                if(!isLeftThumbDMoStarted) {
                    layer_on(LA_LTHUMBDOSL);
                } else {
                    isLeftThumbDMoStarted = false;
                    layer_off(LA_LTHUMBMS);
                    layer_off(LA_LTHUMB);
                }
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
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_TAB);
                tap_code16(KC_DOWN);
            }
            return false;
        case MA_JUMPDETAB:
            if (!(record->event.pressed)) {
                tap_code16(KC_UP);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_DEL);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbEOsl(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_SPC:
            register_code16(KC_LCTL);
            editModeLthumbOslStarted = true;
            return false;
        case MA_NONE:
            if (editModeLthumbOslStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDOSL);
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (editModeLthumbOslStarted) {unregister_code16(KC_LCTL);}
            layer_off(LA_LTHUMBEOSL);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLthumbOslStarted) {unregister_code16(KC_LCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBEOSL);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLthumbOslStarted) {unregister_code16(KC_LCTL);}
                if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
                else {layer_off(LA_LTHUMB);}
                layer_off(LA_LTHUMBEOSL);
                return false;
            } else {
                return true;
            }
    }

}
bool processKeycodeIfLThumbDOsl(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_SPC:
            register_code16(KC_RCTL);
            editModeLthumbOslStarted = true;
            return false;
        case MA_NONE:
            if (editModeLthumbOslStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDOSL);
            return false;
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (editModeLthumbOslStarted) {unregister_code16(KC_RCTL);}
            layer_off(LA_LTHUMBDOSL);
            return false;
        case KC_LALT:
        case KC_LSFT:
        case MA_LPINKY:
        case MO(LA_RTHUMB):
            if (editModeLthumbOslStarted) {unregister_code16(KC_RCTL);}
            if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
            else {layer_off(LA_LTHUMB);}
            layer_off(LA_LTHUMBDOSL);
            return true;
        default:
            if (!(record->event.pressed)) {
                if (editModeLthumbOslStarted) {unregister_code16(KC_RCTL);}
                if (IS_LAYER_ON(LA_LTHUMBMS)) {layer_off(LA_LTHUMBMS);}
                else {layer_off(LA_LTHUMB);}
                layer_off(LA_LTHUMBDOSL);
                return false;
            } else {
                return true;
            }
    }
}
bool processKeycodeIfLThumb1Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB1MO);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumb2Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB2MO);
                layer_off(LA_LTHUMB);
                layer_off(LA_LTHUMBMS);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumb3Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB3MO);
                layer_off(LA_LTHUMB);
            }
            return false;
        case MA_LTHUMBMS:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB3MO);
                layer_off(LA_LTHUMBMS);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbQ(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBQ:
            if (!(record->event.pressed)) {
                if (IS_LAYER_ON(LA_MOUSE)) {isMouseX2Started = false;}
                else {layer_off(LA_LTHUMBQ);}
            }
            return false;
        case MA_UPX2:
            if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
            }
            return false;
        case MA_DOWNX2:
            if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
            }
            return false;
        case MA_LEFTX2:
            if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
            }
            return false;
        case MA_RIGHTX2:
            if (record->event.pressed) {
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
            }
            return false;
        case MA_DELX2:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
            }
            return false;
        case MA_ENTX2:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
            }
            return false;
        case MA_BSPCX2:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbW(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMBW:
            if (!(record->event.pressed)) {
                if (IS_LAYER_ON(LA_MOUSE)) {isMouseX4Started = false;}
                else {layer_off(LA_LTHUMBW);}
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
            }
            return false;
    }
    return true;
}

