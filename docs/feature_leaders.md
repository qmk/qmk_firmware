# Leaders
This feature allows to define key sequences. It is similar to existing
[leader_key](feature_leader_key.md) but with several new
functionalities:

* Unlimited number of leaders (sequence can start from any key).
* The tail of the sequence can be repeated while holding one of the key in the sequence .
* Support on-press and on-release actions.
* Support "wildcard" key in the sequence. This can be useful to define more flexible "layers".


## Enable Leaders

Add to your `rules.mk` in the keymap folder:

   LEADERS_ENABLE = yes

If no `rules.mk` exists, you can create one.

## Sequence definition

To define the sequence, first add start and end of the sequence keycodes to `planck_keycodes`.

```c
enum planck_keycodes {
	QWERTY = SAFE_RANGE,
    ...
    LD_START,
    SEQ_END
    ...
};
```
Then add the sequence definition to `user_definitions`

```c
uint16_t* user_definitions[]  = {
  (uint16_t[]){5, LD_START, KC_A, KC_B, SEQ_END },
  (uint16_t[]){1}
};
```
This example defines a key sequence that starts from `LD_START` keycode, then 2 keys in the positions of =KC_A= and =KC_B= keycodes as they defined on the layer 0.
There are several rules here
1. The last entry in `user_definitions` should always end with `(uint16_t[]){1}`.
2. The first entry in the sequence definition is the number of elements in the array that represent the sequence. (not the number of keys in the sequence). In the example above we have 5 elements in the array but only 3 keys in the sequence.
3. The second element in the sequence is the keycode that is used to start the sequence. (=LD_START= in the example). This keycode should be used in the user `keymaps`.
4. Other keys in the sequence are positions, defined by keycodes on layer 0. Our example defines key sequence that starts from =LD_START=  followed by 2 keys in the positions of =KC_A= and =KC_B= keycodes= on layer 0.
5. There is one exception. =KC_TRNS= keycode represents any key. for example `(uint16_t[]){5, LD_START, KC_A, KC_TRNS, SEQ_END }` represent any key as a last key of the sequence. It can be useful to define layer like functionality. More no this later.
6. More specific key sequence definitions should be place before general one. This example illustrate the idea:
```c
uint16_t* user_definitions[]  = {
  (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_DOUBLERAISE },
  (uint16_t[]){4, LD_RAISE, KC_TRNS, SEQ_RAISE },
};
```
7. Finally the last element of the definition is a keycode that will be used to define actions.

## Initiate definitions

Th next step is to initiate leaders. Just add the following statement after `user_definitions`
```c
void leaders_init_user(void) {
  keyseq_set_definitions(user_definitions);
}
```

## Define actions

The last step is to define on-press and on-release actions for the last keycode in the sequence definition. 

```c
bool keyseq_press_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case SEQ_SYMBOLS:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_SYM, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_SYM, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_RAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_DOUBLERAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      if (kc != KC_NO && record->event.key.row == 0) {
        register_code16(KC_RGUI);
        register_code16(kc);
        unregister_code16(kc);
        unregister_code16(KC_RGUI);
      } else {
        register_code16(kc);
        unregister_code16(kc);
      }
      return false ;
    } else {
      return false;
    }
  case SEQ_IE:
    if (record->event.pressed) {
      SEND_STRING("{}");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_ID:
    if (record->event.pressed) {
      SEND_STRING("()");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_IC:
    if (record->event.pressed) {
      SEND_STRING("[]");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  }
  return false;
}
```

## Notes 
    - `planck/lxol` keymap is my personal keymap where you can see the feature in action.
    - You can press and hold any modifier (except shift) before the sequence.
