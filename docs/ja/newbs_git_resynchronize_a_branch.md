# 同期の外れた git ブランチの再同期

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: adf4acf59:docs/newbs_git_resynchronize_a_branch.md
  git diff adf4acf59 HEAD docs/newbs_git_resynchronize_a_branch.md | cat
-->

仮にあなたの `master` ブランチにあなたのコミットを行い、そしてあなたの QMK リポジトリの更新が必要になったとします。
(フォーク元の) QMKの `master` ブランチを `git pull` することもできますが、but GitHub will tell you that your commit is a number of commits ahead of `qmk:master`、QMK にプルリクエストを行う場合、問題が発生する可能性があります。

?> このドキュメントは [あなたのフォークの master ブランチ: 更新は頻繁に、コミットはしないこと](ja/newbs_git_using_your_master_branch.md) で詳述されている概念に基づいています。その概念に慣れていない場合は、まずそれを読んでから、ここに戻ってください。

## あなた自身の `master` ブランチでの変更のバックアップ（オプション）

救えるものなら自分の行った変更を失いたくはないでしょう。
あなたの `master` ブランチに既に加えた変更を保存したい場合、最も簡単な方法は、単に「ダーティな」`master` ブランチの複製を作成することです：

```sh
git branch old_master master
```

これで、 `master` ブランチの複製である `old_master` という名前のブランチができました。

## あなたのブランチの再同期

さあ、`master` ブランチを再同期します。
この手順では、QMK のリポジトリを git のリモートリポジトリとして設定する必要があります。
設定済みのリモートリポジトリを確認するには、`git remote -v` を実行し、次のような結果が返されなければなりません。

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

もし、上記のようにならずに以下のように参照されるフォークが、1つだけ表示される場合：

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/qmk/qmk_firmware.git (fetch)
origin  https://github.com/qmk/qmk_firmware.git (push)
```

新しいリモートリポジトリを追加します：

```sh
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

次に、`origin` リモートリポジトリを、あなた自身のフォークにリダイレクトします：

```sh
git remote set-url origin https://github.com/<あなたのユーザ名>/qmk_firmware.git
```

Now that you have both remotes configured, you need to update the references for the upstream repository, which is QMK's, by running:  
両方のリモートリポジトリが設定されたので、次を実行して、QMK である `upstream` リポジトリの参照を更新する必要があります。(?? 'references' をこう訳して git の説明として正しいのか??)

```sh
git fetch upstream
```

この時点で、次を実行してあなたの(訳注：master)ブランチを QMK に再同期します。
(訳注： 今現在 `master` ブランチがチェックアウトされていなければなりません。
 そうなってなければ、`git checkout master` を先に実行しておく必要があります。)

```sh
git reset --hard upstream/master
```

これらの手順により、あなたのコンピュータ上のリポジトリが更新されますが、あなたの GitHub 上のフォークはまだ同期されていません。
GitHub 上のフォークを再同期するには、あなたのフォークにプッシュして、ローカルリポジトリに反映されていないリモート変更をオーバーライドするように Git に指示する必要があります。
これを行うには、次を実行します：

```sh
git push --force-with-lease
```

!> 他のユーザーがコミットを投稿するフォークで `git push --force-with-lease` を**実行しないでください**。これをすると、かれらのコミットが消去されてしまいます。

これで、あなたの GitHub フォーク、あなたのローカルファイル、および QMK のリポジトリはすべて同じになりました。
ここから、さらに必要な変更を加え（[変更を行なう](ja/newbs_git_using_your_master_branch.md#making-changes)）、通常どおりそれらを投稿できます。
