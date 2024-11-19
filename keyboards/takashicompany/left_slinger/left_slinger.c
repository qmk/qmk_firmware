// #include <stdio.h>
#include "quantum.h"
#include "left_slinger.h"
#include "custom_joystick.h"

#if CONSOLE_ENABLE
#include <print.h>
#endif

/////////////////////////////
/// miniZoneの実装 ここから ///
////////////////////////////

#define MOUSE_SCROLL_V_REVERSE_BIT  (1 << 0) // 0000 0001
#define MOUSE_SCROLL_H_REVERSE_BIT  (1 << 1) // 0000 0010
#define JOYSTICK_KEY_DEFAULT_ENABLE (1 << 2) // 0000 0100

enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
    CLICKING,   // クリック中。 Clicking.
    SCROLLING   // スクロール中。 Scrolling.
};

typedef union {
  uint32_t raw;

  struct {
    // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
    int16_t joystick_ratio;
    int8_t to_clickable_movement;
    uint8_t settings;
  };
} user_config_t;

user_config_t user_config;

enum click_state state;     // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;       // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

// uint16_t to_clickable_time = 50;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
uint16_t to_reset_time = 1000; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const uint16_t click_layer = 6;   // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled
const uint16_t setting_layer = 7;

int16_t scroll_v_mouse_interval_counter;   // 垂直スクロールの入力をカウントする。　Counting Vertical Scroll Inputs
int16_t scroll_h_mouse_interval_counter;   // 水平スクロールの入力をカウントする。  Counts horizontal scrolling inputs.

int16_t scroll_v_threshold = 50;    // この閾値を超える度に垂直スクロールが実行される。 Vertical scrolling is performed each time this threshold is exceeded.
int16_t scroll_h_threshold = 50;    // この閾値を超える度に水平スクロールが実行される。 Each time this threshold is exceeded, horizontal scrolling is performed.

int16_t after_click_lock_movement = 0;      // クリック入力後の移動量を測定する変数。 Variable that measures the amount of movement after a click input.

int16_t mouse_record_threshold = 30;    // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;     // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.

const uint16_t ignore_disable_mouse_layer_keys[] = {KC_LGUI, KC_LCTL};   // この配列で指定されたキーはマウスレイヤー中に押下してもマウスレイヤーを解除しない

int16_t mouse_movement;

bool joystick_key_flag = false;

void eeconfig_init_kb(void) {
    user_config.raw = 0;
    user_config.joystick_ratio = 100;
    user_config.to_clickable_movement = 50;
    // 新しいビットフィールド設定
    
    user_config.settings = 0; // 初期化
    user_config.settings |= MOUSE_SCROLL_V_REVERSE_BIT * false; // ここでfalseなので実際にはセットしない
    user_config.settings |= MOUSE_SCROLL_H_REVERSE_BIT * false; // 同上
    user_config.settings |= JOYSTICK_KEY_DEFAULT_ENABLE * false;
    
    eeconfig_update_kb(user_config.raw);
}

bool get_mouse_scroll_v_reverse(void) {
    return user_config.settings & MOUSE_SCROLL_V_REVERSE_BIT;
}

bool get_mouse_scroll_h_reverse(void) {
    return user_config.settings & MOUSE_SCROLL_H_REVERSE_BIT;
}

void set_mouse_scroll_v_reverse(bool value) {
    if (value) {
        user_config.settings |= MOUSE_SCROLL_V_REVERSE_BIT;
    } else {
        user_config.settings &= ~MOUSE_SCROLL_V_REVERSE_BIT;
    }
}

void set_mouse_scroll_h_reverse(bool value) {
    if (value) {
        user_config.settings |= MOUSE_SCROLL_H_REVERSE_BIT;
    } else {
        user_config.settings &= ~MOUSE_SCROLL_H_REVERSE_BIT;
    }
}

bool get_joystick_key_default_enable(void) {
    return user_config.settings & JOYSTICK_KEY_DEFAULT_ENABLE;
}

void set_joystick_key_default_enable(bool value) {
    if (value) {
        user_config.settings |= JOYSTICK_KEY_DEFAULT_ENABLE;
    } else {
        user_config.settings &= ~JOYSTICK_KEY_DEFAULT_ENABLE;
    }
}

void keyboard_post_init_kb(void) {
    user_config.raw = eeconfig_read_kb();
    joystick_ratio = user_config.joystick_ratio;
}

// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_v_mouse_interval_counter = 0;
    scroll_h_mouse_interval_counter = 0;
}

bool setting_flags[4] = { false, false, false, false };

void enable_setting_layer(void) {
    for (int i = 0; i < 4; i++)
    {
        setting_flags[i] = false;
    }
    layer_on(setting_layer);

    SEND_STRING(" Setting Layer Start.");
}

void disable_setting_layer(void) {

    for (int i = 0; i < 4; i++)
    {
        setting_flags[i] = false;
    }

    layer_off(setting_layer);
    SEND_STRING(" Setting Layer End.");
}

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int8_t my_abs(int8_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

int16_t my_abs_16(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

// 現在クリックが可能な状態か。 Is it currently clickable?
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (record->event.key.row == 0 && record->event.key.col == 0)
    {
        setting_flags[0] = record->event.pressed;
    }

    if (record->event.key.row == 0 && record->event.key.col == 2)
    {
        setting_flags[1] = record->event.pressed;
    }

    if (record->event.key.row == 5 && record->event.key.col == 0)
    {
        setting_flags[2] = record->event.pressed;
    }

    if (record->event.key.row == 5 && record->event.key.col == 2)
    {
        setting_flags[3] = record->event.pressed;
    }

    for (int i = 0; i < 4; i++)
    {
        if (!setting_flags[i])
        {
            break;
        }

        if (i == 3)
        {
            enable_setting_layer();
            return true;
        }
    }


    switch (keycode) {
        case MY_BTN1:
        case MY_BTN2:
        case MY_BTN3:
        {
            report_mouse_t currentReport = pointing_device_get_report();

            // どこのビットを対象にするか。 Which bits are to be targeted?
            uint8_t btn = 1 << (keycode - MY_BTN1);
            
            if (record->event.pressed) {
                // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
                // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
                currentReport.buttons |= btn;
                state = CLICKING;
                after_click_lock_movement = 30;
            } else {
                // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
                // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
                currentReport.buttons &= ~btn;
            }

            enable_click_layer();

            pointing_device_set_report(currentReport);
            pointing_device_send();
            return false;
        }

        case MY_SCRL:
            if (record->event.pressed) {
                state = SCROLLING;
            } else {
                enable_click_layer();   // スクロールキーを離した時に再度クリックレイヤーを有効にする。 Enable click layer again when the scroll key is released.
            }
         return false;
        
        case MY_CLKI:
            if (record->event.pressed) {
                user_config.to_clickable_movement += 5;
                eeconfig_update_kb(user_config.raw);
            }
            return false;

        case MY_CLKD:
            if (record->event.pressed) {

                user_config.to_clickable_movement -= 5;

                if (user_config.to_clickable_movement < 5) {
                    user_config.to_clickable_movement = 5;
                }

                eeconfig_update_kb(user_config.raw);
            }
            return false;
        
        case MY_SCDV:
            if (record->event.pressed) {
                set_mouse_scroll_v_reverse(!get_mouse_scroll_v_reverse());
                eeconfig_update_kb(user_config.raw);
            }
            return false;
        
        case MY_SCDH:
            if (record->event.pressed) {
                set_mouse_scroll_h_reverse(!get_mouse_scroll_h_reverse());
                eeconfig_update_kb(user_config.raw);
            }
            return false;

        case MY_JSDI:
            if  (record->event.pressed) {
                joystick_ratio = joystick_ratio + 5;
                user_config.joystick_ratio = joystick_ratio;
                eeconfig_update_kb(user_config.raw);
            }
            
            break;

        case MY_JSDD:
            if  (record->event.pressed) {
                joystick_ratio = joystick_ratio - 5;
                user_config.joystick_ratio = joystick_ratio;
                eeconfig_update_kb(user_config.raw);
            }
            
            break;

        case MY_STGE:
            if  (record->event.pressed) {
                disable_setting_layer();
            }
            break;
        
        case MY_JSKD:
            if (record->event.pressed) {
                set_joystick_key_default_enable(!get_joystick_key_default_enable());
                eeconfig_update_kb(user_config.raw);
            }
            break;
        
        case MY_JSKE:
            joystick_key_flag = record->event.pressed;
            break;

         default:
            if  (record->event.pressed) {
                
                if (state == CLICKING || state == SCROLLING)
                {
                    enable_click_layer();
                    return false;
                }
                
                for (int i = 0; i < sizeof(ignore_disable_mouse_layer_keys) / sizeof(ignore_disable_mouse_layer_keys[0]); i++)
                {
                    if (keycode == ignore_disable_mouse_layer_keys[i])
                    {
                        enable_click_layer();
                        return true;
                    }
                }

                disable_click_layer();
            }
    }

    return process_record_user(keycode, record);
}

int8_t joystick_key_column = -1;
uint16_t joystick_key_timer;

void reset_joystick_key(void) {
    if (joystick_key_column >= 0) {
        action_exec(MAKE_KEYEVENT(6, joystick_key_column, false));
    }

    joystick_key_column = -1;
}

void press_joystick_key(int8_t column) {

    joystick_key_timer = timer_read();
    
    if (joystick_key_column == column /* || timer_elapsed(joystick_key_timer) < 200*/) {
        return;
    }

    reset_joystick_key();

    joystick_key_column = column;
    joystick_key_timer = timer_read();
    action_exec(MAKE_KEYEVENT(6, column, true));
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    int8_t current_x = mouse_report.x;
    int8_t current_y = mouse_report.y;
    int8_t current_h = 0;
    int8_t current_v = 0;
    
    if (get_joystick_key_default_enable() != joystick_key_flag) {
#ifdef CONSOLE_ENABLE
        uprintf("x: %d, y: %d, raw_x: %d, raw_y: %d \n", current_x, current_y, joystick_raw_x, joystick_raw_y);
#endif
        if ((current_x != 0 || current_y != 0) &&
            (joystick_raw_x > 100 || joystick_raw_y > 100) == false &&
            (my_abs_16(joystick_raw_x) + my_abs_16(joystick_raw_y) > 350)){
           
            if (joystick_raw_y < joystick_raw_x * 4) {
                // 上
                press_joystick_key(1);
            } else if (joystick_raw_x < joystick_raw_y * 5) {
                press_joystick_key(2);
            } else {
                press_joystick_key(0);
            }
        }
        else {
            if (timer_elapsed(joystick_key_timer) > 100) {
                reset_joystick_key();
            }
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.h = 0;
        mouse_report.v = 0;

        return mouse_report;
    }
    else {
        reset_joystick_key();
    }

    if (current_x != 0 || current_y != 0) {
        
        switch (state) {
            case CLICKABLE:
                click_timer = timer_read();
                break;

            case CLICKING:
                after_click_lock_movement -= my_abs(current_x) + my_abs(current_y);

                if (after_click_lock_movement > 0) {
                    current_x = 0;
                    current_y = 0;
                }

                break;

            case SCROLLING:
            {
                int8_t rep_v = 0;
                int8_t rep_h = 0;

                // 垂直スクロールの方の感度を高める。 Increase sensitivity toward vertical scrolling.
                if (my_abs(current_y) * 2 > my_abs(current_x)) {

                    scroll_v_mouse_interval_counter += current_y;
                    while (my_abs(scroll_v_mouse_interval_counter) > scroll_v_threshold) {
                        if (scroll_v_mouse_interval_counter < 0) {
                            scroll_v_mouse_interval_counter += scroll_v_threshold;
                            rep_v += scroll_v_threshold;
                        } else {
                            scroll_v_mouse_interval_counter -= scroll_v_threshold;
                            rep_v -= scroll_v_threshold;
                        }
                        
                    }
                } else {

                    scroll_h_mouse_interval_counter += current_x;

                    while (my_abs(scroll_h_mouse_interval_counter) > scroll_h_threshold) {
                        if (scroll_h_mouse_interval_counter < 0) {
                            scroll_h_mouse_interval_counter += scroll_h_threshold;
                            rep_h += scroll_h_threshold;
                        } else {
                            scroll_h_mouse_interval_counter -= scroll_h_threshold;
                            rep_h -= scroll_h_threshold;
                        }
                    }
                }

                current_h = rep_h / scroll_h_threshold * (get_mouse_scroll_h_reverse() ? -1 : 1);
                current_v = -rep_v / scroll_v_threshold * (get_mouse_scroll_v_reverse() ? -1 : 1);
                current_x = 0;
                current_y = 0;
            }
                break;

            case WAITING:
                /*
                if (timer_elapsed(click_timer) > user_config.to_clickable_time) {
                    enable_click_layer();
                }
                */

                mouse_movement += my_abs(current_x) + my_abs(current_y);

                if (mouse_movement >= user_config.to_clickable_movement)
                {
                    mouse_movement = 0;
                    enable_click_layer();
                }
                break;

            default:
                click_timer = timer_read();
                state = WAITING;
                mouse_movement = 0;
        }
    }
    else
    {
        switch (state) {
            case CLICKING:
            case SCROLLING:

                break;

            case CLICKABLE:
                if (timer_elapsed(click_timer) > to_reset_time) {
                    disable_click_layer();
                }
                break;

             case WAITING:
                if (timer_elapsed(click_timer) > 50) {
                    mouse_movement = 0;
                    state = NONE;
                }
                break;

            default:
                mouse_movement = 0;
                state = NONE;
        }
    }

    mouse_report.x = current_x;
    mouse_report.y = current_y;
    mouse_report.h = current_h;
    mouse_report.v = current_v;

    return mouse_report;
}

/////////////////////////////
/// miniZoneの実装 ここまで ///
////////////////////////////