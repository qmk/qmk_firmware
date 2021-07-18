# Docker クイックスタート

<!---
  original document: 0.9.32:docs/getting_started_docker.md
  git diff 0.9.32 HEAD -- docs/getting_started_docker.md | cat
-->

このプロジェクトは、プライマリオペレーティングシステムに大きな変更を加えることなくキーボードの新しいファームウェアを非常に簡単に構築することができる Docker ワークフローを含みます。これは、あなたがプロジェクトをクローンしビルドを実行した時に、他の人とまったく同じ環境と QMK ビルド基盤を持つことも保証します。これにより、人々はあなたが遭遇した問題の解決をより簡単に行えるようになります。

## 必要事項

主な前提条件は動作する `docker` がインストールされていることです。
* [Docker CE](https://docs.docker.com/install/#supported-platforms)

## 使い方

(サブモジュールを含む) QMK のレポジトリのローカルコピーを取得する:

```bash
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

キーマップをビルドするために以下のコマンドを実行します:
```bash
util/docker_build.sh <keyboard>:<keymap>
# 例えば: util/docker_build.sh planck/rev6:default
```

これは目的のキーボード/キーマップをコンパイルし、結果として書き込み用に `.hex` あるいは `.bin` ファイルを QMK ディレクトリの中に残します。`:keymap` が省略された場合は全てのキーマップが使われます。パラメータの形式は、`make` を使ってビルドする時と同じであることに注意してください。

`target` を指定して Docker から直接キーボードをビルドし、_かつ_書き込むためのサポートもあります。

```bash
util/docker_build.sh keyboard:keymap:target
# 例えば: util/docker_build.sh planck/rev6:default:flash
```

スクリプトをパラメータ無しで開始することもできます。この場合、1つずつビルドパラメータを入力するように求められます。これが使いやすいと思うかもしれません:

```bash
util/docker_build.sh
# パラメータを入力として読み込みます (空白にすると全てのキーボード/キーマップ)
```

## FAQ

### なぜ Windows/macOS 上で書き込めないのですか？

Windows と macOS では、実行するために [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/) が必要です。これはセットアップが面倒なので、お勧めではありません: 代わりに [QMK Toolbox](https://github.com/qmk/qmk_toolbox) を使ってください。

!> Docker for Windows は[Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v) を有効にする必要があります。これは、Windows 7、Windows 8 および **Windows 10 Home** のような Hyper-V を搭載していない Windows のバージョンでは機能しないことを意味します。
