# cool836A

- このプロジェクトの詳細については設計者たる[m.ki様](https://twitter.com/0002ozlet)による[GitHubリポジトリ](https://github.com/telzo2000/cool836A)の記述をご覧ください。

### バージョン(A, B+, C+)について
- m.ki様によるとどのバージョンも回路は同じで、ファームウェアを分ける必要はないとのことです。
- しかしながらこのファームウェアは、cool836A ver.B+ (通称レッドバージョン)のみでテストされています(2021年1月7日現在)。そのため念のため、当面の間はサブフォルダの名前をcool836A/verB_REDとさせていただきます。
- ほかのバージョンに書き込んだときに不具合等がありましたら、方はお気軽に私[オオハシ](https://twitter.com/oha_oha_Ohashi)までご連絡ください。


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
- [Here](https://github.com/telzo2000/cool836A) are a full description of this project and build guide by the great Designer: m.ki

- Each virsions(A, B+, C+) of cool836A has the same circuit and that means you can install this firmware on any of them.
- However, this repository is currently(Jan 7, 2021) tested on ver.B+ (RED version) only. Feel free to contact [ME](https://github.com/ketcha-k) for any problems.

- firmware maintainer: [Ohashi](https://github.com/ketcha-k)

## Such a humble tutorial
The author would like to provide a minimum guide.

After cloning the repository, you may want to 

``` make cool836A/verB_RED ```

to make sure it's compilable, and 

``` make cool836A/verB_RED:default ```

which leads you to the goal.

It is recommended that beginners learn how to get started with qmk firmware/configurator at other fantastic websites rather than here......
