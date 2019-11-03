# コマンド

以前はマジックとして知られていたコマンドは、[ブートマジック](feature_bootmagic.md)を使うためにフラッシュしたりプラグを抜いたりすることなくキーボードの挙動を変更する方法です。この機能と[ブートマジック キーコード](feature_bootmagic.md#keycodes)には多くの重複があります。可能な限り、コマンドでは無くその機能を使うことをお勧めします。

一部のキーボードではコマンドがデフォルトで無効になっています。その場合、`rules.mk`内で明示的に有効にする必要があります:

```make
COMMAND_ENABLE = yes
```

## 使用法

コマンドを使うには、`IS_COMMAND()`マクロで定義されたキーの組み合わせを押し続けます。デフォルトでは、これは左シフト+右シフトです。次に、目的のコマンドに対応するキーを押します。例えば、現在のQMKバージョンをQMKツールボックス コンソールに出力するには、左Shift+右Shift+`V`を押します。

## 設定

コマンドのためのキーの割り当てを変更したい場合は、キーボードあるいはキーマップレベルのどちらかで、`config.h`にこれらを`#define` します。ここで割り当てる全てのキーコードは`KC_`接頭辞を省略する必要があります。

| 定義 | デフォルト | 説明 |
|------------------------------------|--------------------------------|------------------------------------------------|
| `IS_COMMAND()` | `(get_mods() == MOD_MASK_SHIFT)` | コマンドをアクティブにするキーの組み合わせ |
| `MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS` | `true` | ファンクション行を使ってデフォルトのレイヤを設定 |
| `MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS` | `true` | 数字キーでデフォルトのレイヤを設定 |
| `MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM` | `false` | `MAGIC_KEY_LAYER0..9`を使ってデフォルトのレイヤを設定 |
| `MAGIC_KEY_DEBUG` | `D` | シリアルを介してデバッグを切り替え |
| `MAGIC_KEY_DEBUG_MATRIX` | `X` | キーマトリックス デバッグの切り替え |
| `MAGIC_KEY_DEBUG_KBD` | `K` | キーボード デバッグの切り替え |
| `MAGIC_KEY_DEBUG_MOUSE` | `M` | マウス デバッグの切り替え |
| `MAGIC_KEY_CONSOLE` | `C` | コマンド コンソールを有効にする |
| `MAGIC_KEY_VERSION` | `V` | コンソールに実行中のQMKバージョンを出力 |
| `MAGIC_KEY_STATUS` | `S` | コンソールに現在のキーボードの状態を出力 |
| `MAGIC_KEY_HELP` | `H` | コンソールにコマンドのヘルプを出力 |
| `MAGIC_KEY_HELP_ALT` | `SLASH` | コンソールにコマンドのヘルプを出力 (代替) |
| `MAGIC_KEY_LAYER0` | `0` | レイヤ 0 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER0_ALT` | `GRAVE` | レイヤ 0 をデフォルトレイヤにする (代替) |
| `MAGIC_KEY_LAYER1` | `1` | レイヤ 1 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER2` | `2` | レイヤ 2 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER3` | `3` | レイヤ 3 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER4` | `4` | レイヤ 4 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER5` | `5` | レイヤ 5 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER6` | `6` | レイヤ 6 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER7` | `7` | レイヤ 7 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER8` | `8` | レイヤ 8 をデフォルトレイヤにする |
| `MAGIC_KEY_LAYER9` | `9` | レイヤ 9 をデフォルトレイヤにする |
| `MAGIC_KEY_BOOTLOADER` | `B` | ブートローダにジャンプする |
| `MAGIC_KEY_BOOTLOADER_ALT` | `ESC` | ブートローダにジャンプする (代替) |
| `MAGIC_KEY_LOCK` | `CAPS` | 何も入力できないようにキーボードをロック |
| `MAGIC_KEY_EEPROM` | `E` | 保存されたEEPROM設定をコンソールに出力 |
| `MAGIC_KEY_EEPROM_CLEAR` | `BSPACE` | EEPROMをクリア |
| `MAGIC_KEY_NKRO` | `N` | Nキー ロールオーバーの切り替え (NKRO) |
| `MAGIC_KEY_SLEEP_LED` | `Z` | コンピュータがスリープの時にLEDを切り替え |
