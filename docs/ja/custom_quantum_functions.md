# キーボードの挙動をカスタマイズする方法

<!---
  original document: 0.12.41:docs/custom_quantum_functions.md
  git diff 0.12.41 HEAD -- docs/custom_quantum_functions.md | cat
-->

多くの人にとって、カスタムキーボードはボタンの押下をコンピュータに送信するだけではありません。単純なボタンの押下やマクロよりも複雑なことを実行できるようにしたいでしょう。QMK にはコードを挿入したり、機能を上書きしたり、様々な状況でキーボードの挙動をカスタマイズできるフックがあります。

このページでは、QMK に関する特別な知識は想定していませんが、[QMK の理解](ja/understanding_qmk.md)を読むとより根本的なレベルで何が起きているかを理解するのに役立ちます。

## コア、キーボード、キーマップ階層 :id=a-word-on-core-vs-keyboards-vs-keymap

私たちは QMK を階層として構造化しました:

* コア (`_quantum`)
   * キーボード/リビジョン (`_kb`)
      * キーマップ (`_user`)

以下で説明される各関数は `_kb()` サフィックスあるいは `_user()` サフィックスを使って定義することができます。`_kb()` サフィックスはキーボード/リビジョンレベルで使うことを意図しており、一方で `_user()` サフィックスはキーマップレベルで使われるべきです。

キーボード/リビジョンレベルで関数を定義する場合、`_kb()` は他の何かを実行する前に `_user()` を呼び出すよう実装することが重要です。そうでなければ、キーマップレベル関数は呼ばれないでしょう。

# カスタムキーコード

最も一般的なタスクは、既存のキーコードの挙動を変更するか、新しいキーコードを作成することです。コードの観点からは、それぞれの仕組みは非常に似ています。

## 新しいキーコードの定義

独自のカスタムキーコードを作成する最初のステップは、それらを列挙することです。これは、カスタムキーコードに名前を付け、そのキーコードにユニークな番号を割り当てることの両方を意味します。QMK は、カスタムキーコードを固定範囲の番号に制限するのではなく、`SAFE_RANGE` マクロを提供します。カスタムキーコードを列挙する時に `SAFE_RANGE` を使うと、ユニークな番号を取得することが保証されます。


これは2つのキーコードを列挙する例です。このブロックを `keymap.c` に追加した後で、キーマップの中で `FOO` と `BAR` を使うことができます。

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## 任意のキーコードの挙動のプログラミング :id=programming-the-behavior-of-any-keycode

既存のキーの挙動を上書きしたい場合、あるいは新しいキーについて挙動を定義する場合、`process_record_kb()` および `process_record_user()` 関数を使うべきです。これらは実際のキーイベントが処理される前のキー処理中に QMK によって呼び出されます。これらの関数が `true` を返す場合、QMK はキーコードを通常通りに処理します。これは、キーを置き換えるのではなく、キーの機能を拡張するのに便利です。これらの関数が `false` を返す場合、QMK は通常のキー処理をスキップし、必要なキーのアップまたはダウンイベントを送信するのかはユーザ次第です。

これらの関数はキーが押されるか放されるたびに呼び出されます。

### `process_record_user()` の実装例

この例は2つの事を行います。`FOO` と呼ばれるカスタムキーコードの挙動を定義し、Enter キーが押されるたびに音を再生します。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 押された時に何かをします
      } else {
        // 放された時に何かをします
      }
      return false; // このキーの以降の処理をスキップします
    case KC_ENTER:
      // enter が押された時に音を再生します
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
      }
      return true; // QMK に enter のプレスまたはリリースイベントを送信させます
    default:
      return true; // 他の全てのキーコードを通常通りに処理します
  }
}
```

### `process_record_*` 関数のドキュメント

* キーボード/リビジョン: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* キーマップ: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

`keycode` 引数はキーマップで定義されているものです。例えば `MO(1)`、`KC_L` など。これらのイベントを処理するには `switch...case` ブロックを使うべきです。

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

# キーボードの初期化コード

キーボードの初期化プロセスには幾つかのステップがあります。何をしたいかによって、どの関数を使うべきかに影響します。

3つの主な初期化関数があり、呼び出される順番にリストされています。

* `keyboard_pre_init_*` - ほとんどのものが開始される前に起こります。非常に早くに実行したいハードウェアのセットアップに適しています。
* `matrix_init_*` - ファームウェアのスタートアッププロセスの途中で起こります。ハードウェアは初期化されますが、機能はまだ初期化されていない場合があります。
* `keyboard_post_init_*` - ファームウェアのスタートアッププロセスの最後に起こります。これはほとんどの場合、 "カスタマイズ"コードを配置する場所です。

!> ほとんどの人にとって、`keyboard_post_init_user` が呼び出したいものです。例えば、ここで RGB アンダーグローのセットアップを行います。

## キーボードの事前初期化コード

これは USB さえ起動する前の、起動中の非常に早い段階で実行されます。

この直後にマトリックスが初期化されます。

これは主にハードウェア向きの初期化のためであるため、ほとんどのユーザは使うべきではありません。

ただし、初期化が必要なハードウェアがある場合には、これが最適な場所です (LED ピンの初期化など)。

### `keyboard_pre_init_user()` の実装例

この例は、キーボードレベルで、LED ピンとして B0、B1、B2、B3 および B4 をセットアップします。

```c
void keyboard_pre_init_user(void) {
  // キーボードの事前初期コードを呼び出します。

  // LED ピンを出力として設定します
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
  setPinOutput(B3);
  setPinOutput(B4);
}
```

### `keyboard_pre_init_*` 関数のドキュメント :id=keyboard_pre_init_-function-documentation

* キーボード/リビジョン: `void keyboard_pre_init_kb(void)`
* キーマップ: `void keyboard_pre_init_user(void)`

## マトリックスの初期化コード

これは、マトリックスが初期化され、ハードウェアの一部がセットアップされた後で、ただし機能の多くが初期化される前に、呼び出されます。

他の場所で必要になるかもしれないものをセットアップするのに役立ちますが、ハードウェアに関連するものではなく、開始場所に依存するものでもありません。


### `matrix_init_*` 関数のドキュメント

* キーボード/リビジョン: `void matrix_init_kb(void)`
* キーマップ: `void matrix_init_user(void)`


## キーボードの事後初期化コード

キーボードの初期化プロセスの極めて最後のタスクとして実行されます。この時点で初期化される必要があるような、特定の機能を変更したい場合に便利です。


### `keyboard_post_init_user()` の実装例

この例は、他の全てのものが初期化された後で実行され、rgb アンダーグローの設定をセットアップします。

```c
void keyboard_post_init_user(void) {
  // post init コードを呼びます
  rgblight_enable_noeeprom(); // 設定を保存せずに Rgb を有効にします
  rgblight_sethsv_noeeprom(180, 255, 255); // 保存せずに色を青緑/シアンに設定します
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // 保存せずにモードを高速なブリージングに設定します
}
```

### `keyboard_post_init_*` 関数のドキュメント

* キーボード/リビジョン: `void keyboard_post_init_kb(void)`
* キーマップ: `void keyboard_post_init_user(void)`

# マトリックススキャンコード :id=matrix-scanning-code

可能であれば常に `process_record_*()` を使ってキーボードをカスタマイズし、その方法でイベントをフックし、コードがキーボードのパフォーマンスに悪影響を与えないようにします。ただし、まれにマトリックススキャンにフックする必要があります。これらの関数は1秒あたり少なくとも10回は呼び出されるため、これらの関数のコードのパフォーマンスに非常に注意してください。

### `matrix_scan_*` の実装例

この例は意図的に省略されています。このようなパフォーマンスに敏感な領域にフックする前に、例を使わずにこれを書くために、QMK 内部について十分理解する必要があります。助けが必要であれば、[issue を開く](https://github.com/qmk/qmk_firmware/issues/new) か [Discord で会話](https://discord.gg/Uq7gcHh)してください。

### `matrix_scan_*` 関数のドキュメント

* キーボード/リビジョン: `void matrix_scan_kb(void)`
* キーマップ: `void matrix_scan_user(void)`

この関数はマトリックススキャンのたびに呼び出されます。これは基本的に MCU が処理できる頻度です。大量に実行されるため、ここに何を置くかについては注意してください。

カスタムマトリックススキャンコードが必要な場合は、この関数を使う必要があります。また、カスタムステータス出力 (LED あるいはディスプレイなど)や、ユーザが入力していない場合でも定期的にトリガーするその他の機能のために使うことができます。

# キーボードハウスキーピング :id=keyboard-housekeeping

* キーボード/リビジョン: `void housekeeping_task_kb(void)`
* キーマップ: `void housekeeping_task_user(void)`

この関数は、全ての QMK 処理の最後に、次の繰り返しを開始する前に呼び出されます。`housekeeping_task_*` の関数が呼び出された時点で、QMK が最後のマトリックススキャンを処理したと、安全に見なすことができます -- レイヤーの状態が更新され、USB レポートが送信され、LED が更新され、表示が描画されています。

`matrix_scan_*` と同様に、これらは MCU が処理できる頻度で呼び出されます。キーボードの応答性を維持するために、これらの関数の呼び出し中にできるだけ何もしないことをお勧めします。実際に何か特別なものを実装する必要がある場合に動作を停止させる可能性があります。

# キーボードアイドリング/ウェイクコード

キーボードがサポートしている場合、多くの機能を停止することで"アイドル"にすることができます。これの良い例は、RGB ライトあるいはバックライトです。これにより、電力消費を節約できるか、キーボードの動作が改善されるかもしれません。

これは2つの関数によって制御されます: `suspend_power_down_*` および `suspend_wakeup_init_*`。これらはシステムキーボードがアイドルになった時と、起動した時のそれぞれで呼ばれます。


### suspend_power_down_user() と suspend_wakeup_init_user() の実装例


```c
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
```

### キーボードサスペンド/ウェイク関数のドキュメント

* キーボード/リビジョン : `void suspend_power_down_kb(void)` および `void suspend_wakeup_init_user(void)`
* キーマップ: `void suspend_power_down_kb(void)` および `void suspend_wakeup_init_user(void)`

# レイヤー切り替えコード :id=layer-change-code

これはレイヤーが切り替えられるたびにコードを実行します。レイヤー表示あるいはカスタムレイヤー処理に役立ちます。

### `layer_state_set_*` の実装例

この例は、レイヤーに基づいて [RGB アンダーグロー](ja/feature_rgblight.md)を設定する方法を示していて、Planck を例として使っています。

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
    default: //  他の全てのレイヤーあるいはデフォルトのレイヤー
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```

特定のレイヤーの状態を確認するには、`IS_LAYER_ON_STATE(state, layer)` と `IS_LAYER_OFF_STATE(state, layer)` マクロを使います。

`layer_state_set_*` 関数の外では、グローバルなレイヤー状態を確認するために `IS_LAYER_ON(layer)` と `IS_LAYER_OFF(layer)` マクロを使えます。

### `layer_state_set_*` 関数のドキュメント

* キーボード/リビジョン: `layer_state_t layer_state_set_kb(layer_state_t state)`
* キーマップ: `layer_state_t layer_state_set_user(layer_state_t state)`


[キーマップの概要](ja/keymap.md#keymap-layer-status)で説明されるように、`state` はアクティブなレイヤーのビットマスクです。


# 永続的な設定 (EEPROM)

これによりキーボードのための永続的な設定を設定することができます。これらの設定はコントローラの EEPROM に保存され、電源が落ちた後であっても保持されます。設定は `eeconfig_read_kb` および `eeconfig_read_user` を使って読み取ることができ、`eeconfig_update_kb` および `eeconfig_update_user` を使って書きこむことができます。これは切り替え可能な機能 (rgb レイヤーの表示の切り替えなど)に役立ちます。さらに、`eeconfig_init_kb` および `eeconfig_init_user` を使って EEPROM のデフォルト値を設定できます。

ここでの複雑な部分は、EEPROM を介してデータを保存およびアクセスできる方法がたくさんあり、これを行うための"正しい"方法が無いということです。ただし、各関数には DWORD (4 バイト)しかありません。

EEPROM の書き込み回数には制限があることに注意してください。これは非常に高い値ですが、EEPROM に書き込むのはこれだけではなく、もし頻繁に書き込むと、MCU の寿命を大幅に短くする可能性があります。

* この例を理解していない場合は、この機能はかなり複雑なため、この機能を使うことを避けても構いません。

### 実装例

これは、設定を追加し、読み書きする例です。この例では、ユーザキーマップを使っています。これは複雑な機能で、多くのことが行われています。実際、動作のために上記の多くの関数を使います！


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

これは、設定をメモリ内に保存し、EEPROM に書き込むことができる32ビット構造体をセットアップします。これを使うと、この構造体に変数が定義されるため、変数を定義する必要が無くなります。`bool` (boolean) の値は1ビットを使い、`uint8_t` は8ビットを使い、`uint16_t` は16ビットを使うことに注意してください。組み合わせて使うことができますが、順番の変更は読み書きされる値が変更されるため、問題が発生するかもしれません。

`layer_state_set_*` 関数のために `rgb_layer_change` を使い、全てを設定するために `keyboard_post_init_user` および `process_record_user` を使います。

ここで、上の `keyboard_post_init_user` コードを使って、作成したばかりの構造体を設定するために `eeconfig_read_user()` を追加します。そして、この構造体をすぐに使ってキーマップの機能を制御することができます。それは以下のようになります:
```c
void keyboard_post_init_user(void) {
  // キーマップレベルのマトリックスの初期化処理を呼びます

  // EEPROM からユーザ設定を読み込みます
  user_config.raw = eeconfig_read_user();

  // 有効な場合はデフォルトレイヤーを設定します
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan();
    rgblight_mode_noeeprom(1);
  }
}
```
上記の関数は読み取ったばかりの EEPROM 設定を使い、デフォルトのレイヤーの RGB 色を設定します。その「生の」値は、上で作成した「共用体」に基づいて使用可能な構造に変換されます。

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
    default: //  他の全てのレイヤーあるいはデフォルトのレイヤー
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
```
これにより、値が有効になっていた場合のみ、RGB アンダーグローが変更されます。この値を設定するために、`RGB_LYR` と呼ばれる `process_record_user` 用の新しいキーコードを作成します。さらに、通常の RGB コードを使う場合、上記の例を使ってオフになることを確認します。以下のようになります:
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // 押された時に何かをします
      } else {
        // 放された時に何かをします
      }
      return false; // このキーの以降の処理をスキップします
    case KC_ENTER:
        // enter が押された時に音を再生します
        if (record->event.pressed) {
            PLAY_SONG(tone_qwerty);
        }
        return true; // QMK に enter のプレスまたはリリースイベントを送信させます
    case RGB_LYR:  // これにより、アンダーグローをレイヤー表示として、あるいは通常通りに使うことができます。
        if (record->event.pressed) {
            user_config.rgb_layer_change ^= 1; // 状態を切り替えます
            eeconfig_update_user(user_config.raw); // 新しい状態を EEPROM に書き込みます
            if (user_config.rgb_layer_change) { // レイヤーの状態表示が有効な場合
                layer_state_set(layer_state);   // すぐにレイヤーの色を更新します
            }
        }
        return false;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // 任意の RGB コード に対して(quantum_keycodes.h を見てください。400行目参照)
        if (record->event.pressed) { // これはレイヤー表示を無効にします。これを変更する場合は、無効にしたいだろうため。
            if (user_config.rgb_layer_change) {        // 有効な場合のみ
                user_config.rgb_layer_change = false;  // 無効にします
                eeconfig_update_user(user_config.raw); // 設定を EEPROM に書き込みます
            }
        }
        return true; break;
    default:
      return true; // 他の全てのキーコードを通常通りに処理します
  }
}
```
最後に、`eeconfig_init_user` 関数を追加して、EEPROM がリセットされた時にデフォルト値、さらにはカスタムアクションを指定できるようにします。EEPROM を強制的にリセットするには、`EEP_RST` キーコードあるいは[ブートマジック](ja/feature_bootmagic.md)機能を使います。例えば、デフォルトで rgb レイヤー表示を設定し、デフォルト値を保存したい場合。

```c
void eeconfig_init_user(void) {  // EEPROM がリセットされます！
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // デフォルトでこれを有効にします
  eeconfig_update_user(user_config.raw); // デフォルト値を EEPROM に書き込みます

  // これらの値も EEPROM に書き込むためには、noeeprom 以外のバージョンを使います
  rgblight_enable(); // デフォルトで RGB を有効にします
  rgblight_sethsv_cyan();  // デフォルトでシアンに設定します
  rgblight_mode(1); // デフォルトでソリッドに設定します
}
```

これで完了です。RGB レイヤー表示は必要な場合にのみ機能します。キーボードを取り外した後でも保存されます。RGB コードのいずれかを使うと、レイヤー表示が無効になり、設定したモードと色がそのままになります。

### 'EECONFIG' 関数のドキュメント

* キーボード/リビジョン: `void eeconfig_init_kb(void)`、`uint32_t eeconfig_read_kb(void)` および `void eeconfig_update_kb(uint32_t val)`
* キーマップ: `void eeconfig_init_user(void)`、`uint32_t eeconfig_read_user(void)` および `void eeconfig_update_user(uint32_t val)`

`val` は EEPROM に書き込みたいデータの値です。`eeconfig_read_*` 関数は EEPROM から32ビット(DWORD) 値を返します。
