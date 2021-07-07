# コマンド

<!---
  original document: 0.8.94:docs/feature_command.md
  git diff 0.8.94 HEAD -- docs/feature_command.md | cat
-->

コマンド(旧称:マジック)は、ファームウェアを書き込んだり、[ブートマジック](ja/feature_bootmagic.md)を使うためにプラグを抜いたりすることなくキーボードの挙動を変更する方法です。この機能と[ブートマジックキーコード](feature_bootmagic.md#keycodes)には多くの重複があります。可能な限り、コマンドでは無くブートマジックキーコードの機能を使うことをお勧めします。

一部のキーボードではコマンドがデフォルトで無効になっています。その場合、`rules.mk` 内で明示的に有効にする必要があります:

```make
COMMAND_ENABLE = yes
```

## 使用法

コマンドを使うには、`IS_COMMAND()` マクロで定義されたキーの組み合わせを押し続けます。デフォルトでは、これは「左Shift + 右Shift」です。次に、目的のコマンドに対応するキーを押します。例えば、現在の QMK バージョンを QMK Toolbox コンソールに出力するには、「左Shift + 右Shift + `V`」を押します。

## 設定

コマンドのためのキーの割り当てを変更したい場合は、キーボードあるいはキーマップレベルのどちらかで、`config.h` にこれらを `#define` します。ここで割り当てる全てのキーコードは `KC_` 接頭辞を省略する必要があります。

| 定義 | デフォルト | 説明 |
|------------------------------------|--------------------------------|------------------------------------------------|
| `IS_COMMAND()` | `(get_mods() == MOD_MASK_SHIFT)` | コマンドをアクティブにするキーの組み合わせ |
| `MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS` | `true` | ファンクション行を使ってデフォルトレイヤーを設定 |
| `MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS` | `true` | 数字キーでデフォルトレイヤーを設定 |
| `MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM` | `false` | `MAGIC_KEY_LAYER0..9` を使ってデフォルトレイヤーを設定 |
| `MAGIC_KEY_DEBUG` | `D` | シリアルを介するデバッグの切り替え |
| `MAGIC_KEY_DEBUG_MATRIX` | `X` | キーマトリックスのデバッグの切り替え |
| `MAGIC_KEY_DEBUG_KBD` | `K` | キーボードのデバッグの切り替え |
| `MAGIC_KEY_DEBUG_MOUSE` | `M` | マウスのデバッグの切り替え |
| `MAGIC_KEY_CONSOLE` | `C` | コマンドコンソールを有効にする |
| `MAGIC_KEY_VERSION` | `V` | コンソールに実行中の QMK バージョンを出力 |
| `MAGIC_KEY_STATUS` | `S` | コンソールに現在のキーボードの状態を出力 |
| `MAGIC_KEY_HELP` | `H` | コンソールにコマンドのヘルプを出力 |
| `MAGIC_KEY_HELP_ALT` | `SLASH` | コンソールにコマンドのヘルプを出力 (代替) |
| `MAGIC_KEY_LAYER0` | `0` | レイヤー 0 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER0_ALT` | `GRAVE` | レイヤー 0 をデフォルトレイヤーにする (代替) |
| `MAGIC_KEY_LAYER1` | `1` | レイヤー 1 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER2` | `2` | レイヤー 2 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER3` | `3` | レイヤー 3 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER4` | `4` | レイヤー 4 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER5` | `5` | レイヤー 5 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER6` | `6` | レイヤー 6 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER7` | `7` | レイヤー 7 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER8` | `8` | レイヤー 8 をデフォルトレイヤーにする |
| `MAGIC_KEY_LAYER9` | `9` | レイヤー 9 をデフォルトレイヤーにする |
| `MAGIC_KEY_BOOTLOADER` | `B` | ブートローダにジャンプする |
| `MAGIC_KEY_BOOTLOADER_ALT` | `ESC` | ブートローダにジャンプする (代替) |
| `MAGIC_KEY_LOCK` | `CAPS` | 何も入力できないようにキーボードをロック |
| `MAGIC_KEY_EEPROM` | `E` | 保存された EEPROM 設定をコンソールに出力 |
| `MAGIC_KEY_EEPROM_CLEAR` | `BSPACE` | EEPROM をクリア |
| `MAGIC_KEY_NKRO` | `N` | N キーロールオーバー (NKRO) の有効・無効を切り替え |
| `MAGIC_KEY_SLEEP_LED` | `Z` | コンピュータがスリープの時に LED を切り替え |
