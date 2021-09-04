# キーオーバーライド

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.14.6:docs/feature_key_overrides.md
  git diff 0.14.6 HEAD -- docs/feature_key_overrides.md | cat
-->

キーオーバーライドを使用すると、修飾キーとキーの組み合わせを上書きして、異なる修飾キーの組み合わせを送信したり、完全にカスタマイズされたアクションを実行することができます。`shift` + `1` で `!` がコンピュータに入力されないようにしたいですか？`shift` + `1` を押したときにキーボードに何か別の入力をさせるには、キーオーバーライドを使います。よくある動作は次のようなものです: `修飾キー w` + `キー x` が押された場合、キーボードレポートでこれらのキーを `修飾キー y` + `キー z` に置き換えます。

一時レイヤーや fn キーと同様の方法でキーオーバーライドを使うことで、カスタムキーコードやショートカットを有効化でき、これには多くの利点があります: 修飾キーの元の使い方を完全に維持したまま、キーボードから fn キーを削除することでスペースを節約できます。また、_修飾キーの組み合わせ_ で異なる動作をさせるための設定を、個々の修飾キーに設定するよりずっと簡単に行うことができます。可能性は非常に大きく、このドキュメントには全体を通してインスピレーションを得るためのいくつかの例が含まれています。

##### 始めるためのいくつかの例: キーオーバーライドの使い道
- `ctrl` + `音量アップ/ダウン` を押したときに `輝度アップ/ダウン` を送信する。
- `shift` + `backspace` を押したときに `delete` を送信する。
- カスタムショートカットの作成もしくは既存の変更: 例えば `ctrl`+`y` を押したときに `ctrl`+`shift`+`z` を送信する。
- `ctrl` + `alt` + `esc` を押したときにカスタムコードを実行する。

## 設定

この機能を有効にするには、`rules.mk` に `KEY_OVERRIDE_ENABLE = yes` を追加する必要があります。

次に、`keymap.c` ファイルで、使用する全てのキーオーバーライドを定義する `key_overrides` 配列を定義する必要があります。それぞれのオーバーライドは `key_override_t` 型の値です。`key_overrides` 配列は `NULL` で終了し、`key_override_t` 値へのポインタ (`const key_override_t **`) を含みます。

## キーオーバーライドの作成

`key_override_t` 構造体は、オーバーライドを完全に調整することができるように多くのオプションを持ちます。完全なリファレンスを以下に示します。`key_override_t` 値を手動で作成する代わりに、次の専用の初期化子を使うことをお勧めします:

#### `ko_make_basic(modifiers, key, replacement)`
`key` と `modifiers` が全て押された場合に、`replacement` (キーと修飾キーの組み合わせも可能)を送信する `key_override_t` を返します。このオーバーライドは `modifiers` で指定されていない追加の修飾キーが押されていた場合も有効です。この挙動をカスタマイズするには `ko_make_with_layers_and_negmods` を参照してください。

#### `ko_make_with_layers(modifiers, key, replacement, layers)`
どのレイヤーでオーバーライドが使われたかを定義する `layers` ビットマスクを追加で受け取ります。

#### `ko_make_with_layers_and_negmods(modifiers, key, replacement, layers, negative_mods)`
このオーバーライドを有効化するために押されていてはいけない修飾キーを定義する `negative_mods` ビットマスクを追加で受け取ります。

#### `ko_make_with_layers_negmods_and_options(modifiers, key, replacement, layers, negative_mods, options)`
追加オプションを指定する `options` ビットマスクを追加で受け取ります。利用可能なオプションは `ko_option_t` を参照してください。

さらなるカスタマイズの可能性のために、`key_override_t` を直接作成することができます。これによりさらに多くの動作をカスタマイズできます。詳細と例については以下を読んでください。

## 簡単な例

これは `shift` + `backspace` が押されたときに `delete` を送信する前述の例をどのように実現するかを示します:

```c
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// これは使用する全てのキーオーバーライドをグローバルに定義します
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
	NULL // オーバーライドの配列は Null で終了します！
};
```

## 中程度の難易度の例

### メディアコントロールと画面の明るさ

この例では、キーオーバーライドを使うことでメディアと音量、画面の明るさを制御するように単一のキーを設定します。

- キーは、キーマップで `再生/停止` を送信するよう設定されています。

次のキーオーバーライドが設定されます:

- `Ctrl` + `再生/停止` で `次の曲` を送信します。
- `Ctrl` + `Shift` + `再生/停止` で `前の曲` を送信します。
- `Alt` + `再生/停止` で `音量アップ` を送信します。
- `Alt` + `Shift` + `再生/停止` で `音量ダウン` を送信します。
- `Ctrl` + `Alt` + `再生/停止` で `輝度アップ` を送信します。
- `Ctrl` + `Alt` + `Shift` + `再生/停止` で `輝度ダウン` を送信します。


```c
const key_override_t next_track_override =
	ko_make_with_layers_negmods_and_options(
    	MOD_MASK_CTRL,       // トリガー修飾キー: ctrl
    	KC_MPLY,             // トリガーキー: 再生/停止
    	KC_MNXT,             // 置換キー
    	~0,                  // 全てのレイヤーで有効化
    	MOD_MASK_SA,         // shift や alt が押されている場合は有効化しない
    	ko_option_no_reregister_trigger); // Ctrl を離したあとに再生キーが再度登録されないことを指定する

const key_override_t prev_track_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CS, KC_MPLY,
											KC_MPRV, ~0, MOD_MASK_ALT, ko_option_no_reregister_trigger);

const key_override_t vol_up_override = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT, KC_MPLY,
											KC_VOLU, ~0, MOD_MASK_CS, ko_option_no_reregister_trigger);

const key_override_t vol_down_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SA, KC_MPLY,
											KC_VOLD, ~0, MOD_MASK_CTRL, ko_option_no_reregister_trigger);

const key_override_t brightness_up_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CA, KC_MPLY,
											KC_BRIU, ~0, MOD_MASK_SHIFT, ko_option_no_reregister_trigger);

const key_override_t brightness_down_override = ko_make_basic(MOD_MASK_CSA, KC_MPLY, KC_BRID);

// これは使用する全てのキーオーバーライドをグローバルに定義します
const key_override_t **key_overrides = (const key_override_t *[]){
	&next_track_override,
	&prev_track_override,
	&vol_up_override,
	&vol_down_override,
	&brightness_up_override,
	&brightness_down_override,
	NULL
};
```

### 柔軟な macOS 対応のグレイブエスケープ
[グレイブエスケープ機能](ja/feature_grave_esc.md) は設定可能な範囲が限定されており、[macOS で使うとバグがあります](ja/feature_grave_esc.md#caveats)。キーオーバーライドを使ってグレイブエスケープと同様の機能を実現できますが、よりカスタマイズ性があり、macOS でもバグがありません。

```c
// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRAVE));

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, KC_GRAVE);

const key_override_t **key_overrides = (const key_override_t *[]){
	&tilde_esc_override,
	&grave_esc_override,
	NULL
};
```

macOS で予期せぬバグが発生しないことに加えて、必要に応じて動作を変更することもできます。`GUI` + `ESC` = `` ` `` という設定の代わりに、例えば `Ctrl` + `ESC` = `` ` `` のように任意の他の修飾キーに変更することができます。

## 高度な例
### レイヤーキーとしての修飾キー

fn レイヤーを切り替えるための専用キーが本当に必要ですか？キーオーバーライドを使うと、おそらくそうではありません。この例は `rGUI` + `rAlt` (右 GUI と 右 Alt) を fn レイヤーのような一時レイヤーにアクセスするために使うように設定する方法を示します。これにより、専用のレイヤーキーを使う必要が完全になくなります。もちろん、修飾キーの選択は必要に応じて変更でき、`rGUI` + `rAlt` はここでの単なる例です。

```c
// これはオーバーライドが有効化および無効化されたときに呼ばれます。有効化されると fn レイヤーを有効にし、無効化されると無効にします。
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

const key_override_t fn_override = {.trigger_mods          = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                       //
                                   .layers                 = ~(1 << LAYER_FN),                                          //
                                   .suppressed_mods        = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                       //
                                   .options                = ko_option_no_unregister_on_other_key_down,                 //
                                   .negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL)),          //
                                   .custom_action          = momentary_layer,                                           //
                                   .context                = (void *)LAYER_FN,                                          //
                                   .trigger                = KC_NO,                                                     //
                                   .replacement            = KC_NO,                                                     //
                                   .enabled                = NULL};
```

## キーコード

全てのキーオーバーライドをその場で有効、無効、切替にすることができます。

|キーコード            |説明                                            |同等関数                   |
|----------------------|------------------------------------------------|---------------------------|
|`KEY_OVERRIDE_ON`     |キーオーバーライド機能を有効にする              |`key_override_on(void)`    |
|`KEY_OVERRIDE_OFF`    |キーオーバーライド機能を無効にする              |`key_override_off(void)`   |
|`KEY_OVERRIDE_TOGGLE` |キーオーバーライド機能の ON と OFF を切り替える |`key_override_toggle(void)`|

## `key_override_t` のリファレンス

上級ユーザは、単純な `ko_make` 初期化子が提供するものより、より多くのカスタマイズが必要になる場合があります。このためには、`key_override_t` 値を直接作成し、全てのメンバ変数を設定します。以下は、`key_override_t` の全てのメンバ変数のリファレンスです。

| メンバ変数                                             | 説明                                                                                                                                                                                                                                                                                                                                                                                           |
|--------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `uint16_t trigger`                                     | オーバーライドを動作させる非修飾キーのキーコード。このオーバーライドを有効化するには、このキーコードと必要な修飾キー (`trigger_mods`) を押す必要があります。これをオーバーライドを有効化するキーのキーコードに設定します。`KC_NO` に設定すると、修飾キーのみ押せばよく、非修飾キーは必要ありません。                                                                                         |
| `uint8_t trigger_mods`                                 | 有効化するために押す必要がある修飾キー。もし両側の同じ修飾キー(例えば左 ctrl と 右 ctrl)が設定されている場合、どちらか一方が押されていれば問題ありません(例えば左 ctrl で十分です)。このためには `MOD_MASK_XXX` と `MOD_BIT()` マクロを使います。                                                                                                                                              |
| `layer_state_t layers`                                 | これはビットマスクです！このオーバーライドが適用されるレイヤーを定義します。レイヤー i でこのオーバーライドを使うには、i 番目のビット `(1 << i)` を設定します。                                                                                                                                                                                                                                |
| `uint8_t negative_mod_mask`                            | 押されていてはいけない修飾キー。`(active_modifiers & negative_mod_mask) == 0` でなければなりません。さもなければ、キーオーバーライドは有効化されません。これが true でなくなると、有効なオーバーライドは無効化されます。                                                                                                                                                                      |
| `uint8_t suppressed_mods`                              | オーバーライドが有効な間に「抑制する」修飾キー。修飾キーを抑制するというのは、たとえ修飾キーが押されていたとしても、ホスト OS はその修飾キーが押されていないと認識することを意味します。簡単な例として、トリガー修飾キーを抑制するのに使うことができます。                                                                                                                                    |
| `uint16_t replacement`                                 | このオーバーライドが動作する場合に代替として送信される複合キーコード。これは単純なキーコード、キーと修飾キーの組み合わせ(例えば、`C(KC_A)`)、`KC_NO` (置換キーコードを登録しない場合)が可能です。送信する正しい修飾キーを取得するには、suppressed_mods と組み合わせて使います。                                                                                                               |
| `ko_option_t options`                                  | オーバーライドを有効化するために許可されるアクションのような、オーバーライドの動作を制御するオプション。                                                                                                                                                                                                                                                                                       |
| `bool (*custom_action)(bool activated, void *context)` | NULL でない場合、この関数は提供されたコンテキストとオーバーライドが有効化もしくは無効化されているかのフラグとともに、置換キーが登録される直前に呼び出されます。この関数を使うことで、特定のキーオーバーライドに対していくつかのカスタムアクションを実行できます。`false` を返すと、置換キーは通常のように登録・解除されません。`true` を返すと、オーバーライドは通常通り登録・解除されます。|
| `void *context`                                        | カスタムアクション関数に渡されるコンテキスト。                                                                                                                                                                                                                                                                                                                                                 |
| `bool *enabled`                                        | これが false を指していると、このオーバーライドは使われません。このオーバーライドを常に有効にするには NULL を設定します。                                                                                                                                                                                                                                                                     |

### `ko_option_t` のリファレンス

キーオーバーライドの動作を制御する様々なオプションを持つビットフィールド。

| 値                                          | 説明                                                                                                                                                                                                                       |
|---------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ko_option_activation_trigger_down`         | トリガーキーが押されている場合に有効化できるようにします。                                                                                                                                                                 |
| `ko_option_activation_required_mod_down`    | 必要な修飾キーが押されている場合に有効化できるようにします。                                                                                                                                                               |
| `ko_option_activation_negative_mod_up`      | 押されていてはいけない修飾キーが離されている場合に有効化できるようにします。                                                                                                                                              |
| `ko_option_one_mod`                         | 設定されている場合、オーバーライドを有効化するには `trigger_mods` のいずれかの修飾キーで十分です(修飾キーの論理和)。設定されていない場合、`trigger_mods` の全ての修飾キーが押されている必要があります(修飾キーの論理積)。 |
| `ko_option_no_unregister_on_other_key_down` | 設定されている場合、別のキーが押されてもオーバーライドは無効化されません。本当にこれが必要だとわかっている場合のみ使ってください。                                                                                        |
| `ko_option_no_reregister_trigger`           | 設定されている場合、トリガーキーはオーバーライドが無効化された後で再度登録されることはありません。                                                                                                                        |
| `ko_options_default`                        | `ko_make_xxx` 関数で使われるデフォルトオプション。                                                                                                                                                                         |

## 上級ユーザ向け: 内部の仕組み

このセクションでは、キーオーバーライドがどのように機能するか詳細に説明し、`key_override_t` の各メンバ変数が関わる場所を説明します。キーオーバーライドで提供される全てのオプションを最大限に活用できるようにするには、これを理解することが不可欠です。

#### 有効化

必要なキー (`trigger_mods` + `trigger`) が押された場合、オーバーライドは「有効化」され、キーボードレポートに置換キー (`replacement`) が登録され、`trigger` キーはキーボードレポートから削除されます。オーバーライドが有効な場合に、トリガー修飾キーをキーボードレポートから削除することもできます(`suppressed_mods`)。オーバーライドは `negative_modifiers` のいずれかが押されていた場合、有効化されません。

オーバーライドは3つの異なる場合に有効化されます:

1. トリガーキーが押されて、必要な修飾キーが既に押されている。
2. トリガーキーと他の必要な修飾キーが既に押されている間に、必要な修飾キーが押された。
3. 全ての必要な修飾キーとトリガーキーが既に押されている間に、押されていてはいけない修飾キーが離された。

`option` メンバ変数を使って、これらのイベントのどれがオーバーライドを有効化できるかをカスタマイズします(デフォルト: 3つ全て)。

どの場合も、`trigger` キーが押された _最後の_ 非修飾キーである場合のみ、キーオーバーライドを有効化できます。これは、一般的な OS (macOS、Windows、Linux)が通常のキー入力を処理する挙動をエミュレートします(理解するには: `a` を押したままにし、次に `b` を押したままにし、その後 `shift` を押したままにします。`B` は入力されますが `A` は入力されません)。

#### 無効化

トリガーキー(`trigger_mods`、`trigger`)のいずれかが離されるか、別の非修飾キーが押されるか、`negative_modifiers` のいずれかが押されると、オーバーライドは「無効化」されます。オーバーライドが無効化されると、`replacement` キーがキーボードレポートから削除され、押したままの `suppressed_mods` がキーボードレポートに再度追加されます。デフォルトでは、`trigger` キーがまだ押されていて、それ以降他の非修飾キーが押されていない場合、`trigger` キーはキーボードレポートに再度追加されます。これも、一般的な OS が通常のキー入力を処理する挙動をエミュレートします(理解するには: `a` を押したままにし、次に `b` を押したままにし、さらに `shift` キーを押したままにし、そして `b` を離します。`a` と `shift` キーを押したままにも関わらず `A` は入力されません)。`option` フィールド `ko_option_no_reregister_trigger` を使って、全ての場合にトリガーキーが再登録されないようにします。

#### キーリピート遅延

キーオーバーライドでエミュレートされる、修飾キー入力の一般的な OS 処理の3つ目の挙動は、[「キーリピート遅延」](https://www.dummies.com/computers/pcs/set-your-keyboards-repeat-delay-and-repeat-rate/)です。これが何であるかを説明するために、通常のキーボード入力が主流の OS によってどのように処理されるかもう一度見てみましょう: `a` を押したまますぐ続けて `shift` を押したままにすると、最初に文字 `a` が入力され、少しの間何も入力されず、それから `A` が繰り返し入力されます。`a` を押した直後に shift を押しますが、`A` が入力されるまで少し時間がかかることに注意してください。これは、前述のキーリピート遅延が原因であり、不要な繰り返し文字が入力されないようにする機能です。

これは、修飾キーを離す時にも同様に当てはまります: `shift` キーを押したまま `a` を押すと、`A` が入力されます。そして最初に `shift` を離して続けてすぐに `a` を離すと、少しの間キー `a` を押したままにも関わらず文字 `a` は入力されません。これは、キーリピート遅延時間が経過するまで、修飾された文字が入力されないためです。

この正確な動作はキーオーバーライドでも実装されています: もし `shift` + `a` = `b` というキーオーバーライドが存在するとして、`a` を押して押したままにし、続けて `shift` を押しても、すぐには文字 `b` が入力されません。代わりに、このイベントは、トリガーキー(`a`)が押された瞬間から計測されたキーリピート遅延時間が経過するまで、少しの間延期されます。

キーリピート遅延の間隔は `KEY_OVERRIDE_REPEAT_DELAY` マクロで制御できます。変更するにはこの値を `config.h` ファイルで定義します。デフォルトでは 500ms です。


## コンボとの違い

キーオーバーライドは[コンボ](https://docs.qmk.fm/#/ja/feature_combo)とは大きく異なることに注意してください。コンボはいくつかのキーをほぼ _同時に_ 押す必要があり、非修飾キーの組み合わせで動作します。キーオーバーライドはキーボードのショートカットのように動作します(例えば `ctrl` + `z`): これらは _複数の_ 修飾キーと _1つの_ 非修飾キーの組み合わせで、いくつかのカスタムアクションを実行します。キーオーバーライドは、押されたキーの順序、タイミング、他の押されたキーとの相互作用に関して、通常のキーボードショートカットと同じように動作するように細心の注意を払って実装されています。各キーオーバーライドの動作を本当に微調整するために使えるいくつかのオプション設定があります。キーオーバーライドを使っても、通常のキー押下のキー入力が遅延することはありません。これは本質的にコンボで発生し、望ましくない場合があります。
