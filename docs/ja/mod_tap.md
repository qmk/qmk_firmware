# モッドタップ

<!---
  original document: 0.9.34:docs/mod_tap.md
  git diff 0.9.34 HEAD -- docs/mod_tap.md | cat
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

| キー         | エイリアス                  | 説明                                                        |
|--------------|-----------------------------|-------------------------------------------------------------|
| `LCTL_T(kc)` | `CTL_T(kc)`                 | 押したままの場合は左 Control、タップした場合は `kc`         |
| `LSFT_T(kc)` | `SFT_T(kc)`                 | 押したままの場合は左 Shift、タップした場合は `kc`           |
| `LALT_T(kc)` | `LOPT_T(kc)`, `ALT_T(kc)`, `OPT_T(kc)`                            | 押したままの場合は左 Alt、タップした場合は `kc` |
| `LGUI_T(kc)` | `LCMD_T(kc)`, `LWIN_T(kc)`, `GUI_T(kc)`, `CMD_T(kc)`, `WIN_T(kc)` | 押したままの場合は左 GUI、タップした場合は `kc` |
| `RCTL_T(kc)` |                             | 押したままの場合は右 Control、タップした場合は `kc`         |
| `RSFT_T(kc)` |                             | 押したままの場合は右 Shift、タップした場合は `kc`           |
| `RALT_T(kc)` | `ROPT_T(kc)`, `ALGR_T(kc)`  | 押したままの場合は右 Alt、タップした場合は `kc`             |
| `RGUI_T(kc)` | `RCMD_T(kc)`, `RWIN_T(kc)`  | 押したままの場合は右 GUI、タップした場合は `kc`             |
| `SGUI_T(kc)` | `SCMD_T(kc)`, `SWIN_T(kc)`  | 押したままの場合は左 Shift と左 GUI、タップした場合は `kc`             |
| `LCA_T(kc)`  |                             | 押したままの場合は左 Control と左 Alt、タップした場合は `kc`           |
| `LCAG_T(kc)` |                             | 押したままの場合は左 Control、左 Alt と左 GUI、タップした場合は `kc`   |
| `RCAG_T(kc)` |                             | 押したままの場合は右 Control、右 Alt と右 GUI、タップした場合は `kc`   |
| `C_S_T(kc)`  |                             | 押したままの場合は左 Control と左 Shift、タップした場合は `kc`         |
| `MEH_T(kc)`  |                             | 押したままの場合は左 Control、左 Shift と左 Alt、タップした場合は `kc` |
| `HYPR_T(kc)` | `ALL_T(kc)`  | 押したままの場合は左 Control、左 Shift、左 Alt と左 GUI、タップした場合は `kc` - より詳しくは[ここ](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)を見てください |

## 注意事項

残念ながら、キーコードで指定されたモディファイアは無視されるため、これらのキーコードはモッドタップまたはレイヤータップで使うことができません。

さらに、Windows でリモートデスクトップ接続を使う場合に、問題が発生する場合があります。これらのコードはシフトを非常に高速に送信するため、リモートデスクトップはコードを見逃すかもしれません。

これを修正するには、リモートデスクトップ接続を開き、「オプションの表示」を開き、「ローカル リソース」タブを開きます。キーボードセクションで、ドロップダウンを「このコンピューター」に変更します。これにより問題が修正され、キャラクタが正しく動作するようになります。
