# ブートマジック

<!---
  original document: 5d5ff80:docs/feature_bootmagic.md
  git diff 5d5ff80 HEAD -- docs/feature_bootmagic.md | cat
-->

再書き込みせずにキーボードの挙動を変更することができる、3つの独立した関連する機能があります。それぞれは似たような機能を持ちますが、キーボードがどのように設定されているかによって異なる方法でアクセスされます。

**ブートマジック**は初期化の間にキーボードを設定するためのシステムです。ブートマジックコマンドを起動するには、ブートマジックキーと1つ以上のコマンドキーを押し続けます。

**ブートマジックキーコード** は前に `MAGIC_` が付いており、キーボードが初期化された*後で*ブートマジックの機能にアクセスすることができます。キーコードを使うには、他のキーコードと同じようにそれらをキーマップに割り当てます。

以前は**マジック**として知られていた**コマンド**は、キーボードの異なる側面を制御することができる別の機能です。ブートマジックと一部の機能を共有しますが、コンソールにバージョン情報を出力するような、ブートマジックにはできないこともできます。詳細は、[コマンド](ja/feature_command.md)を見てください。

一部のキーボードでは、ブートマジックはデフォルトで無効になっています。その場合、`rules.mk` 内で以下のように明示的に有効にする必要があります:

```make
BOOTMAGIC_ENABLE = full
```

?> `full` の代わりに `yes` が使われていることがあるかもしれませんが、これは問題ありません。ただし、`yes` は非推奨で、理想的には `full` (あるいは`lite`) が使われるべきです。

さらに、以下を `rules.mk` ファイルに追加することで、[ブートマジックライト](#bootmagic-lite) (スケールダウンした、とても基本的なバージョンのブートマジック)を使うことができます:

```make
BOOTMAGIC_ENABLE = lite
```

## ホットキー

キーボードを接続しながら、ブートマジックキー(デフォルトはスペース)と目的のホットキーを押します。例えば、スペースと `B` を押したままにすると、ブートローダに入ります。

| ホットキー | 説明 |
|------------------|---------------------------------------------|
| エスケープ | EEPROM のブートマジック設定を無視する |
| `B` | ブートローダに入る |
| `D` | シリアルを介するデバッグ出力の切り替え |
| `X` | キーマトリックスのデバッグ出力の切り替え |
| `K` | キーボードのデバッグの切り替え |
| `M` | マウスのデバッグの切り替え |
| `L` | EE_HANDS 左右設定に、"左手"を設定 |
| `R` | EE_HANDS 左右設定に、"右手"を設定 |
| Backspace | EEPROM をクリア |
| Caps Lock | Caps Lock を左コントロールとして扱うかを切り替え |
| 左 Control | Caps Lock と左コントロールの入れ替えを切り替え |
| 左 Alt | 左 Alt と左 GUI の入れ替えを切り替え |
| 右 Alt | 右 Alt と右 GUI の入れ替えを切り替え |
| 左 GUI | GUI キーの有効・無効を切り替え (ゲームの時に便利です) |
| <code>&#96;</code> | <code>&#96;</code> とエスケープの入れ替えを切り替え |
| `\` | `\` とバックスペースの入れ替えを切り替え |
| `N` | N キーロールオーバー (NKRO) の有効・無効を切り替え |
| `0` | レイヤー 0 をデフォルトレイヤーにする |
| `1` | レイヤー 1 をデフォルトレイヤーにする |
| `2` | レイヤー 2 をデフォルトレイヤーにする |
| `3` | レイヤー 3 をデフォルトレイヤーにする |
| `4` | レイヤー 4 をデフォルトレイヤーにする |
| `5` | レイヤー 5 をデフォルトレイヤーにする |
| `6` | レイヤー 6 をデフォルトレイヤーにする |
| `7` | レイヤー 7 をデフォルトレイヤーにする |

## キーコード

| キー | エイリアス | 説明 |
|----------------------------------|---------|--------------------------------------------------------------------------|
| `MAGIC_SWAP_CONTROL_CAPSLOCK` | `CL_SWAP` | Caps Lock と左コントロールの入れ替え |
| `MAGIC_UNSWAP_CONTROL_CAPSLOCK` | `CL_NORM` | Caps Lock と左コントロールの入れ替えの解除 |
| `MAGIC_CAPSLOCK_TO_CONTROL` | `CL_CTRL` | Caps Lock をコントロールとして扱う |
| `MAGIC_UNCAPSLOCK_TO_CONTROL` | `CL_CAPS` | Caps Lock をコントロールとして扱うことを止める |
| `MAGIC_SWAP_LCTL_LGUI` | `LCG_SWP` | 左コントロールと GUI の入れ替え |
| `MAGIC_UNSWAP_LCTL_LGUI` | `LCG_NRM` | 左コントロールと GUI の入れ替えを解除 |
| `MAGIC_SWAP_RCTL_RGUI` | `RCG_SWP` | 右コントロールと GUI の入れ替え |
| `MAGIC_UNSWAP_RCTL_RGUI` | `RCG_NRM` | 右コントロールと GUI の入れ替えを解除 |
| `MAGIC_SWAP_CTL_GUI` | `CG_SWAP` | 両側のコントロールと GUI の入れ替え |
| `MAGIC_UNSWAP_CTL_GUI` | `CG_NORM` | 両側のコントロールと GUI の入れ替えを解除 |
| `MAGIC_TOGGLE_CTL_GUI` | `CG_TOGG` | 両側のコントロールと GUI の入れ替えの切り替え |
| `MAGIC_SWAP_LALT_LGUI` | `LAG_SWP` | 左 Alt と GUI の入れ替え |
| `MAGIC_UNSWAP_LALT_LGUI` | `LAG_NRM` | 左 Alt と GUI の入れ替えを解除 |
| `MAGIC_SWAP_RALT_RGUI` | `RAG_SWP` | 右 Alt と GUI の入れ替え |
| `MAGIC_UNSWAP_RALT_RGUI` | `RAG_NRM` | 右 Alt と GUI の入れ替えを解除 |
| `MAGIC_SWAP_ALT_GUI` | `AG_SWAP` | 両側の Alt と GUI の入れ替え |
| `MAGIC_UNSWAP_ALT_GUI` | `AG_NORM` | 両側の Alt と GUI の入れ替えを解除 |
| `MAGIC_TOGGLE_ALT_GUI` | `AG_TOGG` | 両側の Alt と GUI の入れ替えの切り替え |
| `MAGIC_NO_GUI` | `GUI_OFF` | GUI キーを無効にする |
| `MAGIC_UNNO_GUI` | `GUI_ON` | GUI キーを有効にする |
| `MAGIC_SWAP_GRAVE_ESC` | `GE_SWAP` | <code>&#96;</code> とエスケープの入れ替え |
| `MAGIC_UNSWAP_GRAVE_ESC` | `GE_NORM` | <code>&#96;</code> とエスケープの入れ替えを解除 |
| `MAGIC_SWAP_BACKSLASH_BACKSPACE` | `BS_SWAP` | `\` とバックスペースを入れ替え |
| `MAGIC_UNSWAP_BACKSLASH_BACKSPACE` | `BS_NORM` | `\` とバックスペースの入れ替えを解除する |
| `MAGIC_HOST_NKRO` | `NK_ON` | N キーロールオーバーを有効にする |
| `MAGIC_UNHOST_NKRO` | `NK_OFF` | N キーロールオーバーを無効にする |
| `MAGIC_TOGGLE_NKRO` | `NK_TOGG` | N キーロールオーバーの有効・無効を切り替え |
| `MAGIC_EE_HANDS_LEFT` | `EH_LEFT` | 分割キーボードのマスター側を左手に設定(`EE_HANDS` 用) |
| `MAGIC_EE_HANDS_RIGHT` | `EH_RGHT` | 分割キーボードのマスター側を右手に設定(`EE_HANDS` 用) |

## 設定

ブートマジックのためのホットキーの割り当てを変更したい場合は、キーボードあるいはキーマップレベルのどちらかで、`config.h` にこれらを `#define` します。

| 定義 | デフォルト | 説明 |
|----------------------------------------|-------------|---------------------------------------------------|
| `BOOTMAGIC_KEY_SALT` | `KC_SPACE` | ブートマジックキー |
| `BOOTMAGIC_KEY_SKIP` | `KC_ESC` | EEPROM のブートマジック設定を無視する |
| `BOOTMAGIC_KEY_EEPROM_CLEAR` | `KC_BSPACE` | EEPROM 設定をクリアする |
| `BOOTMAGIC_KEY_BOOTLOADER` | `KC_B` | ブートローダに入る |
| `BOOTMAGIC_KEY_DEBUG_ENABLE` | `KC_D` | シリアルを介するデバッグ出力の切り替え |
| `BOOTMAGIC_KEY_DEBUG_MATRIX` | `KC_X` | マトリックスのデバッグを切り替え |
| `BOOTMAGIC_KEY_DEBUG_KEYBOARD` | `KC_K` | キーボードのデバッグの切り替え |
| `BOOTMAGIC_KEY_DEBUG_MOUSE` | `KC_M` | マウスのデバッグの切り替え |
| `BOOTMAGIC_KEY_EE_HANDS_LEFT` | `KC_L` | EE_HANDS 左右設定に、"左手"を設定 |
| `BOOTMAGIC_KEY_EE_HANDS_RIGHT` | `KC_R` | EE_HANDS 左右設定に、"右手"を設定 |
| `BOOTMAGIC_KEY_SWAP_CONTROL_CAPSLOCK` | `KC_LCTRL` | 左コントロールと Caps Lock の入れ替え |
| `BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL` | `KC_CAPSLOCK` | Caps Lock を左コントロールとして扱うかを切り替え |
| `BOOTMAGIC_KEY_SWAP_LALT_LGUI` | `KC_LALT` | 左 Alt と左 GUI の入れ替えを切り替え (macOS 用) |
| `BOOTMAGIC_KEY_SWAP_RALT_RGUI` | `KC_RALT` | 右 Alt と右 GUI の入れ替えを切り替え (macOS 用) |
| `BOOTMAGIC_KEY_NO_GUI` | `KC_LGUI` | GUI キーの有効・無効を切り替え (ゲームの時に便利です) |
| `BOOTMAGIC_KEY_SWAP_GRAVE_ESC` | `KC_GRAVE` | <code>&#96;</code> とエスケープの入れ替えを切り替え |
| `BOOTMAGIC_KEY_SWAP_BACKSLASH_BACKSPACE` | `KC_BSLASH` | `\` とバックスペースの入れ替えを切り替え |
| `BOOTMAGIC_HOST_NKRO` | `KC_N` | N キーロールオーバー (NKRO) の有効・無効を切り替え |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_0` | `KC_0` | レイヤー 0 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_1` | `KC_1` | レイヤー 1 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_2` | `KC_2` | レイヤー 2 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_3` | `KC_3` | レイヤー 3 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_4` | `KC_4` | レイヤー 4 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_5` | `KC_5` | レイヤー 5 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_6` | `KC_6` | レイヤー 6 をデフォルトレイヤーにする |
| `BOOTMAGIC_KEY_DEFAULT_LAYER_7` | `KC_7` | レイヤー 7 をデフォルトレイヤーにする |

# ブートマジックライト :id=bootmagic-lite

本格的なブートマジック機能の他に、ブートローダへのジャンプのみを処理するブートマジックライトがあります。これは、物理的なリセットボタンが無くブートローダにジャンプする方法が必要だが、ブートマジックが引き起こす問題を扱いたくないキーボードに適しています。

ブートマジックのこのバージョンを有効にするには、以下を使って `rules.mk` で有効にする必要があります:

```make
BOOTMAGIC_ENABLE = lite
```

さらに、どのキーを使うかを指定したほうが良いかもしれません。これは普通ではないマトリックスを持つキーボードで特に便利です。そのためには、使いたいキーの行と列を指定する必要があります。`config.h` ファイルにこれらのエントリを追加します:

```c
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
```

デフォルトでは、これらは 0 と 0 に設定されます。これは通常はほとんどのキーボードで "ESC" キーです。

ブートローダを起動するには、キーボードを接続する時にこのキーを押し続けます。たった1つのキーです。

!> ブートマジックライトを使用すると、EEPROM を**常にリセットします**。つまり保存された全ての設定は失われます。

## 高度なブートマジックライト

`bootmagic_lite` 関数は必要に応じてコード内で置き換えることができるように、弱く定義されています。これの良い例は Zeal60 キーボードで、追加の処理が必要です。

関数を置き換えるには、以下のようなものをコードに追加するだけです:

```c
void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
      // ブートローダにジャンプする。
      bootloader_jump();
    }
}
```

追加の機能をここに追加することができます。例えば、eeprom のリセットやブートマジックを起動するために押す必要がある追加のキーです。`bootmagic_lite` はファームウェア内で大部分の機能が初期化される前に呼ばれることに注意してください。
