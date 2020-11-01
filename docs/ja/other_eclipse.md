# QMK 開発のための Eclipse セットアップ

<!---
  original document: 0.9.34:docs/other_eclipse.md
  git diff 0.9.34 HEAD -- docs/other_eclipse.md | cat
-->

[Eclipse][1]は Java 開発のために広く使われているオープンソースの [統合開発環境](https://en.wikipedia.org/wiki/Integrated_development_environment) (IDE) ですが、他の言語および用途のためにカスタマイズできる拡張可能なプラグインシステムがあります。

Eclipse のような IDE の使用は、プレーンテキストエディタの使用よりも多くの利点をもたらします。例えば、次のような利点です。
* インテリジェントなコード補完
* コード内の便利なナビゲーション
* リファクタリングツール
* 自動ビルド (コマンドラインは不要)
* Git 用の GUI
* 静的なコード解析
* デバッグ、コードフォーマット、呼び出し階層の表示などの多くのツール。

このページの目的は、AVR ソフトウェアの開発および QMK コードベースで作業するために、Eclipse をセットアップする方法を文章化することです。

このセットアップは現時点では Ubuntu 16.04 でのみテストされていることに注意してください。

# 前提条件
## ビルド環境
始める前に、チュートリアルの[セットアップ](ja/newbs_getting_started.md)のセクションに従う必要があります。特に、[`qmk compile` コマンド](ja/newbs_building_firmware.md#build-your-firmware)でファームウェアをビルドできなければなりません。

## Java
Eclipse は Java アプリケーションであるため、実行するには Java 8 以降をインストールする必要があります。JRE または JDK を選択できますが、Java 開発を行う場合は後者が役に立ちます。

# Eclipse とプラグインのインストール
Eclipse は用途に応じて[いくつかのフレーバー](http://www.eclipse.org/downloads/eclipse-packages/)で提供されます。AVR スタックを構成するパッケージは無いため、Eclipse CDT (C/C++ 開発ツール)から始め、必要なプラグインをインストールする必要があります。

## Eclipse CDT のダウンロードとインストール
システムに既に Eclipse CDT がある場合は、この手順をスキップできます。ただし、より良いサポートのために最新の状態に保つことをお勧めします。

別の Eclipse パッケージをインストールしている場合は、通常は[その上に CDT プラグインをインストール](https://eclipse.org/cdt/downloads.php)することができます。しかし、軽くして、作業中のプロジェクトに必要のないツールが乱雑にならないように、ゼロから再インストールすることをお勧めします。

インストールは非常に簡単です: [5 Steps to install Eclipse](https://eclipse.org/downloads/eclipse-packages/?show_instructions=TRUE) に従い、ステップ3で **Eclipse IDE for C/C++ Developers** を選択します。

あるいは、直接 [Eclipse IDE for C/C++ Developers をダウンロード](http://www.eclipse.org/downloads/eclipse-packages/)([現在のバージョンへの直接リンク](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/neonr))し、選択した場所にパッケージを解凍することもできます (これにより `eclipse` フォルダが作成されます)。

## 最初の起動
インストールが完了したら、<kbd>Launch</kbd> ボタンをクリックします。(パッケージを手動で解凍した場合は、Eclipse をインストールしたフォルダを開き、`eclipse` 実行可能ファイルをダブルクリックします)

Workspace 選択で入力を促された場合は、Eclipse メタデータと通常のプロジェクトを保持するディレクトリを選択します。**`qmk_firmware` ディレクトリを選択しないでください**。これはプロジェクトディレクトリになります。代わりに親フォルダを選択するか、(できれば空の)他のフォルダを選択します(まだ使用していない場合は、デフォルトで問題ありません)。

開始したら、右上の <kbd>Workbench</kbd> ボタンをクリックし、workbench ビューに切り替えます (下部に開始時のようこそ画面をスキップするためのチェックボックスもあります)。

## 必要なプラグインをインストール
注意: プラグインをインストールするごとに、Eclipse を再起動する必要はありません。全てのプラグインがインストールされたら単に1回再起動します。

### [The AVR Plugin](http://avr-eclipse.sourceforge.net/)
これは最も重要なプラグインで、Eclipse が AVR C コードを_理解_できるようになります。[更新サイトを使うための指示](http://avr-eclipse.sourceforge.net/wiki/index.php/Plugin_Download#Update_Site)に従い、未署名コンテンツのセキュリティ警告に同意します。

### [ANSI Escape in Console](https://marketplace.eclipse.org/content/ansi-escape-console)
このプラグインは QMK makefile によって生成された色付きビルド出力を適切に表示するために必要です。

1. <kbd><kbd>Help</kbd> > <kbd>Eclipse Marketplace…</kbd></kbd> を開きます
2. _ANSI Escape in Console_ を検索します
3. プラグインの <samp>Install</samp> ボタンをクリックします
4. 指示に従い、未署名コンテンツのセキュリティ警告に再度同意します。

両方のプラグインがインストールされたら、プロンプトに従って Eclipse を再起動します。

# QMK 用の Eclipse の設定
## プロジェクトのインポート
1. <kbd><kbd>File</kbd> > <kbd>New</kbd> > <kbd>Makefile Project with Existing Code</kbd></kbd> をクリックします
2. 次の画面で:
* _Existing Code Location_ としてリポジトリをクローンしたディレクトリを選択します。
* (オプション) プロジェクトに別の名前を付けます¹ 例えば _QMK_ あるいは _Quantum_;
* _AVR-GCC Toolchain_ を選択します;
* 残りをそのままにして、<kbd>Finish</kbd> をクリックします

![Eclipse での QMK のインポート](http://i.imgur.com/oHYR1yW.png)

3. これでプロジェクトがロードされインデックスされます。左側の _Project Explorer_ から、簡単にファイルを参照できます。

¹ カスタム名でプロジェクトをインポートすると問題が発生するかもしれません。正しく動作しない場合は、デフォルトのプロジェクト名 (つまり、ディレクトリの名前、おそらく `qmk_firmware`) のままにしてみてください。

## キーボードのビルド
ここで、プロジェクトをクリーンし、選択したキーマップをビルドする make target を設定します。

1. 画面の右側で、<kbd>Make Target</kbd> タブを選択します
2. フォルダツリーを選択したキーボードまで展開します。例えば、`qmk_firmware/keyboards/ergodox`
3. キーボードフォルダを右クリックして、<kbd>New…</kbd> を選択します (あるいはフォルダを選択し、ツリーの上にある <kbd>New Make Target</kbd> アイコンをクリックします)
4. ビルド target の名前を選択します。例えば、_clean \<your keymap\>_
5. Make Target: これはコマンドラインからビルドする時に `make` に渡す引数です。target 名がこれらの引数と一致しない場合は、<kbd>Same as target name</kbd> のチェックを外し、正しい引数を入力します。例えば、`clean <your keymap>`
6. 他のオプションはチェックしたままにして、<kbd>OK</kbd> をクリックします。これで、選択されたキーボードの下に、make target が表示されます。
7. (オプション) target ツリーの上にある <kbd>Hide Empty Folders</kbd> アイコンボタンを、ビルド target だけが表示されるように切り替えます。
8. 作成したビルド target をダブルクリックし、ビルドを起動します。
9. 下部の <kbd>Console</kbd> ビューを選択し、実行中のビルドを眺めます。

[1]: https://en.wikipedia.org/wiki/Eclipse_(software)
