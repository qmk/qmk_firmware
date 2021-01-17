# QMK 開発用の Visual Studio Code のセットアップ

<!---
  original document: 0.10.33:docs/other_vscode.md
  git diff 0.10.33 HEAD -- docs/other_vscode.md | cat
-->

[Visual Studio Code](https://code.visualstudio.com/) (VS Code) は多くの異なるプログラミング言語をサポートするオープンソースのコードエディタです。

VS Code のようなフル機能のエディタの使用は、プレーンテキストエディタの使用よりも多くの利点をもたらします。例えば、次のような利点です。:
* インテリジェントなコード補完
* コード内の便利なナビゲーション
* リファクタリングツール
* 自動ビルド (コマンドラインは不要)
* Git 用のグラフィカルなフロントエンド
* デバッグ、コードフォーマット、呼び出し階層の表示などの多くのツール

このページの目的は、QMK ファームウェアを開発するために VS Code をセットアップする方法を文章化することです。

このガイドは Windows および Ubuntu 18.04 で必要な全てを構成する方法を説明します。

# VS Code のセットアップ
はじめに、全てのビルドツールをセットアップし、QMK ファームウェアをクローンする必要があります。まだ設定していない場合は、[セットアップ](ja/newbs_getting_started.md)に進んでください。

## Windows

### 前提条件

* [Git for Windows](https://git-scm.com/download/win) (このリンクはインストーラを保存あるいは実行するように促します)

   1. `Git LFS (Large File Support)` および `Check daily for Git for Windows updates` 以外の全てのオプションを無効にします。
   2. デフォルトのエディタを `Use Visual Studio Code as Git's default editor` に設定します。
   3. ここで使用すべきオプションなので、`Use Git from Git Bash only` オプションを選択します。
   4. `Choosing HTTPS transport backend` については、どちらのオプションでも問題ありません。
   5. `Checkout as-is, commit Unix-style line endings` オプションを選択します。QMK ファームウェアは Unix スタイルのコミットを使います。
   6. 追加のオプションについては、デフォルトのオプションをそのままにします。

  このソフトウェアは、VS Code での Git サポートに必要です。これを含めないことも可能ですが、これを使う方が簡単です。

* [Git Credential Manager for Windows](https://github.com/Microsoft/Git-Credential-Manager-for-Windows/releases) (オプション)

   このソフトウェアは、git 証明書、MFA、パーソナルアクセストークン生成のためのセキュアストレージを提供することで、Git のより良いサポートを提供します。

   これは厳密には必要ありませんが、お勧めします。


### VS Code のインストール

1. [VS Code](https://code.visualstudio.com/) に進み、インストーラをダウンロードします
2. インストーラを実行します

この項は非常に簡単です。ただし、正しく構成されていることを確認するために、しなければならない幾つかの設定があります。

### VS Code の設定

最初に、IntelliSense をセットアップする必要があります。これは厳密には必要ではありませんが、あなたの人生をずっと楽にします。これを行うには、QMK ファームウェアフォルダに `.vscode/c_cpp_properties.json` ファイルを作成する必要があります。これは全て手動で行うことができますが、ほとんどの作業は既に完了しています。

[このファイル](https://gist.github.com/drashna/48e2c49ce877be592a1650f91f8473e8) を取得して保存します。MSYS2 をデフォルトの場所にインストールしなかった、または WSL か LxSS を使っている場合、このファイルを編集する必要があります。

このファイルを保存したら、VS Code が既に実行中の場合はリロードする必要があります。

?> また、`.vscode` フォルダ に `extensions.json` および `settings.json` ファイルがあるはずです。


次に、VSCode に統合ターミナルとして表示されるように、MSYS2 ウィンドウを設定します。これには多くの利点があります。ほとんどの場合で、エラー上で Ctrl + クリックするとこれらのファイルにジャンプできます。これによりデバッグがはるかに簡単になります。また、他のウィンドウへジャンプする必要が無いという点でも優れています。

1. <kbd><kbd>ファイル</kbd> > <kbd>ユーザー設定 ></kbd> > <kbd>設定</kbd> </kbd> をクリックします。
2. 右上の <kbd>{}</kbd> ボタンをクリックし、`settings.json` ファイルを開きます。
3. ファイルの内容を以下のように設定します:

   ```json
   {
        "terminal.integrated.shell.windows": "C:\\msys64\\usr\\bin\\bash.exe",
        "terminal.integrated.env.windows": {
            "MSYSTEM": "MINGW64",
            "CHERE_INVOKING": "1"
        },
        "terminal.integrated.shellArgs.windows": [
            "--login"
        ],
        "terminal.integrated.cursorStyle": "line"
    }
    ```

   ここに既に設定がある場合は、最初と最後の波括弧の間に全てを追加し、既存の設定を新しく追加された設定とカンマで区切ります。

?> MSYS2 を別のフォルダにインストールした場合は、`terminal.integrated.shell.windows` のパスをシステムの正しいパスに変更する必要があります。

4. Ctrl-<code>&#96;</code> (Grave) を押して、ターミナルを起動するか、<kbd><kbd>表示</kbd> > <kbd>ターミナル</kbd></kbd> (コマンド `workbench.action.terminal.toggleTerminal`)に進みます。まだターミナルが開いていない場合は、新しいターミナルが開きます。

   これにより、ワークスペースフォルダ(つまり `qmk_firmware` フォルダ)でターミナルが起動し、キーボードをコンパイルすることができます。


## 他の全てのオペレーティングシステム

1. [VS Code](https://code.visualstudio.com/) に進み、インストーラをダウンロードします
2. インストーラを実行します
3. 以上です

いいえ、本当に以上です。必要なパスはパッケージのインストール時に既に含まれています。現在のワークスペースのファイルを検出し、IntelliSense 用に解析する方がより良いです。

## プラグイン

インストールした方が良い拡張が幾つかあります。

* [Git Extension Pack](https://marketplace.visualstudio.com/items?itemName=donjayamanne.git-extension-pack) -
これは QMK ファームウェアで Git を簡単に使用できる Git 関連ツールを多数インスールします。
* [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig) - _[オプション]_ -  QMK コーディング規約にコードを準拠させるのに役立ちます。
* [Bracket Pair Colorizer 2](https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer-2) - _[オプション]_ - これはネストされたコードを参照しやすくするために、コード内の括弧を色分けします。
* [GitHub Markdown Preview](https://marketplace.visualstudio.com/items?itemName=bierner.github-markdown-preview) - _[オプション]_ - VS Code の markdown プレビューを GithHub のようにします。
* [VS Live Share Extension Pack](https://marketplace.visualstudio.com/items?itemName=MS-vsliveshare.vsliveshare-pack) - _[オプション]_ - この拡張により、他の誰かがあなたのワークスペースにアクセスし(あるいは、あなたが他の誰かのワークスペースにアクセスし)、手伝うことができます。あなたが問題を抱えており、他の誰かの助けが必要な場合に便利です。
* [VIM Keymap](https://marketplace.visualstudio.com/items?itemName=GiuseppeCesarano.vim-keymap) - _[オプション]_ - VIM スタイルのキーバインドを好む人向け。これには他のオプションもあります。
* [Travis CI Status](https://marketplace.visualstudio.com/items?itemName=felixrieseberg.vsc-travis-ci-status) - _[オプション]_ - セットアップした場合、現在の Travis CI の状態を表示します。

いずれかの拡張機能をインストールしたら、再起動します。

# QMK 用の VS Code の設定
1. <kbd><kbd>ファイル</kbd> > <kbd>フォルダーを開く</kbd></kbd> をクリックします
2. GitHub からクローンした QMK ファームウェアフォルダを開きます。
3. <kbd><kbd>ファイル</kbd> > <kbd>名前を付けてワークスペースを保存...</kbd></kbd> をクリックします

これで、VS Code で QMK ファームウェアをコーディングする準備ができました。
