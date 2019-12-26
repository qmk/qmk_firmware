# Vagrant クイックスタート

<!---
  original document: 7494490d6:docs/getting_started_vagrant.md
  git diff 7494490d6 HEAD docs/getting_started_vagrant.md | cat
-->

このプロジェクトは、プライマリオペレーティングシステムに大きな変更を加えることなくキーボードの新しいファームウェアを非常に簡単に構築することができる `Vagrantfile` を含みます。これは、あなたがプロジェクトをクローンしビルドを実行した時に、ビルドのために Vagrantfile を使っている他のユーザと全く同じ環境を持つことも保証します。人々が、発生した問題のトラブルシュートを簡単に行えるようにします

## 必要事項

このリポジトリ内の `Vagrantfile` を使うには、[Vagrant](http://www.vagrantup.com/) およびサポートされるプロバイダがインストールされている必要があります:

* [VirtualBox](https://www.virtualbox.org/) (バージョン 5.0.12 以降)
   * 'Vagrant を使うために最もアクセスしやすいプラットフォーム' として販売
* [VMware Workstation](https://www.vmware.com/products/workstation) および [Vagrant VMware plugin](http://www.vagrantup.com/vmware)
   * (有料) VMware プラグインには VMware Workstation/Fusion のライセンスコピーが必要です。
* [Docker](https://www.docker.com/)

Vagrant 以外に、適切なプロバイダがインストールされ、その後におそらくコンピュータを再起動すると、このプロジェクトをチェックアウトしたフォルダの中の任意の場所で 'vagrant up' を単純に実行することができ、このプロジェクトをビルドするのに必要な全てのツールが含まれる環境(仮想マシンあるいはコンテナ)が開始されます。すぐに理解できる Vagrant のスタートアップヒントの投稿があります。それ以外に、以下のビルドドキュメントを参照することもできます。

## ファームウェアの書き込み

ファームウェアを書き込む"簡単"な方法は、ホスト OS からツールを使うことです:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (推奨)
* [Teensy ローダー](https://www.pjrc.com/teensy/loader.html)
* [Atmel FLIP](http://www.atmel.com/tools/flip.aspx)

コマンドラインでプログラムしたい場合は、Vagrant の ['modifyvm'] 行のコメントを解除して Linux への USB パススルーを有効にし、dfu-util/dfu-programmer のようなコマンドラインツールを使ってプログラムすることができます。あるいは Teensy CLI バージョンをインストールすることができます。

## Vagrantfile の概要
開発環境は QMK Docker イメージ、`qmkfm/base_container` を実行するように設定されています。これはシステム間の予測可能性が保証されるだけでなく、CI 環境もミラーされます。

## FAQ

### Virtualbox で問題が表示されるのはなぜですか？
Virtualbox 5 の特定のバージョンはこの Vagrantfile のボックスにインストールされている Virtualbox extension と互換性が無いようです。/vagrant のマウントで問題が発生した場合は、Virtualbox のバージョンを少なくとも 5.0.12 にアップグレードしてください。**または、以下のコマンドを実行してみることができます:**

```console
vagrant plugin install vagrant-vbguest
```

### 既存の環境を削除するにはどうすればいいですか？
あなたの環境での作業が完了しましたか？このプロジェクトをチェックアウトしたフォルダの中のどこからでも、以下を実行してください:

```console
vagrant destroy
```

### Docker を直接使いたい場合はどうしますか？
仮想マシン無しで Vagrant のワークフローを活用したいですか？Vagrantfile は仮想マシンの実行をバイパスし、コンテナを直接実行するように設定されています。Docker を強制的に使うように環境を立ち上げる場合は、以下を実行してください:
```console
vagrant up --provider=docker
```

### Docker コンテナではなく仮想マシンにアクセスするにはどうすればいいですか？
以下を実行して、`vagrant` のユーザ起動を直接 QMK builder イメージへバイパスするようにします:

```console
vagrant ssh -c 'sudo -i'
```
