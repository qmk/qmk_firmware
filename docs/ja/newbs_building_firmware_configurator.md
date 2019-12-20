# QMK Configurator

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: ed0575fc8:docs/newbs_building_firmware_configurator.md
  git diff ed0575fc8 HEAD docs/newbs_building_firmware_configurator.md | cat
-->

[QMK Configurator](https://config.qmk.fm) は、QMKファームウェアの hex ファイルを生成するオンライングラフィカルユーザーインターフェイスです。

?> **次の手順を順番に実行してください。**

[Video Tutorial](https://youtu.be/tx54jkRC9ZY) を見てください。

QMK Configurator は Chrome/Firefox で最適に動作します。

!> **KLE や kbfirmware などの他のツールのファイルは、QMK Configurator と互換性がありません。それらをロードしたり、インポートしたりしないでください。QMK Configurator は異なるツールです。**

## キーボードを選ぶ

ドロップダウンボックスをクリックして、キーマップを作成するキーボードを選択します。

?> **キーボードに複数のバージョンがある場合は、正しいバージョンを選択してください。**

大事なことなのでもう一度言います。

!> **正しいバージョンを選択してください!**

キーボードが QMK を搭載していると宣伝されていてもリストにない場合は、開発者がまだ作業中か、私たちがまだマージするきっかけがなかった可能性があります。
アクティブな [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard) がない場合、[qmk_firmware](https://github.com/qmk/qmk_firmware/issues)で報告して、その特定のキーボードのサポートをリクエストします。
製作者自身の github アカウントにある QMK 搭載キーボードもあります。
それも再確認してください。

## キーボードのレイアウトを選択する

作成したいと思うキーマップに最も近いレイアウトを選択します。一部のキーボードには、まだ十分なレイアウトまたは正しいレイアウトが定義されていません。これらは将来サポートされる予定です。

## キーマップの名前

お好みの名前をキーマップにつけます。

?> コンパイル時に問題が発生した場合は、もしかすると QMK ファームウェアリポジトリに既に同じ名前が存在しているのかもしれません、名前を変更してみてください。

## キーマップを作る

キーコード入力は3つの方法で実行できます。  
1. ドラッグ・アンド・ドロップ
2. レイアウト上の空の場所をクリックして、希望するキーコードをクリックします
3. レイアウト上の空の場所をクリックして、キーボードの物理キーを押します

マウスをキーの上に置くと、そのキーコードの機能の短い説明文が出ます。より詳細な説明については以下を見てください。

[Basic Keycode Reference](https://docs.qmk.fm/#/keycodes_basic)    
[Advanced Keycode Reference](https://docs.qmk.fm/#/feature_advanced_keycodes)    

キーマップをサポートするレイアウトが見つからない場合、例えばスペースバーが3分割されていたり、バックスペースが2分割されていたり、シフトが2分割されているような場合、それらを全て埋めてください。

### 例:

3分割のスペースバー: 全てスペースバーで埋めます。

2分割のバックスペース: 両方ともバックスペースで埋めます。

2分割の右シフト: 両方とも右シフトで埋めます。

左シフトとISOサポート用に1つずつ: 両方とも左シフトで埋めます。

5分割だが4キーのみ: 以前やったことがある人を推測して確認するか尋ねてください。

## 後日のためにキーマップを保存する

キーマップに満足するか、または後で作業したい場合は、`Export Keymap' ボタンを押します。上記で選択した名前に .json が追加されたキーマップが保存されます。

後日、`Import Keymap` ボタンを押すことで、この .json ファイルをロードできます。

!> **注意:** このファイルは、kbfirmware.com またはその他のツールに使用される .jsonファイルと同じ形式ではありません。これらのツールにこれを使用したり、QMK Configurator でこれらのツールの .json を使用しようとすると、キーボードが **爆発** する可能性があります。

## ファームウェアファイルを生成する

緑色の `Compile` ボタンを押します。

コンパイルが完了すると、緑色の `Download Firmware` ボタンを押すことができます。

## キーボードに書き込む(フラッシュする)

[ファームウェアを書きこむ](ja/newbs_flashing.md) を参照してください。

## トラブルシューティング

#### 私の .json ファイルが動きません

.json ファイルが QMK Configurator で作ったものの場合、おめでとうございます。バグに遭遇しました。 [qmk_configurator](https://github.com/qmk/qmk_configurator/issues) で報告してください。

そうでない場合は、... 他の .json ファイルを使用しないようにという、上に書いた注意書きを見逃してませんか？

#### レイアウトに余分なスペースがありますか？どうすればいいですか？

もしスペースバーが3つに分かれている場合は、全てスペースバーで埋めるのが最善の方法です。バックスペースやシフトについても同じことができます。

#### キーコードってなに？

以下を見てください。

[Basic Keycode Reference](https://docs.qmk.fm/#/keycodes_basic)    
[Advanced Keycode Reference](https://docs.qmk.fm/#/feature_advanced_keycodes)    

#### コンパイルできません

キーマップの他のレイヤーを再確認して、ランダムなキーが存在しないことを確認してください。

## 問題とバグ

私たちは利用者の依頼やバグレポートを常に受け入れています。[qmk_configurator](https://github.com/qmk/qmk_configurator/issues) で報告してください。
