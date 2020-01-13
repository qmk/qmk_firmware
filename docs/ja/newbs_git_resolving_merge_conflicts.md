#  マージの競合の解決

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: adf4acf59:docs/newbs_git_resolving_merge_conflicts.md
  git diff adf4acf59 HEAD -- docs/newbs_git_resolving_merge_conflicts.md | cat
-->

ブランチでの作業の完了に時間がかかる場合、他の人が行った変更が、プルリクエストを開いたときにブランチに加えた変更と競合することがあります。
これは *マージの競合* と呼ばれ、複数の人が同じファイルの同じ部分を編集すると発生します。

?> このドキュメントは [あなたのフォークの master ブランチ: 更新は頻繁に、コミットはしないこと](ja/newbs_git_using_your_master_branch.md) で詳述されている概念に基づいています。
その概念に慣れていない場合は、まずそれを読んでから、ここに戻ってください。

## 変更のリベース

*リベース* は、コミット履歴のある時点で適用された変更を取得し、それらを元に戻し、次に同じ変更を別のポイントに適用する Git の方法です。
マージの競合が発生した場合、ブランチをリベースして、ブランチを作成してから現在までに行われた変更を取得できます。

開始するには、次を実行します:

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

ここに入力された `git rev-list` コマンドは、現在のブランチと QMK の master ブランチで異なるコミットの数を返します。
最初に `git fetch` を実行して、upstream リポジトリの現在の状態を表す refs があることを確認します。
入力された `git rev-list` コマンドの出力は2つの数値を返します:

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

最初の数字は、現在のブランチが作成されてからのコミット数を表し、2番目の数字は、現在のブランチが作成されてから `upstream/master` に対して行われたコミットの数であり、したがって、現在のブランチに記録されていない変更です。

現在のブランチと upstream リポジトリの両方の現在の状態がわかったので、リベース操作を開始できます:

```
git rebase upstream/master
```

これにより、Git は現在のブランチのコミットを取り消してから、QMK の master ブランチに対してコミットを再適用します。

```
$ git rebase upstream/master
First, rewinding head to replay your work on top of it...
Applying: Commit #1
Using index info to reconstruct a base tree...
M       conflicting_file_1.txt
Falling back to patching base and 3-way merge...
Auto-merging conflicting_file_1.txt
CONFLICT (content): Merge conflict in conflicting_file_1.txt
error: Failed to merge in the changes.
hint: Use 'git am --show-current-patch' to see the failed patch
Patch failed at 0001 Commit #1

Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
```

これにより、マージの競合があることがわかり、競合のあるファイルの名前が示されます。
テキストエディタで競合するファイルを開くと、ファイルのどこかに次のような行があります:

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

行 `<<<<<<< HEAD` はマージ競合の始まりを示し、行 `>>>>>>> commit #1` は終了を示し、競合するセクションは `=======` で区切られます。
`HEAD` 側の部分はファイルの QMK master バージョンからのものであり、コミットメッセージでマークされた部分は現在のブランチとコミットからのものです。

Git はファイルの内容ではなく *ファイルへの変更* を直接追跡するため、Git がコミットの前にファイル内にあったテキストを見つけられない場合、ファイルの編集方法がわかりません。
ファイルを再編集して、競合を解決します。
変更を加えてから、ファイルを保存します。

```
<p>Need help? Email support@webhost.us.</p>
```

そしてコマンド実行:

```
git add conflicting_file_1.txt
git rebase --continue
```

Git は、競合するファイルへの変更をログに記録し、ブランチのコミットが最後に達するまで適用し続けます。
