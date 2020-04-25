# グレイブエスケープ

<!---
  original document: 0.8.123:docs/feature_grave_esc.md
  git diff 0.8.123 HEAD -- docs/feature_grave_esc.md | cat
-->

60% キーボード、または F 行の無い他のレイアウトを使っている場合、専用の Escape キーが無いことに気付くでしょう。グレイブエスケープはグレイブキー (<code>&#96;</code> および `~`) を Escape と共有することができる機能です。

## 使用法

キーマップ内の `KC_GRAVE` キー (通常は`1` キーの左)を `KC_GESC` に置き換えます。ほとんどの場合、このキーは押された時に `KC_ESC` を出力します。ただし、Shift あるいは GUI を押したままにすると、代わりに `KC_GRV` を出力します。

## OS に見えるもの

メアリーがキーボードで GESC を押すと、OS には KC_ESC 文字が見えます。メアリーが Shift を押しながら GESC を押すと、`~` または Shift されたバックティックを出力します。彼女が GUI/CMD/WIN を押したままにすると、単純な <code>&#96;</code> 文字を出力します。

## キーコード

| キー | エイリアス | 説明 |
|---------|-----------|------------------------------------------------------------------|
| `KC_GESC` | `GRAVE_ESC` | 押された場合に Escape。Shift あるいは GUI が押されたままの場合は <code>&#96;</code> |

### 注意事項

macOS では、コマンド+<code>&#96;</code> はデフォルトで "次のウィンドウを操作対象にする" にマップされます。つまりバックティックを出力しません。さらに、ショートカットがキーボード環境設定で変更された場合でも、ターミナルは常にこのショートカットを認識してウィンドウを切り替えます。

## 設定

このことが崩れる可能性のあるキーの組み合わせが幾つかあります。その中には、Windows では Control+Shift+Escape、macOSでは Command+Option+Escape があります。これを回避するには、`config.h` でこれらのオプションを `#define` することができます:

| 定義 | 説明 |
|--------------------------|-----------------------------------------|
| `GRAVE_ESC_ALT_OVERRIDE` | Alt が押された場合、常に Escape を送信する |
| `GRAVE_ESC_CTRL_OVERRIDE` | Control が押された場合、常に Escape を送信する |
| `GRAVE_ESC_GUI_OVERRIDE` | GUI が押された場合、常に Escape を送信する |
| `GRAVE_ESC_SHIFT_OVERRIDE` | Shift が押された場合、常に Escape を送信する |
