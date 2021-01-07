# まだ公開してはいけない！
- ~~`cool836Ami4` ---->  `cool836A`~~
- ~~get ready for pull request~~
- m.kiさんとゆかりさんから許可を得る
- ~~キーマップ`Ohasheen`のデフォルト配列をQWERTYに~~
- ~~デフォキーマップのがぞう添付~~
- ~~すべて動作確認~~


# cool836A

- このプロジェクトの詳細については設計者たる[m.ki様](https://twitter.com/0002ozlet)による[GitHubリポジトリ](https://github.com/telzo2000/cool836A)の記述をご覧ください。

- このファームウェアは2021年1月7日現在、cool836A ver.B+ (通称レッドバージョン)のみをサポートしています。ほかのバージョンに対応するコードを書いてくださる方あるいは書いてほしい方はお気軽に私[オオハシ](https://twitter.com/oha_oha_Ohashi)までご連絡ください。


## 申し訳程度のチュートリアル
詳細に書き込む労力は払えませんでしたが、最低限のコードのみ記します。

git clone のあと、

``` make cool836A/verB_RED:default ```

でコンパイル可能であることを確認し、

``` make cool836A/verB_RED:default:avrdude ```

によってデフォルトキーマップをPro Microに焼けるかもしれません。
`default`の代わりに`Ohasheen`を利用することもできます。

初心者の方はもっと素晴らしいウェブサイトでGitやqmk firmwareの使い方を覚えていただくのがよいかと思います。



-----------------
## English
- [Here](https://github.com/telzo2000/cool836A) are a full description of this project and build guide by the great Designer: [m.ki](imgur.com image replace me!)

- This repository currently(Jan 7, 2021) supports ver.B+ (RED version) only. Feel free to contact [ME](https://github.com/ketcha-k) for your build of other virsions' firmware.

- firmware maintainer: [Ohashi](https://github.com/ketcha-k)

## Such a humble tutorial
The author would like to provide a minimum guide.

After cloning the repository, you may want to 

``` make cool836A:verB_RED ```

to make sure it's compilable, and 

``` make cool836A:verB_RED:default ```

which leads you to the goal.

It is recommended that beginners learn how to get started with qmk firmware/configurator at other fantastic websites rather than here......

