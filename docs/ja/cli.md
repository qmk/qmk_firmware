# QMK CLI :id=qmk-cli

<!---
  original document: 0.8.58:docs/cli.md
  git diff 0.8.58 HEAD -- docs/cli.md | cat
-->

## 概要 :id=overview

QMK CLI を使用すると QMK キーボードの構築と作業が簡単になります。QMK ファームウェアの取得とコンパイル、キーマップの作成などのようなタスクを簡素化し合理化するためのコマンドを多く提供します。

### 必要事項 :id=requirements

CLI は Python 3.5 以上を必要とします。我々は必要事項の数を少なくしようとしていますが、[`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt) に列挙されているパッケージもインストールする必要があります。これらは QMK CLI をインストールするときに自動的にインストールされます。

### Homebrew を使ったインストール (macOS、いくつかの Linux) :id=install-using-homebrew

[Homebrew](https://brew.sh) をインストールしている場合は、タップして QMK をインストールすることができます:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # オプション、`qmk_firmware` の場所を設定します
qmk setup  # これは `qmk/qmk_firmware` をクローンし、オプションでビルド環境をセットアップします
```

### easy_install あるいは pip を使ってインストール :id=install-using-easy_install-or-pip

上のリストにあなたのシステムがない場合は、QMK を手動でインストールすることができます。最初に、python 3.5 (以降)をインストールしていて、pip をインストールしていることを確認してください。次に以下のコマンドを使って QMK をインストールします:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # オプション、`qmk_firmware` の場所を設定します
qmk setup  # これは `qmk/qmk_firmware` をクローンし、オプションでビルド環境をセットアップします
```

### 他のオペレーティングシステムのためのパッケージ :id=packaging-for-other-operating-systems

より多くのオペレーティングシステム用に `qmk` パッケージを作成および保守する人を探しています。OS 用のパッケージを作成する場合は、以下のガイドラインに従ってください:

* これらのガイドラインと矛盾する場合は、OS のベストプラクティスに従ってください
   * 逸脱する場合は、理由をコメントに文章化してください。
* virtualenv を使ってインストールしてください
* 環境変数 `QMK_HOME` を設定して、ファームウェアソースを `~/qmk_firmware` 以外のどこかにチェックアウトするようにユーザに指示してください。
