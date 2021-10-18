# モッドタップ

<!---
  original document: 0.13.34:docs/mod_tap.md
  git diff 0.13.34 HEAD -- docs/mod_tap.md | cat
-->

モッドタップキー `MT(mod, kc)` は、押したままの時にモディファイアのように機能し、タップされた時に通常のキーのように振舞います。別の言い方をすると、タップした時に Escape を送信しますが、押したままの時に Control あるいは Shift キーとして機能するキーを持つことができます。

このキーコードと `OSM()` が受け付けるモディファイアは、`KC_` ではなく、`MOD_` の接頭辞が付いています:

| モディファイア |  説明                                        |
|----------------|----------------------------------------------|
|  `MOD_LCTL`    | 左 Control                                   |
|  `MOD_LSFT`    | 左 Shift                                     |
|  `MOD_LALT`    | 左 Alt                                       |
|  `MOD_LGUI`    | 左 GUI (Windows/Command/Meta キー)           |
|  `MOD_RCTL`    | 右 Control                                   |
|  `MOD_RSFT`    | 右 Shift                                     |
|  `MOD_RALT`    | 右 Alt (AltGr)                               |
|  `MOD_RGUI`    | 右 GUI (Windows/Command/Meta キー)           |
|  `MOD_HYPR`    | Hyper (左 Control、左 Shift、左 Alt、左 GUI) |
|  `MOD_MEH`     | Meh (左 Control、左 Shift、左 Alt)           |

以下のようにそれらを OR することで、これらを組み合わせることができます:

```c
MT(MOD_LCTL | MOD_LSFT, KC_ESC)
```

押したままの時にこのキーは左 Control および左 Shift をアクティブにし、タップされた時に Escape を送信します。

便利なように、QMK はキーマップで一般的な組み合わせをよりコンパクトにするためのモッドタップショートカットを含んでいます:

| キー         | エイリアス                                                        | 説明                                                                   |
| ------------ | ----------------------------------------------------------------- | ---------------------------------------------------------------------- |
| `LCTL_T(kc)` | `CTL_T(kc)`                                                       | 押したままの場合は左 Control、タップした場合は `kc`                    |
| `LSFT_T(kc)` | `SFT_T(kc)`                                                       | 押したままの場合は左 Shift、タップした場合は `kc`                      |
| `LALT_T(kc)` | `LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                            | 押したままの場合は左 Alt、タップした場合は `kc`                        |
| `LGUI_T(kc)` | `LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)` | 押したままの場合は左 GUI、タップした場合は `kc`                        |
| `RCTL_T(kc)` |                                                                   | 押したままの場合は右 Control、タップした場合は `kc`                    |
| `RSFT_T(kc)` |                                                                   | 押したままの場合は右 Shift、タップした場合は `kc`                      |
| `RALT_T(kc)` | `ROPT_T(kc)`, `ALGR_T(kc)`                                        | 押したままの場合は右 Alt、タップした場合は `kc`                        |
| `RGUI_T(kc)` | `RCMD_T(kc)`, `RWIN_T(kc)`                                        | 押したままの場合は右 GUI、タップした場合は `kc`                        |
| `LSG_T(kc)`  | `SGUI_T(kc)`, `SCMD_T(kc)`, `SWIN_T(kc)`                          | 押したままの場合は左 Shift と左 GUI、タップした場合は `kc`             |
| `LAG_T(kc)`  |                                                                   | 押したままの場合は左 Alt と左 GUI、タップした場合は `kc`               |
| `RSG_T(kc)`  |                                                                   | 押したままの場合は右 Shift と右 GUI、タップした場合は `kc`             |
| `RAG_T(kc)`  |                                                                   | 押したままの場合は右 Alt と右 GUI、タップした場合は `kc`               |
| `LCA_T(kc)`  |                                                                   | 押したままの場合は左 Control と左 Alt、タップした場合は `kc`           |
| `LSA_T(kc)`  |                                                                   | 押したままの場合は左 Shift と Alt、タップした場合は `kc`               |
| `RSA_T(kc)`  | `SAGR_T(kc)`                                                      | 押したままの場合は右 Shift と Alt (AltGr)、タップした場合は `kc`       |
| `RCS_T(kc)`  |                                                                   | 押したままの場合は右 Control と Shift、タップした場合は `kc`           |
| `LCAG_T(kc)` |                                                                   | 押したままの場合は左 Control、左 Alt と左 GUI、タップした場合は `kc`   |
| `RCAG_T(kc)` |                                                                   | 押したままの場合は右 Control、右 Alt と右 GUI、タップした場合は `kc`   |
| `C_S_T(kc)`  |                                                                   | 押したままの場合は左 Control と左 Shift、タップした場合は `kc`         |
| `MEH_T(kc)`  |                                                                   | 押したままの場合は左 Control、左 Shift と左 Alt、タップした場合は `kc` |
| `HYPR_T(kc)` | `ALL_T(kc)`                                                       | 押したままの場合は左 Control、左 Shift、左 Alt と左 GUI、タップした場合は `kc` - より詳しくは[ここ](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)を見てください |

## 注意事項

現在のところ、`MT()` の引数 `kc` は[基本的なキーコードセット](ja/keycodes_basic.md)に制限されています。つまり、`LCTL()`、`KC_TILD`、あるいは `0xFF` より大きなキーコードを使うことができません。これは、QMK が16ビットのキーコードを使うためです。3ビットは機能の識別のために使われ、1ビットは右または左の mod を選択するために使われ、4ビットはどの mod かを区別するために使われ、キーコードには8ビットしか残されていません。さらに、モッドタップで少なくとも1つの右手用のモディファイアが指定された場合、指定された全てのモディファイアが右手用になるため、2つをうまく組み合わせて一致させることはできません。例えば、左 Control と右 Shift は、右 Control と右 Shift になります。

これを拡張してもせいぜい複雑になるだけでしょう。32ビットキーコードに移行すると、これの多くが解決されますが、キーマップマトリックスが使用する領域が2倍になります。また、問題が起きる可能性もあります。タップしたキーコードにモディファイアを適用する必要がある場合は、[タップダンス](ja/feature_tap_dance.md#example-5)を使うことができます。

さらに、Windows でリモートデスクトップ接続を使う場合に、問題が発生する場合があります。なぜならば、これらのキーコードは人よりも速くキーイベントを送信するため、リモートデスクトップがキーコードを見落とすかもしれないからです。
この問題を解決するには、リモートデスクトップ接続を開いて「オプションの表示」をクリックし、「ローカル リソース」タブを開きます。キーボードセクションで、ドロップダウンを「このコンピューター」に変更します。これで問題が解決され、文字が正しく機能するようになります。
[`TAP_CODE_DELAY`](ja/config_options.md#behaviors-that-can-be-configured) を増やすことで緩和することもできます。

## 他のリソース

モッドタップの動作を調整する追加フラグについては、[タップホールド設定オプション](ja/tap_hold.md)を参照してください。
