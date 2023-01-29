# QMK Configurator에 기본 키맵 추가하기 :id=adding-default-keymaps

이 페이지에서는 QMK Configurator로 키보드의 기본 키맵을 추가하는 방법을 다룹니다.

## 기술적 정보 :id=technical-information

QMK Configurator는 JSON을 키맵의 네이티브 파일 포맷으로 사용합니다. 가능한, 이들은 `qmk_firmware`에서 `make <keyboard>:default`를 실행하는 것과 동일하게 작동하도록 유지되어야 합니다.

이 디렉토리에 있는 키맵들은 4가지의 키값 쌍을 요구합니다:

* `keyboard` (string)
  * 이것은 키보드의 이름이며, `make`로 컴파일 작업을 실행할 때 사용되는 것과 동일합니다. (e.g. `make 1upkeyboards/1up60rgb:default`).
* `keymap` (string)
  * `default`로 설정되어야 합니다.
* `layout` (string)
  * 이것은 기본 키맵에서 사용되는 레이아웃 매크로 입니다.
* `layers` (array)
  * 키맵 그자체. 이 키는 레이어당 하나의 배열을 포함해야 하며, 그 자체로 해당 레이어를 구성하는 키코드를 포함되어야 합니다.

또한, 대부분의 키맵들이 `commit` 키를 담고 있습니다. 이 키는 QMK Configurator를 백스톱하는 API에서 사용되지 않고, Configurator의 유지 관리자가 어떠한 버전의 키맵이 이 리포지토리 안의 JSON 키맵을 생성하는 데 사용되었는 지 알려줍니다. 이 키값은 `qmk_firmware` 리포지토리의 보드의 기본 `keymap.c`를 수정하기 위한 최근 커밋된 SHA 입니다. 이 SHA는 [`마스터` 브랜치의 `qmk/qmk_firmware` 리포지토리](https://github.com/qmk/qmk_firmware/tree/master/)를 체크아웃 하고 `git log -1 --pretty=oneline -- keyboards/<keyboard>/keymaps/default/keymap.c` (문제의 키보드가 이 파일을 대신 가지고 있다고 한다면 `keymap.json`을 사용하세요) 실행하여 찾아지는데, 이와 비슷한 것으로 리턴해야 합니다:

```
f14629ed1cd7c7ec9089604d64f29a99981558e8 Remove/migrate action_get_macro()s from default keymaps (#5625)
```

이 에제에서는, `f14629ed1cd7c7ec9089604d64f29a99981558e8` 는 `commit`을 위해 사용되어야 하는 값입니다.


## 예제 :id=example

이를테면 누군가가 Hineybush의 H87a의 기본 키맵을 추가하길 바란다고 하겠습니다. 그러면 `qmk_firmware`에 있는 H87a의 기본 키맵에 대해 조금 전 명령어인 `git log`를 실행할 것입니다:

```
user ~/qmk_firmware (master)
$ git log -1 --pretty=oneline master -- keyboards/hineybush/h87a/keymaps/default/keymap.c
ef8878fba5d3786e3f9c66436da63a560cd36ac9 Hineybush h87a lock indicators (#8237)
```

이제 커밋 해쉬값을 가지고 있으므로, 키맵이 필요합니다. (가독성을 위해 편집됨):

```c
...
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all(
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,              KC_PSCR, KC_SCRL, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_END,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_TRNS,                      KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RGUI, KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT),

  [1] = LAYOUT_all(
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,             BL_TOGG, BL_DEC,  BL_INC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_MPLY, KC_MNXT, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS),

};
```

기본 키맵은 `LAYOUT_all` 매크로를 사용하고 있으므로, `layout`키의 값이 될 것입니다. QMK Configurator에 JSON 키맵을 컴파일하면, 결과 파일은 다음이어야 합니다:

```json
{
  "keyboard": "hineybush/h87a",
  "keymap": "default",
  "commit": "ef8878fba5d3786e3f9c66436da63a560cd36ac9",
  "layout": "LAYOUT_all",
  "layers": [
    [
      "KC_ESC",             "KC_F1",   "KC_F2",   "KC_F3",   "KC_F4",   "KC_F5",   "KC_F6",   "KC_F7",   "KC_F8",   "KC_F9",   "KC_F10",  "KC_F11",  "KC_F12",                "KC_PSCR", "KC_SCRL", "KC_PAUS",
      "KC_GRV",  "KC_1",    "KC_2",    "KC_3",    "KC_4",    "KC_5",    "KC_6",    "KC_7",    "KC_8",    "KC_9",    "KC_0",    "KC_MINS", "KC_EQL",  "KC_BSPC", "KC_BSPC",    "KC_INS",  "KC_HOME", "KC_PGUP",
      "KC_TAB",  "KC_Q",    "KC_W",    "KC_E",    "KC_R",    "KC_T",    "KC_Y",    "KC_U",    "KC_I",    "KC_O",    "KC_P",    "KC_LBRC", "KC_RBRC", "KC_BSLS",               "KC_DEL",  "KC_END",  "KC_PGDN",
      "KC_CAPS", "KC_A",    "KC_S",    "KC_D",    "KC_F",    "KC_G",    "KC_H",    "KC_J",    "KC_K",    "KC_L",    "KC_SCLN", "KC_QUOT", "KC_NUHS", "KC_ENT",
      "KC_LSFT", "KC_NUBS", "KC_Z",    "KC_X",    "KC_C",    "KC_V",    "KC_B",    "KC_N",    "KC_M",    "KC_COMM", "KC_DOT",  "KC_SLSH", "KC_RSFT", "KC_TRNS",                          "KC_UP",
      "KC_LCTL", "KC_LGUI", "KC_LALT",                                  "KC_SPC",                                   "KC_RALT", "MO(1)",   "KC_RGUI", "KC_RCTL",               "KC_LEFT", "KC_DOWN", "KC_RGHT"
    ],
    [
      "KC_TRNS",            "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "RGB_TOG", "RGB_MOD", "RGB_HUD", "RGB_HUI", "RGB_SAD", "RGB_SAI", "RGB_VAD", "RGB_VAI",               "BL_TOGG", "BL_DEC",  "BL_INC",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",    "KC_TRNS", "KC_TRNS", "KC_VOLU",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "RESET",   "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_MPLY", "KC_MNXT", "KC_VOLD",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",                          "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS",                                  "KC_TRNS",                                  "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_TRNS", "KC_TRNS", "KC_TRNS"
    ]
  ]
}
```

`layers` 배열안의 공란은 키맵 기능에 아무런 영향을 끼치지 않으며, 이는 이러한 파일들을 사람이 쉽게 읽을 수 있도록 하기 위함입니다.


## 주의사항들 :id=caveats

### 레이어는 숫자로만 참조할 수 있음 :id=layer-references

일반적인 QMK 규약은 일련의 `#define`또는 `enum`문의 열을 사용해 이름을 지어주는 것입니다:

```c
enum layer_names {
    _BASE,
    _MEDIA,
    _FN
};
```

C언어에서는 이 코드가 작동하지만, Configurator에서는 *반드시* 레이어의 숫자 인덱스를 사용하야 합니다 – 위의 예제에서, `MO(_FN)`은 `MO(2)`이어야 합니다.

### 어떠한 종류의 커스텀 코드도 지원하지 않음 :id=custom-code

keymap.c 파일에 추가되는 기능이 요구되는 경우, 이를테면 Tap Dance 또는 유니코드 같은 것들은 **전혀** Configurator에서 컴파일되지 않습니다. 키보드 레벨의 `qmk_firmware`리포지토리 안에 있는 `TAP_DANCE_ENABLE = yes`를 설정하더라도 Configurator가 해당 키보드의 **어떠한** 펌웨어를 컴파일하는 것을 막을 것입니다. 이는 API와 현재 JSON 키맵 형식의 스펙의 한계로 인해 제한되고 있습니다.

### 커스텀 키코드의 제한적 지원 :id=custom-keycodes

커스텀 키코드를 지원하는 한가지 방법이 있습니다: 커스텀 키코드의 로직이 qmk_firmware안의 키맵 레벨 대신 키보드 레벨에서 구현된다면, 저 키코드는 Configurator에서 사용 *될 수 있을 것*이고 컴파일 및 작동이 *될 것*입니다. 다음의 예제의 `keymap.c`에서:

```c
enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3
};
...
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return true;
};
```

... 이를 사용하는 대신 해당 키보드의 헤더 파일 (`<keyboard>.h`)를 다음과 같이 `enum` 블록에 키코드를 추가합니다 (참고로 여기서 `enum`은 `keyboard_keycodes`으로 명명합니다):

```c
enum keyboard_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3,
    NEW_SAFE_RANGE  // Important!
};
```

... 그리고 로직은 `<keyboard>.c`의 `process_record_kb()`으로:

```c
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return process_record_user(keycode, record);
};
```

여기서 끝부분에 `process_record_user()`를 불러옵니다. 추가적으로, 이러한 키보드 사용자들은 키보드에서 제공하는 것을 넘어 키맵 레벨에서 고유 커스텀 키 코드를 추가하길 원한다면, `SAFE_RANGE`대신 `NEW_SAFE_RANGE`를 사용해야 할 것입니다.


## 더 읽어보기 :id=additional-reading

QMK Configurator가 키보드를 지원하려면, 키보드가 반드시 `qmk_firmware` 리포지토리의 `master` 브랜치에 있어야 합니다. 이 안내사항과 관련하여, [QMK Configurator에서 키보드 지원](reference_configurator_support.md)를 살펴보세요.
