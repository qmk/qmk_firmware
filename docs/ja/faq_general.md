# よくある質問

<!---
  original document: d598f01cb:docs/faq_general.md
  git diff d598f01cb HEAD -- docs/faq_general.md | cat
-->

## QMK とは何か？

Quantum Mechanical Keyboard の略である [QMK](https://github.com/qmk) は、カスタムキーボードのためのツールをビルドしている人々のグループです。[TMK](https://github.com/tmk/tmk_keyboard) の大幅に修正されたフォークである [QMK ファームウェア](https://github.com/qmk/qmk_firmware)から始まりました。

## QMK と TMK の違いは何か？

TMK は [Jun Wako](https://github.com/tmk) によって設計され実装されました。QMK は [Jack Humbert](https://github.com/jackhumbert) の Planck 用 TMK のフォークとして始まりました。しばらくして、Jack のフォークは TMK からかなり分岐し、2015年に Jack はフォークを QMK に名前を変えることにしました。

技術的な観点から、QMK は幾つかの新しい機能を追加した TMK に基づいています。最も注目すべきことは、QMK は利用可能なキーコードの数を増やし、`S()`、`LCTL()` および `MO()` などの高度な機能を実装するためにこれらを使っています。[キーコード](keycodes.md)でこれらのキーコードの完全なリストを見ることができます。

プロジェクトとコミュニティの管理の観点から、TMK は公式にサポートされている全てのキーボードを自分で管理しており、コミュニティのサポートも少し受けています。他のキーボード用に別個のコミュニティが維持するフォークが存在するか、作成できます。デフォルトでは少数のキーマップのみが提供されるため、ユーザは一般的にお互いにキーマップを共有しません。QMK は集中管理されたリポジトリを介して、キーボードとキーマップの両方を共有することを奨励しており、品質基準に準拠する全てのプルリクエストを受け付けます。これらはほとんどコミュニティで管理されますが、必要な場合は QMK チームも支援します。

どちらのアプローチもメリットとデメリットがあり、理に適う場合は TMK と QMK の間でコードは自由にやり取りされます。
