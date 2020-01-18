# あなたのフォークの master ブランチ: 更新は頻繁に、コミットはしないこと

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: adf4acf59:docs/newbs_git_using_your_master_branch.md
  git diff adf4acf59 HEAD -- docs/newbs_git_using_your_master_branch.md | cat
-->

QMK の開発では、何がどこで行われているかにかかわらず、`master` ブランチを最新の状態に保つことを強くお勧めします、しかし `master` ブランチには***絶対に直接コミットしないでください***。
代わりに、あなたのすべての変更は開発ブランチで行い、あなたが開発する時にはそのブランチからプルリクエストを発行します。

マージの競合 &mdash; これは 2人以上のユーザーがファイルの同じ部分をそれぞれ異なる編集をして統合できなくなった状態 &mdash; の可能性を減らすため `master` ブランチをなるべく最新の状態に保ち、新しいブランチを作成して新しい開発を開始します。

## あなたの master ブランチを更新する

`master` ブランチを最新の状態に保つには、git のリモートリポジトリとして QMK ファームウェアのリポジトリ(以降、QMK リポジトリ)を追加することをお勧めします。
これを行うには、Git コマンドラインインターフェイスを開き、次のように入力します。

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

?> `upstream`(訳注: `upstream` は`上流`という意味です)という名前は任意ですが、一般的な慣習です。
QMK のリモートリポジトリには、あなたにとって分かりやすい名前を付けることができます。
Git の `remote` コマンドは、構文 `git remote add <name> <url>` を使用します。
`<name>` はリモートリポジトリの省略形としてあなたが指定するものです。
この名前は、`fetch`、`pull`、`push` やそれ以外の多くの Git コマンドで、対象のリモートリポジトリを指定するために使用されます。

リポジトリが追加されたことを確認するには、`git remote -v` を実行します。
次のように表示されます。

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

これが完了すると、`git fetch upstream` を実行してリポジトリの更新を確認できます。
このコマンドは `upstream` というニックネームを持つ QMK リポジトリから、ブランチとタグ &mdash; "refs" と総称されます &mdash; を取得します。
これで、あなたのフォーク `origin` のデータを QMK が保持するデータと比較できます。

あなたのフォークの `master` を更新するには、次を実行します、各行の後にEnterキーを押してください:

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

これにより、あなたの `master` ブランチに切り替わり、QMK リポジトリから 'refs' を取得し、現在の QMK の `master` ブランチをコンピュータにダウンロードしてから、あなたのフォークにアップロードします。

## 変更を行なう :id=making-changes

変更するには、以下を入力して新しいブランチを作成します:

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

これにより、`dev_branch` という名前の新しいブランチが作成され、チェックアウトされ、新しいブランチがあなたのフォークに保存されます。
`--set-upstream` 引数は、このブランチから `git push` または `git pull` を使用するたびに、あなたのフォークと `dev_branch` ブランチを使用するように git に指示します。
この引数は最初のプッシュでのみ使用する必要があります。
その後、残りの引数なしで `git push` または `git pull` を安全に使用できます。

?> `git push` では、`-set-upstream` の代わりに `-u` を使用できます、 `-u` は `--set-upstream` のエイリアスです。

ブランチにはほぼ任意の名前を付けることができますが、あなたが行なう変更を表す名前を付けることをお勧めします。

デフォルトでは、`git checkout -b`は、今チェックアウトされているブランチに基づいて新しいブランチを作成します。
コマンド末尾に既存のブランチの名前を追加指定することにより、チェックアウトされていない既存のブランチを基にして新しいブランチを作成できます:

```
git checkout -b dev_branch master
```

これで開発ブランチができたのでテキストエディタを開き必要な変更を加えます。
ブランチに対して多くの小さなコミットを行うことをお勧めします。
そうすることで、問題を引き起こす変更をより簡単に特定し必要に応じて元に戻すことができます。
変更を加えるには、更新が必要なファイルを編集して保存し、Git の *ステージングエリア* に追加してから、ブランチにコミットします:

```
git add path/to/updated_file
git commit -m "My commit message."
```

`git add`は、変更されたファイルを Git の *ステージングエリア* に追加します。
これは、Git の「ロードゾーン」です。
これには、`git commit` によって *コミット* される変更が含まれており、リポジトリへの変更が保存されます。
変更内容が一目でわかるように、説明的なコミットメッセージを使用します。

?> 複数のファイルを変更した場合、`git add -- path/to/file1 path/to/file2 ...` を実行すれば、あなたの望むファイルを追加できます。

## 変更を公開する

最後のステップは、変更をフォークにプッシュすることです。
これを行うには、`git push`と入力します。
Gitは、 `dev_branch`の現在の状態をフォークに公開します。
