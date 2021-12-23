# My 34 keys layout

This are my principles for layout:

* I am using Callum style layout. Here you can read explanation by
  Callum himself and his reasoning for not using mod-tap:
  [here](../../../../users/callum/readme.md)

* There should be only one way to type key. Key can be on
  different layer but it must maintain its physical location.

* The less features are used the better.

* trilayer is cool.

* There is 🐍 key for no reason.

As well I have added one shot layers compatible with Callum's one
shot keys.

There is simple TMUX layer as well.








bool a_active = false;
uint16_t a_timer = 0;


    if (keycode == KC_A && record->event.pressed) {
        a_active = true;
        a_timer = timer_read();
        return false;
    }


void matrix_scan_user(void) { // The very important timer.
  if (a_active) {
    if (timer_elapsed(a_timer) > 30) {
      register_code(KC_A);
      a_active = false;
    }
  }
}
