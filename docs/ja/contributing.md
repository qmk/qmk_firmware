# 貢献方法

👍🎉 まず、これを読み貢献する時間を作ってくれてありがとうございます！🎉👍

サードパーティの貢献は、QMKの成長と改善に役立ちます。プルリクエストと貢献プロセスを貢献者とメンテナの両方にとって便利で簡単なものにしたいです。この目的のために、大きな変更をせずにプルリクエストが受け入れられるように貢献者向けのガイドラインをまとめました。

* [プロジェクトの概要](#project-overview)
* [コーディング規約](#coding-conventions)
* [一般的なガイドライン](#general-guidelines)
* [行動規範は私にとって何を意味しますか？](#what-does-the-code-of-conduct-mean-for-me)

## この全てを読みたくはありません！単純に質問があります！

QMKについて質問したい場合は、[OLKB Subreddit](https://reddit.com/r/olkb) あるいは [Discord](https://discord.gg/Uq7gcHh) でそうすることができます。

以下の事を覚えておいてください:

* 誰かがあなたの質問に答えるのに数時間掛かるかもしれません。しばらくお待ちください！
* QMKに関わる全ての人が彼らの時間とエネルギーを寄付しています。QMKに関する作業や質問への回答に対する報酬はありません。
* できるだけ簡単に答えられるように質問してみてください。その方法が分からない場合は、以下に幾つかの良いガイドがあります:
   * https://opensource.com/life/16/10/how-ask-technical-questions
   * http://www.catb.org/esr/faqs/smart-questions.html

# プロジェクトの概要

QMKは主にCで書かれており、特定の機能と部分はC++で書かれています。キーボードの中の組み込みプロセッサ、特に AVR ([LUFA](http://www.fourwalledcubicle.com/LUFA.php)) と ARM ([ChibiOS](http://www.chibios.com)) を対象にしています。すでにArduinoプログラミングに精通している場合は、多くの概念と制限がおなじみのものです。QMKに貢献するにはArduinoを使用した経験は必要ありません。

<!-- FIXME: We should include a list of resources for learning C here. -->

# どこで助けを得られますか？

助けが必要であれば、[issueを開く](https://github.com/qmk/qmk_firmware/issues) か [Discordで会話する](https://discord.gg/Uq7gcHh)ことができます。

# どうやって貢献することができますか？

以前にオープンソースに貢献したことはありませんか？QMKで貢献がどのように機能するかが疑問ですか？ここに簡単な説明があります！

0. [GitHub](https://github.com) アカウントにサインアップします。
1. 貢献するためのキーマップを結合する、解決に興味がある[問題を見つける](https://github.com/qmk/qmk_firmware/issues)、あるいは追加したい[機能](https://github.com/qmk/qmk_firmware/issues?q=is%3Aopen+is%3Aissue+label%3Afeature)を見つけます。
2. 問題に関連付けられているレポジトリをあなたのGitHubアカウントにフォークします。これは、`your-GitHub-username/qmk_firmware`の下にレポジトリのコピーを持つことを意味します。
3. `git clone https://github.com/github-username/repository-name.git` を使ってローカルマシンにレポジトリをクローンします。
4. 新しい機能に取り組んでいる場合は、issueを開きこれから行う作業について話し合うことを検討してください。
5. `git checkout -b branch-name-here`を使って修正用の新しいブランチを作成します。
6. 解決しようとしている問題、あるいは追加したい機能について適切な変更を加えます。
7. `git add insert-paths-of-changed-files-here` を使って変更されたファイルの内容をgitがプロジェクトの状態を管理するために使用する "snapshot"、インデックスとしても知られている、に追加します。
8. `git commit -m "Insert a short message of the changes made here"`を使って、説明的なメッセージとともにインデックスの内容を保存します。
9. `git push origin branch-name-here`を使ってGitHub上のレポジトリに変更をプッシュします。
10. プルリクエストを[QMK Firmware](https://github.com/qmk/qmk_firmware/pull/new/master)にサブミットします。
11. 行われた変更の簡単な説明と、変更に関する問題またはバグ番号で、プルリクエストにタイトルを付けます。例えば、issueに "Added more log outputting to resolve #4352" のようなタイトルをつけることができます。
12. プルリクエストの説明では、行った変更、行ったプルリクエストに存在すると思われる問題、およびメンテナに対する質問を説明します。プルリクエストが完ぺきではない場合(プルリクエストが無い場合)は問題ありません。レビュワーが問題の修正と改善を手伝います。
13. プルリクエストがメンテナによってレビューされるのを待ちます。
14. レビューをしているメンテナが推奨する場合は、プルリクエストに変更を加えます。
15. プルリクエストがマージされた後で成功を祝います！

# コーディング規約

私たちのスタイルのほとんどは簡単に理解できます。C あるいは Python のいずれかに精通している場合は、ローカルスタイルにそれほど問題はないはずです。

* [コーディング規約 - C](coding_conventions_c.md)
* [コーディング規約 - Python](coding_conventions_python.md)

# 一般的なガイドライン

QMKには幾つかの異なるタイプの変更があり、それぞれ異なるレベルの厳密さが必要です。どのような種類の変更を行っても、次のガイドラインに留意してください。

* PRを論理単位に分割します。例えば、2つの個別の機能をカバーする1つのPRを送信するのではなく、代わりに機能ごとに個別のPRをサブミットします。
* コミットする前に、`git diff --check` を使って不要な空白を確認します。
* コードの変更が実際にコンパイルされることを確認してください。
   * キーマップ: `make keyboard:your_new_keymap` がエラーを返さないことを確認してください。
   * キーボード: `make keyboard:all` がエラーを返さないことを確認してください。
   * コア: `make all`がエラーを返さないことを確認してください。
* コミットメッセージがそれ自体で理解できることを確認してください。最初の行に短い説明(70文字以内)を入れ、2行目は空にし、3行目以降では必要に応じてコミットを詳細に説明する必要があります。例:

```
kerpleplorkのfronzlebop を調整します

kerpleplork はエラーコード 23 で連続的に失敗していました。根本的な原因はfronzlebop設定で、これによりkerpleplorkはN回の繰り返しごとにアクティブになります。

Limited experimentation on the devices I have available shows that 7 is high enough to avoid confusing the kerpleplork, but I'd like to get some feedback from people with ARM devices to be sure.
```

!> **重要:** デフォルト以外のキーマップ、ユーザスペースおよびレイアウトのようなユーザコードへのバグ修正あるいは改善に貢献したい場合は、PRにコードの元の提出者にタグをつけてください。Git と GitHub のスキルレベルに関係なく、多くのユーザが知らないうちにコードが変更されることに混乱したりイライラしたりするかもしれません。

## ドキュメント

ドキュメントはQMKへの貢献を始める最も簡単な方法の1つです。ドキュメントが間違っているか不完全な場所を見つけ、これらを修正するのは簡単です！またドキュメントを編集する人を非常に必要としています。編集するスキルがあるが、どこにどのように飛び乗ればいいのか分からない場合は、[助けをもとめて](#where-can-i-go-for-help)ください！

全てのドキュメントは`qmk_firmware/docs` ディレクトリの中にあります。あるいはwebベースのワークフローを使いたい場合は、http://docs.qmk.fm/ の各ページの上部にある "Suggest An Edit" をクリックすることができます。

ドキュメントの中にコードの例を提供する場合は、ドキュメント内の他の場所で使用されている命名規則を順守してください。例えば、一貫性を保つために、`my_layers` あるいは `my_keycodes` として列挙型を標準化します:

```c
enum my_layers {
  _FIRST_LAYER,
  _SECOND_LAYER
};

enum my_keycodes {
  FIRST_LAYER = SAFE_RANGE,
  SECOND_LAYER
};
```

## キーマップ

ほとんどの初めてのQMK貢献者は、個人のキーマップから始めます。We try to keep keymap standards pretty casual (keymaps, after all, reflect the personality of their creators) but we do ask that you follow these guidelines to make it easier for others to discover and learn from your keymap.

* [the template](documentation_templates.md)を使って`readme.md`を書きます。
* 全てのキーマップのPRは潰されるため、コミットがどのように潰されるかを気にする場合は、自分で行う必要があります。
* キーマップ PRで機能をまとめないでください。最初に機能をサブミットし、次にキーマップのための2つ目のPRをサブミットします。
* `Makefile`をキーマップ フォルダ (もう使われていません)に含めないでください。
* ファイルヘッダの著作権を更新します (`%YOUR_NAME%`を探します)

## キーボード

キーボードはQMKの存在理由です。一部のキーボードはコミュニティによって管理されていますが、他のキーボードは特定のキーボードを作成する責任者によって管理されています。`readme.md` は、特定のキーボードを管理しているユーザを示すはずです。特定のキーボードに関する質問がある場合、[Issueを開いて](https://github.com/qmk/qmk_firmware/issues)質問にメンテナをタグ付けしてください。

また以下のガイドラインに従うことをお願いします:

* [the template](documentation_templates.md)を使って`readme.md`を書きます。
* コミットの数を適切に保ってください。そうでなければあなたのPRを潰します。
* コア機能を新しいキーボードにまとめないでください。最初に機能をサブミットし、次にキーボード用に別のPRをサブミットしてください。
* Name `.c`/`.h` file after the immediate parent folder, eg `/keyboards/<kb1>/<kb2>/<kb2>.[ch]`
* キーボード フォルダに`Makefile`を含めないでください (それらは使われなくなりました)
* ファイルヘッダの著作権を更新します (`%YOUR_NAME%`を探します)

## Quantum/TMK コア

新しい機能をビルドするために多くの作業を行う前に、最適な方法で実装していることを確認する必要があります。[QMKの理解](understanding_qmk.md)を読むことで、QMKの基本的な理解を得ることができます。これはあなたをQMKのプログラム フローのツアーに連れて行きます。From here you should talk to us to get a sense of the best way to implement your idea. これを行うには主に2つの方法があります:

* [Discordでのチャット](https://discord.gg/Uq7gcHh)
* [Issueを開く](https://github.com/qmk/qmk_firmware/issues/new)

機能とバグ修正のPRは全てのキーボードに影響します。また、私たちはQMKの再編も進めています。このため、実装が行われる前に特に重要な変更について議論することが特に重要です。最初に私たちと話をせずにPRを開いた場合、あなたの選択が私たちの計画した方向とうまく合わない場合は幾つかの重要な再作業を行う準備をしてください。

機能やバグの修正に取り組む時に留意すべき幾つかの事があります。

* **デフォルトで無効** - QMKがサポートするほとんどのチップでメモリがかなり制限されており、現在のキーマップが壊れていないことが重要です。ですので、あなたの機能をオフにするのではなく**オン**にするようにしてください。デフォルトでオンにすべき場合、あるいはコードのサイズを小さくする必要がある場合は、相談してください。
* **サブミットする前にローカルでコンパイル** - これが明白であることを願っていますが、コンパイルする必要があります。私たちのTravisシステムは全ての問題をキャッチしますが、結果が返ってくるのを待つ代わりに幾つかのキーボードをコンパイルする方が一般的に速いです。
* **リビジョンと異なるチップベースを考慮** - 僅かに異なる設定、さらには異なるチップベースを可能にするリビジョンを持つキーボードが幾つかあります。ARMおよびAVRでサポートされる機能を作成する、あるいは動作しないプラットフォームでは自動的に無効化するようにしてください。
* **機能の説明** - 新しいファイルあるいは既存のファイルの一部として、`docs/`の中にドキュメント化します。文章化しないと、他の人はあなたの苦労から利益を得ることができません。

また以下のガイドラインに従うことをお願いします:

* コミットの数を適切に保ってください。そうでなければあなたのPRを潰します。
* キーボードあるいはキーマップをコアの変更にまとめないでください。コアの変更を最初にサブミットしてください。
* 機能のための[ユニット テスト](unit_testing.md)を書いてください。
* 編集しているファイルのスタイルに従います。スタイルが明確でないか、スタイルが混在している場合は、上記の[コーディング規約](#coding-conventions)に準拠する必要があります。

## リファクタリング

QMKで物事がどのようにレイアウトされるかについて明確なビジョンを維持するために、私たちはリファクタリングを詳細に計画し、変更をする協力者がいます。リファクタリングのアイデアあるいは提案がある場合は、[issueを開いてください](https://github.com/qmk/qmk_firmware/issues)。QMKを改善する方法についてお話ししたいと思います。

# 行動規範は私にとって何を意味しますか？

私たちの[行動規範](https://github.com/qmk/qmk_firmware/blob/master/CODE_OF_CONDUCT.md)は、身元に関係なくあなたがプロジェクトの全員を経緯と礼儀を持って扱う責任があることを意味します。あなたが行動規範に記載されている不適切な行動やコメントの被害者である場合は、私たちはあなたのためにここにおり、私たちのコードに従って虐待者が適切に懲戒せるように最善を尽くします。
