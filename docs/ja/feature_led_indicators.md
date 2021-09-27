# LED インジケータ

<!---
  original document: 0.10.52:docs/feature_led_indicators.md
  git diff 0.10.52 HEAD -- docs/feature_led_indicators.md | cat
-->

QMK は HID 仕様で定義された5つの LED の読み取りメソッドを提供します:

* Num Lock
* Caps Lock
* Scroll Lock
* Compose
* Kana

ロック LED の状態を取得するには3つの方法があります:
* `config.h` で設定オプションを指定する
* `bool led_update_kb(led_t led_state)` あるいは `_user(led_t led_state)` を実装する、または
* `led_t host_keyboard_led_state()` を呼び出す

!> `host_keyboard_led_state()` は `led_update_user()` が呼ばれる前に新しい値を既に反映している場合があります。

LED の状態を `uint8_t` として提供する2つの非推奨の関数があります:

* `uint8_t led_set_kb(uint8_t usb_led)` と `_user(uint8_t usb_led)`
* `uint8_t host_keyboard_leds()`

## 設定オプション :id=configuration-options

インジケータを設定するには、`config.h` で以下の `#define` をします:

| 定義                  | 既定値     | 説明                             |
|-----------------------|------------|----------------------------------|
| `LED_NUM_LOCK_PIN`    | *定義なし* | `Num Lock` LED を制御するピン    |
| `LED_CAPS_LOCK_PIN`   | *定義なし* | `Caps Lock` LED を制御するピン   |
| `LED_SCROLL_LOCK_PIN` | *定義なし* | `Scroll Lock` LED を制御するピン |
| `LED_COMPOSE_PIN`     | *定義なし* | `Compose` LED を制御するピン     |
| `LED_KANA_PIN`        | *定義なし* | `Kana` LED を制御するピン        |
| `LED_PIN_ON_STATE`    | `1`        | LED が "オン" の時のインジケータピンの状態 - high の場合は`1`、low の場合は`0` |

独自のキーボードを設計しているわけではない限り、通常は上記の設定オプションを変更する必要はありません。

## `led_update_*()`

設定オプションが十分な柔軟性を提供しない場合は、提供される API フックにより LED の挙動の独自の制御ができます。これらの関数はこれら5つの LED のいずれかの状態が変化すると呼ばれます。LED の状態を構造体のパラメータとして受け取ります。

慣例により、`led_update_kb()` にそのコードを実行するようフックさせるために `led_update_user()` から `true` を返し、`led_update_kb()` でコードを実行したくない場合は `false` を返します。

以下はいくつかの例です:

- レイヤー表示のような何かのために LED を使うために LED を上書きする
   - `_kb()` 関数を実行したくないので、`false`  を返します。これはレイヤーの挙動を上書きするためです。
- LED がオンあるいはオフになった時に音楽を再生する。
   - `_kb` 関数を実行したいので、`true` を返します。これはデフォルトの LED の挙動に追加されます。

?> `led_set_*` 関数は `bool` の代わりに `void` を返すため、キーボードの LED 制御を上書きすることができません。従って、代わりに `led_update_*` を使うことをお勧めします。

### `led_update_kb()` の実装例

```c
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin は 1 でピンを high に、0 で low に設定します。
        // この例では、ピンは反転していて、
        // low/0 は LED がオンになり、high/1 は LED がオフになります。
        // この挙動は、LED がピンと VCC の間にあるか、ピンと GND の間にあるかどうかに依存します。
        writePin(B0, !led_state.num_lock);
        writePin(B1, !led_state.caps_lock);
        writePin(B2, !led_state.scroll_lock);
        writePin(B3, !led_state.compose);
        writePin(B4, !led_state.kana);
    }
    return res;
}
```

### `led_update_user()` の実装例

この不完全な例は Caps Lock がオンまたはオフになった場合に音を再生します。また LED の状態を保持する必要があるため、`true` を返します。

```c
#ifdef AUDIO_ENABLE
  float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
  float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool led_update_user(led_t led_state) {
    #ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
        caps_state = led_state.caps_lock;
    }
    #endif
    return true;
}
```

### `led_update_*` 関数のドキュメント

* キーボード/リビジョン: `bool led_update_kb(led_t led_state)`
* キーマップ: `bool led_update_user(led_t led_state)`

## `host_keyboard_led_state()`

最後に受信した LED の状態を `led_t` として取得するためにこの関数を呼びます。これは、`led_update_*` の外部から、例えば [`matrix_scan_user()`](#matrix-scanning-code) の中で LED の状態を読み取るのに便利です。

## 物理的な LED の状態の設定

一部のキーボードの実装は、物理的な LED の状態を設定するための便利なメソッドを提供しています。

### Ergodox キーボード

Ergodox の実装は、個々の LED をオンあるいはオフにするために `ergodox_right_led_1`/`2`/`3_on`/`off()` と、インデックスによってそれらをオンあるいはオフにするために `ergodox_right_led_on`/`off(uint8_t led)` を提供します。

さらに、LED の明度を指定することができます。全ての LED に同じ明度を指定するなら `ergodox_led_all_set(uint8_t n)` を使い、個別の LED の明度を指定するなら `ergodox_right_led_1`/`2`/`3_set(uint8_t n)` を使い、LED のインデックスを指定して明度を指定するには  `ergodox_right_led_set(uint8_t led, uint8_t n)` を使います。

Ergodox キーボードは、最低の明度として `LED_BRIGHTNESS_LO` を、最高の輝度(これはデフォルトです)として `LED_BRIGHTNESS_HI` も定義しています。
