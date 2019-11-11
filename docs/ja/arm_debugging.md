# Eclipseを使ったARMデバッグ

このページでは、SWD アダプタとオープンソース/フリー ツールを使って ARM MCU のデバッグをセットアップする方法について説明します。このガイドでは、GNU MCU Eclipse IDE for C/C++ Developers および OpenOCD を必要な依存関係と一緒にインストールします。

このガイドは上級者向けであり、MAKE フローを使ってマシンで ARM 互換キーボードをコンパイルできることを前提にしています。

## ソフトウェアのインストール

ここでの主な目的は MCU Eclipse IDE を正しくマシンにインストールすることです。必要な手順は[この](https://gnu-mcu-eclipse.github.io/install/)インストール ガイドから派生しています。

### xPack マネージャ

このツールはソフトウェア パッケージ マネージャであり、必要な依存関係を取得するために使われます。

XPM はNode.jsを使って実行されるため、[ここ](https://nodejs.org/en/)から取得してください。インストールの後で、ターミナルを開き `npm -v` を入力します。バージョン番号の応答は、インストールが成功したことを意味します。

XPMのインストール手順は[ここ](https://www.npmjs.com/package/xpm)で見つけることができ、OS固有のものです。ターミナルへの `xpm --version` の入力で、ソフトウェアのバージョンが返るべきです。

### ARM ツールチェーン

XPMを使うと、ARM ツールチェーンを簡単にインストールできます。コマンドを入力します `xpm install --global @gnu-mcu-eclipse/arm-none-eabi-gcc`。

### Windows ビルド ツール

Windows を使っている場合は、これをインストールする必要があります！

`xpm install --global @gnu-mcu-eclipse/windows-build-tools`

### プログラマ/デバッガ ドライバ

プログラマのドライバをインスト―ルします。このチュートリアルはほとんどどこからでも入手することができる ST-Link v2 を使って作成されました。
ST-Link を持っている場合は、ドライバは[ここ](https://www.st.com/en/development-tools/stsw-link009.html)で見つけることができます。そうでない場合はツールの製造元にお問い合わせください。

### OpenOCD

この依存により、SWD は GDB からアクセスでき、デバッグに不可欠です。`xpm install --global @gnu-mcu-eclipse/openocd` を実行します。

### Java

Java は Eclipse で必要とされるため、[ここ](https://www.oracle.com/technetwork/java/javase/downloads/index.html)からダウンロードしてください。

### GNU MCU Eclipse IDE

最後に IDE をインストールする番です。最新のバージョンを取得するために[ここ](https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases/)のリリースページを使います。

## Eclipseの設定

ダウンロードした Eclipse IDE を開きます。QMKディレクトリをインポートするために、File -> Import -> C/C++ -> Existing code as Makefile Project を開きます。next を選択し、QMKフォルダを選択するために Browse を使います。tool-chain リストの中で ARM Cross GCC を選択し、Finish を選択します。

これで、左側に QMK フォルダが表示されます。右クリックして、プロパティを選択します。左側で MCUを開き、ARM Toolchain パスを選択します。xPack と OK を押します。Repeat for OpenOCD Path  and if you are on windows for Build Tool Path. Apply と Close を選択します。

ここで、必要な MCU パッケージをインストールします。Window -> Open Perspective -> Others -> Packs を選択して、Packs perspective に行きます。Packs タブの横にある黄色のリフレッシュ記号を選択します。様々な場所からMCUの定義を要求しているため、時間が掛かります。リンクが失敗した場合、おそらく Ignore を選択することができます。

これが終了すると、ビルド/デバッグするMCUを見つけることができるはずです。この例では、STM32F3 シリーズの MCU を使います。左側で、STMicroelectonics -> STM32F3 Series を選択します。中央のウィンドウに、packが表示されます。右クリックし、Install を選択します。それが終了したら、デフォルトのパースペクティブに戻ることができます。Window -> Open Perspective -> Others -> C/C++。

Eclipse に QMK をビルドする予定のデバイスを知らせる必要があります。QMK folder を右クリック -> Properties -> C/C++ Build -> Settings。デバイス タブを選択し、デバイスの下で MCU の適切な variant を選択します。私の例では、STM32F303CC です

ここにいる間に、buildコマンドもセットアップしましょう。C/C++ Build を選択し、Behavior タブを選択します。build コマンドで、`all` を必要な make コマンドに置き換えます。例えば、デフォルトのキーマップの rev6 Planck の場合、これは `planck/rev6:default` です。Apply と Close を選択します。

## ビルド

全てを正しくセットアップした場合、ハンマーボタンを押すとファームウェアがビルドされ、.binファイルが出力されるはずです。

## デバッグ

### デバッガの接続

ARM MCU は、クロック (SWCLK) 信号とデータ (SWDIO) 信号で構成される Single Wire Debug (SWD) プロトコルを使います。MCUを完全に操作するには、この2本のワイヤとグラウンドを接続するだけで十分です。ここでは、キーボードはUSBを介して電力が供給されると想定しています。リセットボタンを使って手動でアサートできるため、RESET 信号は必要ありません。より高度なセットアップのためにprintfとscanfをホストに非同期にパイプする SWO 信号を使用できますが、私たちのセットアップでは無視します。

注意: SWCLK と SWDIO ピンがキーボードのマトリックスで使われていないことを確認してください。もし使われている場合は、一時的に他のピンに切り替えることができます。

### デバッガの設定

QMKフォルダ上で右クリックし、Debug As -> Debug Configuration を選択します。ここで、GDB OpenOCD Debugging をダブルクリックします。デバッガ タブを選択し、MCUに必要な設定を入力します。見つけるには手間取ったりググったりする必要があるかもしれません。STM32F3 のためのデフォルトのスクリプトは stm32f3discovery.cfg と呼ばれます。OpenOCD に伝えるには、Config オプションの中で `-f board/stm32f3discovery.cfg` を入力します。

注意: 私の場合、この設定スクリプトは reset assertion を無効にするために編集が必要です。スクリプトの場所は、通常はパス `openocd/version/.content/scripts/board` の下の実際の実行可能フィールドの中で見つかります。ここで、私は `reset_config srst_only` を `reset_config none` に編集しました。

Apply と Close を選択します。

### デバッガを実行。

あなたのキーボードをリセットしてください。

虫アイコンをクリックし、もし全てがうまく行けばデバッグ パースペクティブの中にいることが分かります。ここでは、main  関数の最初でプログラム カウンタが停止し、再生ボタンを押します。全てのデバッガのほとんどの機能は ARM MCUで動作しますが、正確な詳細については google があなたのお友達です！


ハッピー デバッギング！
