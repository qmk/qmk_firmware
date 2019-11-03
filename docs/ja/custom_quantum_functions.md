# キーボードの挙動をカスタマイズする方法

多くの人にとって、カスタム キーボードはボタンを押すことをコンピュータに送信するだけではありません。単純なボタンの押下やマクロよりも複雑なことを実行できるようにしたいです。QMKにはコードを挿入したり、機能を上書きしたり、様々な状況でキーボードの挙動をカスタマイズしたりできるフックがあります。

このページでは、QMKに関する特別な知識は想定していませんが、[QMKの理解](understanding_qmk.md)を読むとより根本的なレベルで何が起きているかを理解するのに役立ちます。

## A Word on Core vs Keyboards vs Keymap

QMKを階層として構造化しました:

* コア (`_quantum`)
   * キーボード/リビジョン (`_kb`)
      * キーマップ (`_user`)

以下で説明される各関数は `_kb()` サフィックスあるいは `_user()` サフィックスを使って定義することができます。キーボード/リビジョン レベルで`_kb()` サフィックスを使うことを意図しており、一方でキーマップ レベルでは `_user()`サフィックスが使われるべきです。

キーボード/リビジョン レベルで関数を定義する場合、他の何かを呼び出す前に`_kb()`の実装が `_user()` を呼び出すことが重要です。そうでなければ、キーマップ レベル関数は呼ばれないでしょう。

# カスタム キーコード

最も一般的なタスクは、既存のキーコードの挙動を変更するか、新しいキーコードを作成することです。コードの観点からは、それぞれの仕組みは非常に似ています。

## 新しいキーコードの定義

独自のカスタム キーコードを作成する最初のステップは、それらを列挙することです。これは、それらに名前を付け、そのキーコードにユニークな番号を割り当てることを意味します。カスタムキーコードを固定範囲の数字に制限するのではなく、QMKは `SAFE_RANGE`マクロを提供します。カスタムキーコードを列挙する時に `SAFE_RANGE` を使うと、ユニークな番号を取得することが保証されます。


これは2つのキーコードを列挙する例です。このブロックを`keymap.c`に追加した後で、キーマップの中で`FOO` と `BAR` を使うことができます。

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## 任意のキーコードの挙動のプログラミング

既存のキーの挙動を上書きしたい場合、あるいは新しいキーについて挙動を定義する場合、`process_record_kb()` および `process_record_user()` 関数を使うべきです。これらは実際のキーイベントが処理される前のキー処理中にQMKによって呼び出されます。これらの関数が `true` を返す場合、QMKはキーコードを通常通りに処理します。これは、キーを置き換えるのではなく、キーの機能を拡張するのに便利です。これらの関数が `false` を返す場合、QMK は通常のキー処理をスキップします。必要なキーのアップまたはダウンイベントを送信するのはユーザ次第です。

これらの関数はキーが押されるか放されるたびに呼び出されます。

### 例 `process_record_user()` の実装

この例は2つの事を行います。`FOO`と呼ばれるカスタム キーコードの挙動を定義し、押されるたびに音を再生することでEnterキーを補完します。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 押された時に何かをします
      } else {
        // 放された時に何かをします
      }
      return false; // このキー以降の処理をスキップします
    case KC_ENTER:
      // enterが押された時に音を再生します
      if (record->event.pressed) {
        PLAY_NOTE_ARRAY(tone_qwerty);
      }
      return true; // QMKにenterのプレス/リリース イベントを送信させます
    default:
      return true; // 他の全てのキーコードを通常通りに処理します
  }
}
```

### `process_record_*` 関数のドキュメント

* キーボード/リビジョン: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* キーマップ: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

`keycode` 引数はキーマップで定義されているものです。例えば `MO(1)`, `KC_L` など。これらのイベントを処理するには`switch...case`ブロックを使うべきです。

`record` 引数は実際のプレスに関する情報を含みます:

```c
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

# LED 制御

QMKはHID仕様の一部として定義されている5つのLEDの読み取るメソッドを提供します:

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`

これら5つの定数は、ホストLEDの状態の位置ビットに対応します。
ホストLEDの状態を取得するには2つの方法があります:

* `led_set_user()`の実装
* `host_keyboard_leds()`の呼び出し

## `led_set_user()`

この関数はこれら5つのLEDの1つの状態が変化すると呼ばれます。LEDの状態をパラメータとして受け取ります。
LEDの状態を調べるには、`IS_LED_ON(usb_led, led_name)` および `IS_LED_OFF(usb_led, led_name)`マクロを使ってください。

!> `host_keyboard_leds()` は`led_set_user()`が呼ばれる前に新しい値を既に反映している場合があります。

### 例 `led_set_user()` の実装

```c
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(B0);
    } else {
        writePinHigh(B0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B1);
    } else {
        writePinHigh(B1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(B2);
    } else {
        writePinHigh(B2);
    }
    if (IS_LED_ON(usb_led, USB_LED_COMPOSE)) {
        writePinLow(B3);
    } else {
        writePinHigh(B3);
    }
    if (IS_LED_ON(usb_led, USB_LED_KANA)) {
        writePinLow(B4);
    } else {
        writePinHigh(B4);
    }
}
```

### `led_set_*` 関数のドキュメント

* キーボード/リビジョン: `void led_set_kb(uint8_t usb_led)`
* キーマップ: `void led_set_user(uint8_t usb_led)`

## `host_keyboard_leds()`

最後に受信したLEDの状態を取得するためにこの関数を呼びます。これは`led_set_*`外のLEDの状態を読み取るのに便利です。例えば [`matrix_scan_user()`](#matrix-scanning-code)。
便宜のため、直接`host_keyboard_leds()`を調べる代わりに`IS_HOST_LED_ON(led_name)` と `IS_HOST_LED_OFF(led_name)` マクロを使うことができます。

## 物理的なLEDの状態の設定

一部のキーボードは物理的なLEDの状態設定するために便利なメソッドを提供します。

### Ergodox Boards

Ergodoxの実装は、個々のLEDをオンあるいはオフにするために`ergodox_right_led_1`/`2`/`3_on`/`off()`と、インデックスによってそれらをオンあるいはオフにするために`ergodox_right_led_on`/`off(uint8_t led)`を提供します。

さらに、`ergodox_led_all_set(uint8_t n)`を使って全てのLEDの輝度を指定することができます; `ergodox_right_led_1`/`2`/`3_set(uint8_t n)` を使って個々のLED; `ergodox_right_led_set(uint8_t led, uint8_t n)`を使ってインデックスによるもの。

Ergodox boards は最低の輝度に`LED_BRIGHTNESS_LO`を、最高の輝度(これはデフォルトです)に`LED_BRIGHTNESS_HI` も定義します。

# キーボードの初期化コード

キーボードの初期化プロセスには幾つかのステップがあります。何をしたいかによって、どの関数を使うべきかに影響します。

3つの主な初期化関数があり、呼び出される順番にリストされています。

* `keyboard_pre_init_*` - ほとんどのものが開始される前に発生します。非常に速く実行したいハードウェアのセットアップに適しています。
* `matrix_init_*` - ファームウェアのスタートアップ プロセスの途中で発生します。ハードウェアは初期化されますが、機能はまだ無いかもしれません。
* `keyboard_post_init_*` - ファームウェアのスタートアップ プロセスの最後に発生します。これはほとんどの場合、 "カスタマイズ" コードを配置する場所です。

!> ほとんどの人にとって、`keyboard_post_init_user` が呼び出したいものです。例えば、RGBアンダーグローのセットアップを行います。

## キーボードの事前初期化コード

これはUSBさえ起動する前の、起動中の非常に早い段階で実行されます。

この直後にマトリックスが初期化されます。

ほとんどのユーザにとって、これは主にハードウェア向きの初期化のためであるため、使うべきではありません。

ただし、初期化が必要なハードウェアがある場合には、これが最適な場所です (LEDピンの初期化など)。

### 例 `keyboard_pre_init_user()` の実装

この例は、キーボードレベルで、LEDピンとして B0, B1, B2, B3 および B4 をセットアップします。

```c
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
  setPinOutput(B3);
  setPinOutput(B4);
}
```

### `keyboard_pre_init_*` 関数のドキュメント

* キーボード/リビジョン: `void keyboard_pre_init_kb(void)`
* キーマップ: `void keyboard_pre_init_user(void)`

## マトリックスの初期化コード

これはマトリックスが初期化され、ハードウェアの一部がセットアップされた後で、ただし機能の多くが初期化される前に、呼び出されます。

これは、他の場所で必要になるかもしれないものをセットアップするのに役立ちますが、ハードウェアに関連するものではなく、開始場所に依存するものでもありません。


### `matrix_init_*` 関数のドキュメント

* キーボード/リビジョン: `void matrix_init_kb(void)`
* キーマップ: `void matrix_init_user(void)`


## キーボードの事後初期化コード

これはキーボードの初期化プロセスの極めて最後のタスクとして実行されます。これは、特定の機能を変更したい場合に便利です。この時点で初期化される必要があるからです。


### 例 `keyboard_post_init_user()` の実装

他の全てのものが初期化された後で実行されるこの例は、rgbアンダーグローの設定をセットアップします。

```c
void keyboard_post_init_user(void) {
  // post initコードを呼びます
  rgblight_enable_noeeprom(); // 設定を保存せずにRgbを有効にします
  rgblight_sethsv_noeeprom(180, 255, 255); // 保存せずに色を青緑/シアンに設定します
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // 保存せずにモードを高速なブレスに設定します
}
```

### `keyboard_post_init_*` 関数のドキュメント

* キーボード/リビジョン: `void keyboard_post_init_kb(void)`
* キーマップ: `void keyboard_post_init_user(void)`

# マトリックス スキャン コード

可能であれば常に`process_record_*()` を使ってキーボードをカスタマイズし、その方法でイベントをフックし、コードがキーボードのパフォーマンスに悪影響を与えないようにします。ただし、まれにマトリックス スキャンにフックする必要があります。これらの関数は1秒あたり少なくとも10回は呼び出されるため、これらの関数のコードのパフォーマンスに非常に注意してください。

### 例 `matrix_scan_*` の実装

この例は意図的に省略されています。このようなパフォーマンスに敏感な領域にフックする前に、例を使わずにこれを書くために、QMK内部について十分理解する必要があります。助けが必要であれば、[issueを開く](https://github.com/qmk/qmk_firmware/issues/new) か [Discordで会話](https://discord.gg/Uq7gcHh)してください。

### `matrix_scan_*` 関数のドキュメント

* キーボード/リビジョン: `void matrix_scan_kb(void)`
* キーマップ: `void matrix_scan_user(void)`

この関数は全てのマトリックス スキャンで呼び出されます。これは基本的にMCUが処理できる頻度です。ここに何を置くかに注意してください。大量に実行されるからです。

カスタム マトリックス スキャン コードが必要な場合は、この関数を使う必要があります。また、カスタム ステータス出力(LEDあるいはディスプレイなど)や、ユーザが入力していない場合でも定期的にトリガーするその他の機能のために使うことができます。


# キーボード アイドリング/ウェイク コード

ボードがサポートしている場合、多くの機能を停止することで "アイドル"にすることができます。これの良い例は、RGBライトあるいはバックライトです。これにより、電力消費を節約できるか、キーボードの動作が改善されるかもしれません。

これは2つの関数によって制御されます: `suspend_power_down_*` および `suspend_wakeup_init_*`。これらはそれぞれ システム ボードがアイドルになった時と、起動した時に呼ばれます。


### 例 suspend_power_down_user() と suspend_wakeup_init_user() の実装


```c
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
```

### キーボード suspend/wake 関数のドキュメント

* キーボード/リビジョン : `void suspend_power_down_kb(void)` および `void suspend_wakeup_init_user(void)`
* キーマップ: `void suspend_power_down_kb(void)` および `void suspend_wakeup_init_user(void)`

# レイヤ変更コード

これはレイヤが変更されるたびにコードを実行します。これはレイヤ表示あるいはカスタム レイヤ処理に役立ちます。

### 例 `layer_state_set_*` の実装

この例は、Planckを例として使って、レイヤに基づいて[RGB アンダーグロー](feature_rgblight.md) を設定する方法を示します。

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case _PLOVER:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case _ADJUST:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    default: //  他の全てのレイヤあるいはデフォルトのレイヤ
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```
### `layer_state_set_*` 関数のドキュメント

* キーボード/リビジョン: `layer_state_t layer_state_set_kb(layer_state_t state)`
* キーマップ: `layer_state_t layer_state_set_user(layer_state_t state)`


[キーマップの概要](keymap.md#keymap-layer-status)で説明されるように、`state` はアクティブなレイヤのビットマスクです。


# 永続的な設定 (EEPROM)

これによりキーボードのための永続的な設定を設定することができます。これらの設定はコントローラのEEPROMに保存され、電源が喪失した後であっても保持されます。設定は`eeconfig_read_kb` および `eeconfig_read_user`を使って読み込むことができ、`eeconfig_update_kb` および `eeconfig_update_user`を使って書きこむことができます。これは切り替え可能な機能(rgbレイヤの表示の切り替えなど)に役立ちます。さらに、`eeconfig_init_kb` および `eeconfig_init_user` を使ってEEPROMのデフォルト値を設定できます。

ここでの複雑な部分は、EEPROMを介してデータを保存およびアクセスできる方法がたくさんあり、これを行うための"正しい"方法が無いということです。ただし、各関数には DWORD (4 バイト)しかありません。

EEPROMの書き込み回数には制限があることに注意してください。これは非常に高い値ですが、EEPROMに書き込むのはこれだけではなく、もし頻繁に書き込むと、MCUの寿命を大幅に短くする可能性があります。

* この例を理解していない場合は、この機能はかなり複雑なため、この機能を使うことをさけることができます。

### 実装の例

これは、設定を追加し、読み書きする例です。ここの例では、ユーザ キーマップを使っています。これは複雑な機能で、多くのことが行われています。実際、動作のために上記の多くの関数を使います！


keymap.c ファイルの中で、先頭にこれを追加します:
```c
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;
```

これは、設定をメモリ内に保存し、EEPROMに書き込むことができる32ビット構造体をセットアップします。これを使うと、この構造体に変数が定義されるため、変数を定義する必要が無くなります。`bool` (boolean) の値は1ビットを使い、`uint8_t`は8ビットを使い、`uint16_t`は16ビットまでを使うことに注意してください。組み合わせて使うことができますが、順番の変更は読み書きされる値が変更されるため、問題が発生するかもしれません。

`layer_state_set_*`関数のために`rgb_layer_change`を使い、全てを設定するために`keyboard_post_init_user`および `process_record_user`を使います。

ここで、上の`keyboard_post_init_user`コードを使って、作成したばかりの構造体を設定するために`eeconfig_read_user()`を追加します。そして、この構造体をすぐに使ってキーマップの機能を制御することができます。それは以下のようになります:
```c
void keyboard_post_init_user(void) {
  // キーマップ レベルのマトリックスのinitを呼びます

  // EEPROMからユーザ設定を読み込みます
  user_config.raw = eeconfig_read_user();

  // 有効な場合はデフォルトレイヤを設定します
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan();
    rgblight_mode_noeeprom(1);
  }
}
```
上記の関数は読み取ったばかりのEEPROM設定を使い、デフォルトのレイヤのRGB色を設定します。その"生の"値は、上で作成した"union"に基づいて使用可能な構造に変換されます。

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); }
        break;
    case _LOWER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case _PLOVER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
        break;
    case _ADJUST:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    default: //  他の全てのレイヤあるいはデフォルトのレイヤ
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
```
これにより、値が有効になっていた場合のみRGBアンダーグローが変更されます。この値を設定するために、`RGB_LYR`と呼ばれる`process_record_user`の新しいキーコードを作成します。さらに、通常のRGBコードを使う場合、上記の例を使ってオフにすることを確認します。以下のようになります:
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 押された時に何かをします
      } else {
        // 放された時に何かをします
      }
      return false; // このキー以降の処理をスキップします
    case KC_ENTER:
        // enterが押された時に音を再生します
        if (record->event.pressed) {
            PLAY_NOTE_ARRAY(tone_qwerty);
        }
        return true; // QMKにenterのプレス/リリース イベントを送信させます
    case RGB_LYR:  // これにより、アンダーグローをレイヤ表示として、あるいは通常通りに使うことができます。
        if (record->event.pressed) {
            user_config.rgb_layer_change ^= 1; // 状態を切り替えます
            eeconfig_update_user(user_config.raw); // 新しい状態をEEPROMに書き込みます
            if (user_config.rgb_layer_change) { // レイヤの状態表示が有効な場合
                layer_state_set(layer_state);   // すぐにレイヤの色を更新します
            }
        }
        return false; break;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // 任意のRGBコード (quantum_keycodes.h を見てください。参照としては L400)
        if (record->event.pressed) { // これはレイヤ表示を無効にします。これを変更する場合は、無効にしたいだろうため。
            if (user_config.rgb_layer_change) {        // 有効な場合のみ
                user_config.rgb_layer_change = false;  // 無効にします
                eeconfig_update_user(user_config.raw); // 設定をEEPROMに書き込みます
            }
        }
        return true; break;
    default:
      return true; // 他の全てのキーコードを通常通りに処理します
  }
}
```
最後に、`eeconfig_init_user`関数を追加して、EEPROMがリセットされた時にデフォルト値、さらにはカスタム アクションを指定できるようにします。EEPROMを強制的にリセットするには、`EEP_RST` キーコードあるいは[Bootmagic](feature_bootmagic.md)機能を使います。例えば、デフォルトでrgbレイヤ表示を設定し、デフォルト値を保存したい場合。

```c
void eeconfig_init_user(void) {  // EEPROMがリセットされます！
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // デフォルトでこれを有効にします
  eeconfig_update_user(user_config.raw); // デフォルト値をEEPROMに書き込みます

  // noeeprom以外のバージョンを使って、これらの値もEEPROMに書き込みます
  rgblight_enable(); // デフォルトでRGBを有効にします
  rgblight_sethsv_cyan();  // デフォルトでCYANに設定します
  rgblight_mode(1); // デフォルトでソリッドに設定します
}
```

これで完了です。RGBレイヤ表示は必要な場合にのみ機能します。ボードを取り外した後でも保存されます。RGBコードのいずれかを使うと、レイヤ表示が無効になり、設定したモードと色がそのままになります。

### 'EECONFIG' 関数のドキュメント

* キーボード/リビジョン: `void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)` および `void eeconfig_update_kb(uint32_t val)`
* キーマップ: `void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)` および `void eeconfig_update_user(uint32_t val)`

`val` はEEPROMに書き込みたいデータの値です。`eeconfig_read_*`関数はEEPROMから32ビット(DWORD)値を返します。

# カスタム タッピング期間

デフォルトでは、タッピング期間はグローバルに設定されていて、キーでは設定することができません。ほとんどのユーザにとって、これは全然問題ありません。しかし、場合によっては、`LT`キーとは異なるタイムアウトによって、または一部のキーは他のキーよりも保持しやすいため、デュアル ファンクション キーが大幅に改善されます。それぞれにカスタム キー コードを使う代わりに、これによりキーごとに設定可能な `TAPPING_TERM` を可能にします。

この機能を有効にするには、最初に`config.h`に`#define TAPPING_TERM_PER_KEY`を追加する必要があります。


## 例 `get_tapping_term` の実装

キーコードに基づいて`TAPPING TERM`を変更するには、次のようなものを `keymap.c` ファイルに追加します:

```c
uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case SFT_T(KC_SPC):
      return TAPPING_TERM + 1250;
    case LT(1, KC_GRV):
      return 130;
    default:
      return TAPPING_TERM;
  }
}
```

### `get_tapping_term` 関数のドキュメント

ここにある他の多くの関数とは異なり、quantum あるいはキーボード レベルの関数を持つ必要はありません (または理由さえありません)。ここではユーザ レベルの関数だけが有用なため、そのようにマークする必要はありません。
