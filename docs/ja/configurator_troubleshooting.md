# Configurator トラブルシューティング

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.0:docs/configurator_troubleshooting.md
  git diff 0.9.0 HEAD -- docs/configurator_troubleshooting.md | cat
-->

## 私の .json ファイルが動きません

.json ファイルが QMK Configurator で作ったものの場合、おめでとうございます。バグに遭遇しました。 [qmk_configurator](https://github.com/qmk/qmk_configurator/issues) で報告してください。

そうでない場合は、... 他の .json ファイルを使用しないようにという、上に書いた注意書きを見逃してませんか？

#### レイアウトに余分なスペースがありますか？どうすればいいですか？

もしスペースバーが3つに分かれている場合は、全てスペースバーで埋めるのが最善の方法です。バックスペースや Shift キーについても同じことができます。

#### キーコードってなに？

以下を見てください。

* [基本的なキーコードリファレンス](ja/keycodes_basic.md)
* [高度なキーコードリファレンス](ja/feature_advanced_keycodes.md)

#### コンパイルできません

キーマップの他のレイヤーを再確認して、おかしなキーが存在しないことを確認してください。

## 問題とバグ

私たちは利用者の依頼やバグレポートを常に受け入れています。[qmk_configurator](https://github.com/qmk/qmk_configurator/issues) で報告してください。
