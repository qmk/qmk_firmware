# 修飾キー :id=modifier-keys

<!---
  original document: 0.9.0:docs/feature_advanced_keycodes.md
  git diff 0.9.0 HEAD -- docs/feature_advanced_keycodes.md | cat
-->

以下のようにキーコードとモディファイアを組み合わせることができます。押すと、モディファイアのキーダウンイベントが送信され、次に `kc` のキーダウンイベントが送信されます。放すと、`kc` のキーアップイベントが送信され、次にモディファイアのキーアップイベントが送信されます。

| キー | エイリアス | 説明 |
|----------|-------------------------------|----------------------------------------------------|
| `LCTL(kc)` | `C(kc)` | 左 Control を押しながら `kc` を押します。 |
| `LSFT(kc)` | `S(kc)` | 左 Shift を押しながら `kc` を押します。 |
| `LALT(kc)` | `A(kc)`, `LOPT(kc)` | 左 Alt を押しながら `kc`を押します。 |
| `LGUI(kc)` | `G(kc)`, `LCMD(kc)`, `LWIN(kc)` | 左 GUI を押しながら `kc` を押します。 |
| `RCTL(kc)` |  | 右 Control を押しながら `kc` を押します。 |
| `RSFT(kc)` |  | 右 Shift を押しながら `kc` を押します。 |
| `RALT(kc)` | `ROPT(kc)`, `ALGR(kc)` | 右 Alt を押しながら `kc` を押します。 |
| `RGUI(kc)` | `RCMD(kc)`, `LWIN(kc)` | 右 GUI を押しながら `kc` を押します。 |
| `SGUI(kc)` | `SCMD(kc)`, `SWIN(kc)` | 左 Shift と左 GUI を押しながら `kc` を押します。 |
| `LCA(kc)` |  | 左 Control と左 Alt を押しながら `kc` を押します。 |
| `LCAG(kc)` |  | 左 Control、左 Alt、左 GUI を押しながら `kc` を押します。 |
| `MEH(kc)` |  | 左 Control、左 Shift、左 Alt を押しながら `kc` を押します。 |
| `HYPR(kc)` |  | 左 Control、左 Shift、左 Alt、左 GUI を押しながら `kc` を押します。 |

また、それらを繋げることができます。例えば、`LCTL(LALT(KC_DEL))` または  `C(A(KC_DEL))` は1回のキー押下で Control+Alt+Delete を送信するキーを作成します。

# 過去の内容 :id=legacy-content

このページには多くの機能が含まれていました。このページを構成していた多くのセクションをそれぞれのページに移動しました。これより下は全て単なるリダイレクトであるため、web上で古いリンクをたどっている人は探しているものを見つけることができます。

## レイヤー :id=switching-and-toggling-layers

* [レイヤー](ja/feature_layers.md)

## モッドタップ :id=mod-tap

* [モッドタップ](ja/mod_tap.md)

## ワンショットキー :id=one-shot-keys

* [ワンショットキー](ja/one_shot_keys.md)

## タップホールド設定オプション :id=tap-hold-configuration-options

* [タップホールド設定オプション](ja/tap_hold.md)
