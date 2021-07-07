# PR チェックリスト

<!---
  original document: 0.10.7:docs/pr_checklist.md
  git diff 0.10.7 HEAD -- docs/pr_checklist.md | cat
-->

これは、提出された PR を QMK の協力者がレビューする際に何をチェックするのかの非網羅的なチェックリストです。

これらの推奨事項に矛盾がある場合は、このドキュメントに対して [issue を開く](https://github.com/qmk/qmk_firmware/issues/new)か、[Discord](https://discord.gg/Uq7gcHh) の QMK コラボレータに連絡することをお勧めします。

## 一般的な PR

- PRは、ソースリポジトリ上の `master` ではないブランチを使って提出する必要があります
    - これは、あなたの PR にとって別のブランチをターゲットにするという意味ではなく、むしろ自分の master ブランチで作業をしていないという意味です
    - もし PR の提出者が自分の `master` ブランチを使っている場合は、マージ後に ["git の使い方"](https://docs.qmk.fm/#/ja/newbs_git_using_your_master_branch) ページへのリンクが表示されます - (このドキュメントの最後にはメッセージの内容が含まれます)
- 新しく追加されたディレクトリとファイル名は小文字でなければなりません
    - 上流のソースが元々大文字を使っていた場合 (ChibiOS や他のリポジトリからインポートしたファイルなど)、このルールは緩和されるかもしれません
    - 十分な正当性がある場合 (既存のコアファイルとの整合性など) は、このルールを緩和することができます。
        - ボードデザイナーがキーボードの名前を大文字にした場合は、十分な正当性とはみとめられません
- すべての `*.c` および `*.h` ソースファイルの有効なライセンスヘッダ
    - 一貫性のために GPL2/GPL3 が推奨されています
    - 他のライセンスも許可されていますが、GPL と互換性があり、再配布が許可されていなければなりません。異なるライセンスを使うと、PR がマージされるのをほぼ確実に遅らせることになります
- QMK コードベースの「ベストプラクティス」に従う
    - これは網羅的なリストではありませんし、時間が経つにつれて修正される可能性が高いです
    - ヘッダファイルでは、`#ifndef` インクルードガードの代わりに `#pragma once` を使います
    - 「旧式の」 GPIO/I2C/SPI 関数を使用しない - 正当な理由がない限り、QMK の抽象化を使用しなければなりません (怠惰は正当な理由にはなりません)
    - タイミングの抽象化にも従う必要があります:
        - `_delay_ms()` のかわりに `wait_ms()` を。(`#include <util/delay.h>` も消します)
        - `timer_read()` と `timer_read32()` など。 -- タイミング API は [timer.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/timer.h) を参照してください
    - 新しい抽象化が有用だと思う場合は、次のことをお勧めします:
        - 機能が完成するまで自分のキーボードでプロトタイプを作成する
        - Discord の QMK コラボレータと話し合う
        - 個別のコア変更としてそれをリファクタリングする
        - あなたのキーボードからそのコピーを削除する
- PR を開く前にリベースしてマージの競合をすべて修正します (ヘルプやアドバイスが必要な場合は、Discord で QMK コラボレータに連絡してください)。

## キーマップの PR

- 特定のボードファイルをインクルードするよりも `#include QMK_KEYBOARD_H` を推奨します
- レイヤーは  `#define` よりも `enum` が好まれます
- カスタムキーコードは `#define` ではなく `enum` が必要です。最初のエントリには `= SAFE_RANGE` が必要です
- LAYOUT マクロ呼び出しのパラメータの途中の改行ではバックスラッシュ(`\`)は不要です
- スペーシング（コンマまたはキーコードの最初の文字の配置など）に注意を払うと、見栄えの良いキーマップになります

## キーボードの PR

終了した PR（インスピレーションを得るために、以前のレビューコメントセットは、自分のレビューのピンポンをなくすのに役立ちます）:
https://github.com/qmk/qmk_firmware/pulls?q=is%3Apr+is%3Aclosed+label%3Akeyboard

- `info.json`
    - 有効な URL
    - 有効なメンテナ
    - Configurator で正しく表示されること（Ctrl + Shift + I を押してローカルファイルをプレビューし、高速入力をオンにして順序を確認する）
- `readme.md`
    - 標準テンプレートがあること
    - 書き込みコマンドが `:flash` で終わっていること
    - 有効なハードウェアの入手方法へのリンク (手配線の場合を除く) -- プライベートな共同購入は問題ありませんが、一回限りのプロトタイプは疑問視されます。オープンソースの場合は、ファイルへのリンクを提供してください
    - ボードをブートローダーモードにリセットする方法を明確に説明してください
    - キーボードの写真、できれば PCB の写真も添付してください
- `rules.mk`
    - `MIDI_ENABLE`、`FAUXCLICKY_ENABLE`、`HD44780_ENABLE` は削除されました
    - `# Enable Bluetooth with the Adafruit EZ-Key HID` は `# Enable Bluetooth` に変更されました
    - 機能の有効化に関する `(-/+サイズ)` コメントはなくなりました
    - ブートローダが指定されている場合は、代替ブートローダのリストを削除します
    - [mcu_selection.mk](https://github.com/qmk/qmk_firmware/blob/master/quantum/mcu_selection.mk)の同等の MCU と比較した場合、同じ値の場合、デフォルトの MCU パラメータの再定義がないこと
- キーボードの `config.h`
    - `PRODUCT` 値に `MANUFACTURER` を繰り返さないでください
    - `#define DESCRIPTION` は要りません
    - マジックキーオプション、 MIDI オプション、HD44780 コンフィギュレーションは要りません
    - ユーザー設定の設定可能な `＃define` はキーマップ `config.h` に移動する必要があります
    - "`DEBOUNCING_DELAY`" の代りに "`DEBOUNCE`" を使います
    - キーボードが QMK で起動するために最低限必要なコードが存在する必要があります
        - マトリックスと重要なデバイスの初期化コード
        - (カスタムキーコードや特別なアニメーションなど)商用キーボードの既存の機能をミラーリングする場合は、`default` ではないキーマップを使って処理する必要があります
- `keyboard.c`
    - 空の `xxxx_xxxx_kb()` または他の weak-define のデフォルト実装関数が削除されていること
    - コメントアウトされた関数も削除されていること
    - `matrix_init_board()` などが `keyboard_pre_init_kb()` に移行されました。[keyboard_pre_init*](https://docs.qmk.fm/#/ja/custom_quantum_functions?id=keyboard_pre_init_-function-documentation) を参照してください
    - カスタムマトリックスを使用する場合は、`CUSTOM_MATRIX = lite` を選択し、標準のデバウンスを許可します。[マトリックスコードの部分置き換え](https://docs.qmk.fm/#/ja/custom_matrix?id=lite) を参照してください
- `keyboard.h`
    - 先頭に `#include "quantum.h"` を置きます
    - `LAYOUT` マクロは、該当する場合は標準の定義を使用してください
        - 該当する場合はコミュニティレイアウトマクロ名を使用します (`LAYOUT`/`LAYOUT_all`よりも優先されます)
- キーマップの `config.h`
    - キーボードから `rules.mk` や `config.h` が重複していないこと
- `keymaps/default/keymap.c`
    - `QMKBEST`/`QMKURL` が削除されていること
    - `MO(_LOWER)`および `MO(_RAISE)`キーコードまたは同等のものを使用していて、キーマップに両方のキーを押したときに adjust レイヤーがある場合 - キーマップに直接 adjust レイヤーに入るキーコードがない場合（`MO(_ADJUST)`のように）次のように記述します...
        ```
        layer_state_t layer_state_set_user(layer_state_t state) {
          return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
        }
        ```
        ...キーマップの `process_record_user()` 内で `layer_on()`、 `update_tri_layer()` を手動で処理する代わりに。
- default (および via) のキーマップは「素朴」でなければなりません。
    - 他のユーザーが独自のユーザー固有のキーマップを開発するための「クリーンな状態」として使用するための最低限のもの。
    - これらのキーマップで推奨される標準レイアウト（可能な場合）
- PR の提出者は、同じ PR に機能を紹介する個人的な（または豪華な）キーマップを持たせることができますが、「デフォルト」のキーマップに埋め込むべきではありません
- PR の提出者はまた、既存の商用キーボードへ QMK を移植する場合、その商用製品の既存の機能を反映する「製造業者に一致する」キーマップを持つことができます

さらに、ChibiOS に固有で:
- 既存の ChibiOS ボード定義を使用することを**強く**推奨します。
    - 多くの場合、同等の Nucleo ボードは、同じファミリの異なるフラッシュサイズまたはわずかに異なるモデルで使用できます。
        - 例：STM32L082KZ の場合、STM32L073RZ に類似しているため、rules.mkで `BOARD = ST_NUCLEO64_L073RZ` を使用できます。
    - QMK は ChibiOS のアップグレード時のメンテナンス負担が継続的に発生するため、可能な限りカスタムボード定義を持たないように移行しています。
- ボードの定義が避けられない場合、`board.c` には標準の `__early_init()` (通常の ChibiOS ボードの定義と同じ) と空の `boardInit()` を実装しなければなりません。
    - Arm/ChibiOS [早期初期化](https:/docs.qmk.fm/#/ja/platformdev_chibios_earlyinit?id=board-init)を参照してください
    - `__early_init()`は、`early_hardware_init_pre()` または `early_hardware_init_post()` で適切に置き換える必要があります
    - `boardInit()` は `board_init()` に移行する必要があります

## コアの PR

- `develop` ブランチをターゲットにする必要があります。これは、その後、breaking change のタイムラインで `master` にマージされます。
- その他の注意事項 TBD
    - 投稿された変更の幅を考えると、コアはもっと主観的です

---

## 注意事項

人々が自分の `master` ブランチを使用する場合、マージ後に以下を投稿します：

```
For future reference, we recommend against committing to your `master` branch as you've done here, because pull requests from modified `master` branches can make it more difficult to keep your QMK fork updated. It is highly recommended for QMK development – regardless of what is being done or where – to keep your master updated, but **NEVER** commit to it. Instead, do all your changes in a branch (branches are basically free in Git) and issue PRs from your branches when you're developing.

There are instructions on how to keep your fork updated here:

[**Best Practices: Your Fork's Master: Update Often, Commit Never**](https://docs.qmk.fm/#/newbs_git_using_your_master_branch)

[Fixing Your Branch](https://docs.qmk.fm/#/newbs_git_resynchronize_a_branch) will walk you through fixing up your `master` branch moving forward. If you need any help with this just ask.

Thanks for contributing!
```
