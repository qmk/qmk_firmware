# よくある質問

## QMKとは何か？

Quantum Mechanical Keyboardの略である[QMK](https://github.com/qmk)はカスタム キーボードのためのツールをビルドしている人々のグループです。[TMK](https://github.com/tmk/tmk_keyboard)の大幅に修正されたフォークである[QMK ファームウェア](https://github.com/qmk/qmk_firmware)から始めました。

## QMK と TMKの違いは何か？

TMKは[Jun Wako](https://github.com/tmk)によって設計され実装されました。QMK は [Jack Humbert](https://github.com/jackhumbert)のPlanck用TMKのフォークとして始まりました。しばらくして、JackのフォークはTMKからかなり分岐し、2015年にJackはフォークをQMKに名前を変えることにしました。

技術的な観点から、QMKは幾つかの新しい機能を追加したTMKに基づいています。最も注目すべきことは、QMKは利用可能なキーボードの数を増やし、`S()`, `LCTL()` および `MO()` などの高度な機能を実装するためにこれらを使っています。[キーコード](keycodes.md)でこれらのキーコードの完全なリストを見ることができます。

プロジェクトとコミュニティの管理の観点から、TMKは公式にサポートされている全てのキーボードを自分で管理しており、コミュニティのサポートも少し受けています。Separate community maintained forks exist or can be created for other keyboards. デフォルトでは少数のキーマップのみが提供されるため、ユーザは一般的にお互いにキーマップを共有しません。QMKは集中管理されたレポジトリを介して、キーボードとキーマップの両方を共有することを奨励しており、品質基準に準拠する全てのプルリクエストを受け付けます。これらはほとんどコミュニティで管理されますが、必要な場合はQMKチームも支援します。

どちらのアプローチもメリットとデメリットがあり、理に適う場合はTMKとQMKの間でコードは自由に流れます。
