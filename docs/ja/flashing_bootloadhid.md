# BootloadHID の書き込み手順とブートローダの情報

<!---
  original document: 0.9.32:docs/flashing_bootloadhid.md
  git diff 0.9.32 HEAD -- docs/flashing_bootloadhid.md | cat
-->

ps2avr(GB) キーボードは ATmega32A マイクロコントローラを使い、異なるブートローダを使います。それは通常の QMK の方法を使って書き込むことができません。

一般的な書き込みシーケンス:

1. 以下のいずれかの方法を使ってブートローダに入ります:
   * `RESET` キーコードをタップします (全てのデバイスでは動作しないかもしれません)
   * ソルトキーを押し続けながらキーボードを接続します (通常はキーボードの readme に書かれています)
2. OS がデバイスを検知するのを待ちます。
3. .hex ファイルを書き込みます
4. デバイスをアプリケーションモードにリセットします(自動的に実行されるかもしれません)

## bootloadHID の書き込みターゲット

?> [こちら](ja/newbs_getting_started.md)で詳しく説明されている QMK インストールスクリプトを使うと、必要な bootloadHID ツールが自動的にインストールされます。

コマンドライン経由で書き込むには、以下のコマンドを実行してターゲット `:bootloadHID` を使います:

    make <keyboard>:<keymap>:bootloadHID

## GUI 書き込み

### Windows
1. [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash) をダウンロードします。
2. キーボードをリセットします。
3. 設定された VendorID が `16c0` で、ProductID が `05df` であることを確認します
4. `Find Device` ボタンを押し、キーボードが見つかることを確認します。
5. `Open .hex File` ボタンを押し、作成した `.hex` ファイルを見つけます。
6. `Flash Device` ボタンを押し、処理が完了するまで待ちます。

## コマンドライン書き込み

1. キーボードをリセットします。
2. `bootloadHID -r` に続けて `.hex` ファイルへのパスを入力し、キーボードに書き込みます。

### Windows 手動インストール
MSYS2の場合:
1. https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz から BootloadHID ファームウェアパッケージをダウンロードします。
2. 互換性のあるツール、例えば 7-Zip を使って内容を抽出します。
3. 解凍された書庫から MSYS2 インストール先、通常 `C:\msys64\usr\bin` に `commandline/bootloadHID.exe` をコピーして、MSYS パスに追加します。

ネイティブの Windows 書き込みの場合、MSYS2 環境の外部で `bootloadHID.exe` を使うことができます。

### Linux 手動インストール
1. libusb development の依存関係をインストールします:
   ```bash
   # これは OS に依存します - Debian については以下で動作します
sudo apt-get install libusb-dev
   ```
2. BootloadHID ファームウェアパッケージをダウンロードします:
   ```
   wget https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz -O - | tar -xz -C /tmp
   ```
3. bootloadHID 実行可能ファイルをビルドします:
   ```
   cd /tmp/bootloadHID.2012-12-08/commandline/
make
sudo cp bootloadHID /usr/local/bin
   ```

### MacOS 手動インストール
1. 以下を入力して Homebrew をインストールします:
   ```
   /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
   ```
2. 以下のパッケージをインストールします:
   ```
   brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
   ```
