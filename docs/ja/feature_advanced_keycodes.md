# 修飾キー :id=modifier-keys

<!---
  original document: 0.12.29:docs/feature_advanced_keycodes.md
  git diff 0.12.29 HEAD -- docs/feature_advanced_keycodes.md | cat
-->

以下のようにキーコードとモディファイアを組み合わせることができます。押すと、モディファイアのキーダウンイベントが送信され、次に `kc` のキーダウンイベントが送信されます。放すと、`kc` のキーアップイベントが送信され、次にモディファイアのキーアップイベントが送信されます。

| キー       | エイリアス                      | 説明                                                                |
| ---------- | ------------------------------- | ------------------------------------------------------------------- |
| `LCTL(kc)` | `C(kc)`                         | 左 Control を押しながら `kc` を押します。                           |
| `LSFT(kc)` | `S(kc)`                         | 左 Shift を押しながら `kc` を押します。                             |
| `LALT(kc)` | `A(kc)`, `LOPT(kc)`             | 左 Alt を押しながら `kc`を押します。                                |
| `LGUI(kc)` | `G(kc)`, `LCMD(kc)`, `LWIN(kc)` | 左 GUI を押しながら `kc` を押します。                               |
| `RCTL(kc)` |                                 | 右 Control を押しながら `kc` を押します。                           |
| `RSFT(kc)` |                                 | 右 Shift を押しながら `kc` を押します。                             |
| `RALT(kc)` | `ROPT(kc)`, `ALGR(kc)`          | 右 Alt を押しながら `kc` を押します。                               |
| `RGUI(kc)` | `RCMD(kc)`, `LWIN(kc)`          | 右 GUI を押しながら `kc` を押します。                               |
| `SGUI(kc)` | `SCMD(kc)`, `SWIN(kc)`          | 左 Shift と左 GUI を押しながら `kc` を押します。                    |
| `LCA(kc)`  |                                 | 左 Control と左 Alt を押しながら `kc` を押します。                  |
| `LSA(kc)`  |                                 | 左 Shift と左 Alt を押しながら `kc` を押します。                    |
| `RSA(kc)`  | `SAGR(kc)`                      | 右 Shift と右 Alt (AltGr) を押しながら `kc` を押します。            |
| `RCS(kc)`  |                                 | 右 Control と右 Shift を押しながら `kc` を押します。                |
| `LCAG(kc)` |                                 | 左 Control、左 Alt、左 GUI を押しながら `kc` を押します。           |
| `MEH(kc)`  |                                 | 左 Control、左 Shift、左 Alt を押しながら `kc` を押します。         |
| `HYPR(kc)` |                                 | 左 Control、左 Shift、左 Alt、左 GUI を押しながら `kc` を押します。 |

また、それらを繋げることができます。例えば、`LCTL(LALT(KC_DEL))` または  `C(A(KC_DEL))` は1回のキー押下で Control+Alt+Delete を送信するキーを作成します。

# モディファイアの状態を確認 :id=checking-modifier-state


現在のモディファイアの状態は、2つの関数によって主にアクセスされます。: `get_mods()` 関数は通常のモディファイアとモッドタップの状態を、`get_oneshot_mods()` 関数はワンショットモディファイアの状態を確認する関数です。(ワンショットモディファイアはキーが押されていない限り、通常のモディファイアキーのように動作します。)

1つ以上の特定のモディファイアが現在のモディファイアの状態に含まれているかどうかは、モディファイアの状態と、照合したいモディファイアの組み合わせに相当するモッドマスクとを AND 演算することで検出できます。
ビット演算が使われる理由は、モディファイアの状態が (GASC)<sub>R</sub>(GASC)<sub>L</sub> の形式で1バイトとして格納されるためです。

従って、例を挙げると、`01000010` は LShift+RALT の内部表現です。
C 言語におけるビット演算のより詳しい情報は、[ここ](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) をクリックして、Wikipedia のページのトピックを開いてください。

実際には、`get_mods() & MOD_BIT(KC_<modifier>)`([モディファイアキーコードのリスト](ja/keycodes_basic.md#modifiers) 参照) で、あるモディファイアが有効かどうかをチェックできるということです、また左右のモディファイアの違いが重要ではなく、両方にマッチさせたい場合は、`get_mods() & MOD_MASK_<modifier>`とします。ワンショットモディファイアについても、`get_mods()` を `get_oneshot_mods()` に置き換えれば同じことができます。

モディファイアの特定の組み合わせが同時にアクティブなのか確認する*だけ*なら、上で説明したモディファイアの状態とモッドマスクの論理積と、モッドマスク自身の結果を比較します。: `get_mods() & <mod mask> == <mod mask>`

例えば、左 Control キーと 左 Shift キーのワンショットモディファイアがオンで、その他のワンショットモディファイアがオフの場合にカスタムコードを起動したいとしましょう。そうするには、`(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))` で左 Control キーと Shift キーのモッドビットを組み合わせて目的のモッドマスクを構成し、それらを差し込みます: `get_oneshot_mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)) == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))`。モッドビットマスクの代わりに `MOD_MASK_CS` 使うと、条件を満たすために4つのモディファイアキー (左右両方の Control キーと Shift キー) を押す必要があります。

モッドマスクの完全なリストは、以下のとおりです。

| モッドマスク名     | マッチするモディファイア                                    |
|--------------------|-------------------------------------------------------------|
| `MOD_MASK_CTRL`    | 左 Control      , 右 Control                                |
| `MOD_MASK_SHIFT`   | 左 Shift        , 右 Shift                                  |
| `MOD_MASK_ALT`     | 左 Alt          , 右 Alt                                    |
| `MOD_MASK_GUI`     | 左 GUI          , 右 GUI                                    |
| `MOD_MASK_CS`      | Control         , Shift                                     |
| `MOD_MASK_CA`      | (左/右) Control , (左/右) Alt                               |
| `MOD_MASK_CG`      | (左/右) Control , (左/右) GUI                               |
| `MOD_MASK_SA`      | (左/右) Shift   , (左/右) Alt                               |
| `MOD_MASK_SG`      | (左/右) Shift   , (左/右) GUI                               |
| `MOD_MASK_AG`      | (左/右) Alt     , (左/右) GUI                               |
| `MOD_MASK_CSA`     | (左/右) Control , (左/右) Shift , (左/右) Alt               |
| `MOD_MASK_CSG`     | (左/右) Control , (左/右) Shift , (左/右) GUI               |
| `MOD_MASK_CAG`     | (左/右) Control , (左/右) Alt   , (左/右) GUI               |
| `MOD_MASK_SAG`     | (左/右) Shift   , (左/右) Alt   , (左/右) GUI               |
| `MOD_MASK_CSAG`    | (左/右) Control , (左/右) Shift , (左/右) Alt , (左/右) GUI |

`get_mods()` 関数を使って現在アクティブなモディファイアにアクセスする以外に、モディファイアの状態を変更するために使えるいくつかの関数があります。ここでは、`mods` 引数はモディファイアビットマスクを表します。

* `add_mods(mods)`: その他のモディファイアに影響を与えずに `mods` を有効にします。
* `register_mods(mods)`: `add_mods` に似ていますが、キーボードにすぐにレポートを送信します。
* `del_mods(mods)`: その他のモディファイアに影響を与えずに `mods` を無効にします。
* `unregister_mods(mods)`: `del_mods` に似ていますが、キーボードにすぐにレポートを送信します。
* `set_mods(mods)`: `mods` で現在のモディファイアの状態を上書きします
* `clear_mods()`: 全てのモディファイアを無効にすることによって、モディファイアの状態をリセットします。

同様に、`get_oneshot_mods()` 関数に加えて、ワンショットモディファイアのための関数もあります。

* `add_oneshot_mods(mods)`: その他のワンショットモディファイアに影響を与えずに `mods` を有効にします
* `del_oneshot_mods(mods)`: その他のワンショットモディファイアに影響を与えずに `mods` を無効にします
* `set_oneshot_mods(mods)`: `mods` で現在のワンショットモディファイアの状態を上書きします
* `clear_oneshot_mods()`: 全てのワンショットモディファイアを無効にすることによって、ワンショットモディファイアの状態をリセットします。

## 例 :id=examples

次の例は、[マクロについてのページ](ja/feature_macros.md) で読める [高度なマクロ](ja/feature_macros.md?id=advanced-macro-functions) を使っています。
### Alt + Tab の代わりの Alt + Escape :id=alt-escape-for-alt-tab

左 Alt と `KC_ESC` が押されたときに、アプリ切り替えの（左 Alt と） `KC_TAB` のように振る舞うことを実現する単純な例です。この例は、左 Alt だけがアクティブになっているかを厳格に確認します。つまり、Alt+Shift+Esc によるアプリの逆順での切り替えはできません。また、この例は、実際の Alt+Escape キーボードショートカットを起動することはできなくなりますが、AltGr+Escape キーボードショートカットを起動することはできることに留意してください。

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case KC_ESC:
        // 左 Alt だけがアクティブか検知します
        if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {
                // KC_LALT を登録する必要はありません。既にアクティブだからです。
                // Alt モディファイアはこの KC_TAB に適用されます。
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            // QMK にこれ以上キーコードの処理をさせません。
            return false;
        }
        // それ以外の場合は、QMK に通常通り KC_ESC の処理をさせます。
        return true;

    }
    return true;
};
```

### Delete の代わりの Shift + Backspace :id=shift-backspace-for-delete

`KC_BSPC` と組み合わせることで Shift の本来の動作が取り消され、そして、`KC_DEL` に完全に置き換えられる高度な例です。この例を適切に動作させるために2つのメイン変数が作られます。: `mod_state` と `delkey_registered` です。最初の1つ目の変数は、モディファイアの状態を記憶し、`KC_DEL` を登録した後に元に戻すために使われます。2つ目の変数はブール型変数 (true または false) で、`KC_DEL` の状態を追跡して Backspace/Delete キー全体のリリースを正確に管理します。

前の例と対照的に、この例は厳格なモディファイアの確認を行いません。このカスタムコードを起動するには、1つまたは2つの Shift キーがアクティブな間に `KC_BSPC` を押せば十分で、他のモディファイアの状態は関係ありません。この方法は、いくつかの特典を提供します。: Ctrl+Shift+Backspace は次の単語を削除 (Control+Delete) し、Ctrl+Alt+Shift+Backspace は Ctrl+Alt+Del キーボードショートカットを実行します。

```c
// アクティブなモディファイアを表すバイナリデータを保持する変数を初期化します
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 後々の参照のために現在のモディファイアの状態を変数に格納します
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Delete キーの状態（登録されているかどうか）を追跡するブール型変数を初期化します。
        static bool delkey_registered;
        if (record->event.pressed) {
            // いずれかの Shift がアクティブか検知します
            if (mod_state & MOD_MASK_SHIFT) {
                // 最初に、 Shift キーを KC_DEL に適用しないため、
                // 一時的に左右両方の Shift キーをキャンセルします
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // KC_DEL の状態を反映させるためにブール型変数を更新します
                delkey_registered = true;
                // Backspace/Delete キーをタップした後でも押し続けている Shift キーが機能するように、
                // モディファイアの状態を再適用します。
                set_mods(mod_state);
                return false;
            }
        } else { // KC_BSPC キーを離した場合
            // KC_BSPC を離しても KC_DEL が送信されている場合
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // QMK に Shift キーを除いて KC_BSPC を通常通り処理させます
        return true;
    }

    }
    return true;
};
```
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
