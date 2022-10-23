# キーボードをより良くするための便利なコア関数のリスト

<!---
  original document: 0.12.41:docs/ref_functions.md
  git diff 0.12.41 HEAD -- docs/ref_functions.md | cat
-->

QMK には、信じられないほど便利な、またはあなたが望んでいた機能を少し追加する、隠された関数がたくさんあります。特定の機能に固有の関数はそれぞれの機能のページにあるため、ここには含まれていません。

## (OLKB) トライレイヤー :id=olkb-tri-layers

目的に応じて、実際に使うことができる別個の関数があります。

### `update_tri_layer(x, y, z)`

最初は `update_tri_layer(x, y, z)` 関数です。この関数はレイヤー `x` と `y` の両方がオンになっているかどうかを調べます。両方ともオンの場合は、レイヤー `z` がオンになります。それ以外の場合、`x` と `y` の両方がオンではない(一方のみがオン、またはどちらもオンでない)場合は、レイヤー `z` をオフにします。

この関数は、この機能を持つ特定のキーを作成したいが、他のレイヤーのキーコードではそうしたくない場合に便利です。

#### 例

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    }
  return true;
}
```

### `update_tri_layer_state(state, x, y, z)`
もう1つの関数は `update_tri_layer_state(state, x, y, z)` です。この関数は [`layer_state_set_*` 関数](ja/custom_quantum_functions.md#layer-change-code)から呼び出されることを意図しています。これは、キーコードを使ってレイヤーを変更するたびに、これがチェックされることを意味します。したがって、`LT(layer, kc)` を使ってレイヤーを変更すると、同じレイヤーチェックが引き起こされます。

このメソッドの注意点は2つあります:
1. `x` および `y` レイヤーをオンにしないと、`z` レイヤーにアクセスできません。これは、レイヤー `z` のみをアクティブにしようとすると、このコードが実行され、使用前にレイヤー `z` がオフになるからです。
2. レイヤーは最上位の番号から処理されるので、`z` は `x` や `y` よりも上位のレイヤーでなければなりません。そうでなければアクセスできない場合があります。

#### 例

```c
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
```

あるいは、すぐに値を「返す」必要はありません。複数のトライレイヤーを追加、あるいは追加の効果を追加する場合に便利です。

```c
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layer_state(state, _RAISE, _SYMB, _SPECIAL);
  return state;
}
```

## 永続的なデフォルトレイヤーの設定

デフォルトレイヤーを設定して、キーボードを取り外しても保持されるようにしたいですか？そうであれば、これがそのための関数です。

これを使うには、`set_single_persistent_default_layer(layer)` を使います。レイヤーに名前が定義されている場合は、代わりにそれを使うことができます (_QWERTY、_DVORAK、_COLEMAK など)。

これは、デフォルトレイヤーを設定し、永続設定が更新され、もし [オーディオ](ja/feature_audio.md) がキーボードで有効でデフォルトレイヤーの音が設定されている場合は、曲を再生します。

デフォルトレイヤーの音を設定するには、以下のように `config.h` ファイルに定義する必要があります。

```c
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                              SONG(COLEMAK_SOUND), \
                              SONG(DVORAK_SOUND) \
                            }
```


?> [quantum/audio/song_list.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h) に使用できる多くの定義済みの曲があります。

## キーボードのリセット

使用できる `RESET` quantum キーコードがあります。ただし、キーを個別に押すのではなくマクロの一部としてリセットしたい場合は、そうすることができます。

そのためには、`reset_keyboard()` を関数またはマクロに追加すると、ブートローダがリセットされます。

## EEPROM (永続ストレージ)の消去

オーディオ、RGB アンダーグロー、バックライト、キーの動作に問題がある場合は、EEPROM (永続的な設定のストレージ)をリセットすることができます。EEPROM を強制的にリセットするには、[`EEP_RST` キーコード](ja/quantum_keycodes.md)あるいは[ブートマジック](ja/feature_bootmagic.md)機能を使います。それらのいずれも選択肢にない場合は、カスタムマクロを使って行うことができます。

EEPROM を消去するには、関数またはマクロから `eeconfig_init()` を実行し、ほとんどの設定をデフォルトにリセットします。

## タップランダムキー

ランダムな文字をホストコンピュータに送信する場合は、`tap_random_base64()` 関数を使うことができます。これは[疑似乱数的に](https://en.wikipedia.org/wiki/Pseudorandom_number_generator)0から63の数字を選択し、その選択に基づいてキー押下を送信します。(0–25 は `A`–`Z`、26–51 は `a`–`z`、52–61 は `0`–`9`、62 は `+`、63 は `/`)。

?> 言うまでもないですが、これはランダムに Base64 キーあるいはパスワードを生成する暗号的に安全な方法では _ありません_。

## ソフトウェアタイマー

タイマーを開始し、時間固有のイベントの値を読み取ることができます。以下は例です:

```c
static uint16_t key_timer;
key_timer = timer_read();

if (timer_elapsed(key_timer) < 100) {
  // 経過時間が 100ms 未満の場合に何かを行う
} else {
  // 経過時間が 100ms 以上の場合に何かを行う
}
```
