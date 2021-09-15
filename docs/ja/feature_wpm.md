# Word Per Minute (WPM) の計算

<!---
  original document: 0.14.14:docs/feature_wpm.md
  git diff 0.14.14 HEAD -- docs/feature_wpm.md | cat
-->

WPM 機能は、キーストローク間の時間から1分あたりの平均（移動平均）単語数を計算し、様々な用途で利用できるようにします。

`rules.mk` に以下を追加することで WPM システムを有効にします:

    WPM_ENABLE = yes

ソフトシリアルを使っている分割キーボードについては、計算された WPM スコアがマスター側とスレーブ側で利用可能です。

## 設定

| 定義                         | デフォルト | 説明                                                                                  |
|------------------------------|------------|---------------------------------------------------------------------------------------|
| `WPM_SMOOTHING`              | `0.0487`   | 平滑化を約40キーストロークに設定します                                                |
| `WPM_ESTIMATED_WORD_SIZE`    | `5`        | これは、平均ワードサイズを推定する時に使われる値です(後戻りや通常の使用の場合)        |
| `WPM_ALLOW_COUNT_REGRESSOIN` | _定義なし_ | 定義されている場合、Delete または Backspace を押したときに WPM を減らすことができます |
## 公開関数

| 関数                    | 説明                                         |
|-------------------------|----------------------------------------------|
| `get_current_wpm(void)` | 現在の WPM を0から255の間の値として返します  |
| `set_current_wpm(x)`    | 現在の WPM を `x` (0から255の間)に設定します |

## コールバック

デフォルトでは、WPM スコアは文字、空白、およびいくつかの句読点のみを含みます。WPM の計算に含むとみなす文字セットを変更したい場合は、独自の `bool wpm_keycode_user(uint16_t keycode)` を実装し、計算に含めたい文字について true を返し、計算しない特定のキーコードに false を返すようにします。

例えば、デフォルトは以下の通りです:

```c
bool wpm_keycode_user(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLASH)) {
        return true;
    }

    return false;
}
```

さらに、`WPM_ALLOW_COUNT_REGRESSION` が定義されている場合、WPM を減少させることができる `uint8_t wpm_regress_count(uint16_t keycode)` という関数があります。これは特定のキーコード(またはその組み合わせ)にペナルティを課すことができるようにしたい場合に便利です。

```c
__attribute__((weak)) uint8_t wpm_regress_count(uint16_t keycode) {
    bool weak_modded = (keycode >= QK_LCTL && keycode < QK_LSFT) || (keycode >= QK_RCTL && keycode < QK_RSFT);
    
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if (((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL} || weak_modded) && (keycode == KC_DEL || keycode == KC_BSPC)) {
        return WPM_ESTIMATED_WORD_SIZE;
    }
    if (keycode == KC_DEL || keycode == KC_BSPC) {
        return 1;
    }
}
```
