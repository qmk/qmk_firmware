<!-- # Best Practices -->
# QMK における Git 運用作法

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: e75919960:docs/newbs_best_practices.md
  git diff e75919960 HEAD docs/newbs_best_practices.md | cat
-->

<!-- ## Or, "How I Learned to Stop Worrying and Love Git." -->
## または、如何にして私は心配することをやめて Git を愛することを学んだか。

<!-- _Almost the same as #7231:25fdbf2a0:newbs_git_best_practices.md L5_ -->
<!-- This document aims to instruct novices in the best ways to have a smooth experience in contributing to QMK. We will walk through the process of contributing to QMK, detailing some ways to make this task easier, and then later we'll break some things in order to teach you how to fix them. -->
この文書は、QMK への貢献をスムーズに行なう最もよい方法を初心者に教えることを目的としています。
QMK に貢献するプロセスを順を追って説明し、この作業を簡単にするいくつかの方法を詳しく説明します。
その後、意図的に一部を壊してみせて、それらを修正する方法を教えます。

<!-- This document assumes a few things: -->
このドキュメントは以下のことを前提としています:

<!-- _Same as #7231:25fdbf2a0:newbs_git_best_practices.md L9_  -->
<!-- 1. You have a GitHub account, and have [forked the qmk_firmware repository](getting_started_github.md) to your account. -->
<!-- 2. You've [set up your build environment](newbs_getting_started.md?id=environment-setup). -->
<!-- #7231:da7d49246: 2. You've set up both [your build environment](newbs_getting_started.md?id=set-up-your-environment) and [QMK](newbs_getting_started.md?id=set-up-qmk). -->

1. あなたは GitHub アカウントがあり、アカウントに [qmk_firmware リポジトリをフォーク](ja/getting_started_github.md) している。
2. あなたは、[環境構築](ja/newbs_getting_started.md#set-up-your-environment) と [QMK の設定](ja/newbs_getting_started.md#set-up-qmk) を両方とも完了している。

<!-- ## Your fork's master: Update Often, Commit Never -->
## あなたのフォークの master ブランチ: 更新は頻繁に、コミットはしないこと

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L3_  -->
<!-- It is highly recommended for QMK development, regardless of what is being done or where, to keep your `master` branch updated, but ***never*** commit to it. Instead, do all your changes in a development branch and issue pull requests from your branches when you're developing. -->
QMK の開発では、何がどこで行われているかにかかわらず、`master` ブランチを最新の状態に保つことを強くお勧めします、しかし `master` ブランチには***絶対に直接コミットしないでください***。
代わりに、あなたのすべての変更は開発ブランチで行い、あなたが開発する時にはそのブランチからプルリクエストを発行します。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L5_  -->
<!-- To reduce the chances of merge conflicts &mdash; instances where two or more users have edited the same part of a file concurrently &mdash; keep your `master` branch relatively up-to-date, and start any new developments by creating a new branch. -->
マージの競合 &mdash; これは 2人以上のユーザーがファイルの同じ部分をそれぞれ異なる編集をして統合できなくなった状態 &mdash; の可能性を減らすため `master` ブランチをなるべく最新の状態に保ち、新しいブランチを作成して新しい開発を開始します。

<!-- ### Updating your master branch -->
### あなたの master ブランチを更新する

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L9_  -->
<!-- To keep your `master` branch updated, it is recommended to add the QMK Firmware repository ("repo") as a remote repository in git. To do this, open your Git command line interface and enter: -->
`master` ブランチを最新の状態に保つには、git のリモートリポジトリとして QMK ファームウェアのリポジトリ(以降、QMK リポジトリ)を追加することをお勧めします。
これを行うには、Git コマンドラインインターフェイスを開き、次のように入力します。

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L15_  -->
<!-- To verify that the repository has been added, run `git remote -v`, which should return the following: -->
リポジトリが追加されたことを確認するには、`git remote -v` を実行します。
次のように表示されます。(訳注: `upstream` は`上流`という意味です。)

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L25_  -->
<!-- Now that this is done, you can check for updates to the repo by running `git fetch upstream`. This retrieves the branches and tags &mdash; collectively referred to as "refs" &mdash; from the QMK repo, which now has the nickname `upstream`. We can now compare the data on our fork `origin` to that held by QMK. -->
これが完了すると、`git fetch upstream` を実行してリポジトリの更新を確認できます。
このコマンドは `upstream` というニックネームを持つ QMK リポジトリから、ブランチとタグ &mdash; "refs" と総称されます &mdash; を取得します。
これで、あなたのフォーク `origin` のデータを QMK が保持するデータと比較できます。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L27_  -->
<!-- To update your fork's master, run the following, hitting the Enter key after each line: -->
あなたのフォークの `master` を更新するには、次を実行します、各行の後にEnterキーを押してください:

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L36_  -->
<!-- This switches you to your `master` branch, retrieves the refs from the QMK repo, downloads the current QMK `master` branch to your computer, and then uploads it to your fork. -->
これにより、あなたの `master` ブランチに切り替わり、QMK リポジトリから 'refs' を取得し、現在の QMK の `master` ブランチをコンピュータにダウンロードしてから、あなたのフォークにアップロードします。

<!-- ### Making Changes -->
### 変更を行なう

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L40_  -->
<!-- To make changes, create a new branch by entering: -->
変更するには、以下を入力して新しいブランチを作成します:

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L47_  -->
<!-- This creates a new branch named `dev_branch`, checks it out, and then saves the new branch to your fork. The `--set-upstream` argument tells git to use your fork and the `dev_branch` branch every time you use `git push` or `git pull` from this branch. It only needs to be used on the first push; after that, you can safely use `git push` or `git pull`, without the rest of the arguments. -->
これにより、`dev_branch` という名前の新しいブランチが作成され、チェックアウトされ、新しいブランチがあなたのフォークに保存されます。
`--set-upstream` 引数は、このブランチから `git push` または `git pull` を使用するたびに、あなたのフォークと `dev_branch` ブランチを使用するように git に指示します。
この引数は最初のプッシュでのみ使用する必要があります。
その後、残りの引数なしで `git push` または `git pull` を安全に使用できます。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L49_  -->
<!--  With `git push`, you can use `-u` in place of `--set-upstream` &mdash; `-u` is an alias for `--set-upstream`. -->
!> `git push` では、`-set-upstream` の代わりに `-u` を使用できます、 `-u` は `--set-upstream` のエイリアスです。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L51_  -->
<!-- You can name your branch nearly anything you want, though it is recommended to name it something related to the changes you are going to make. -->
ブランチにはほぼ任意の名前を付けることができますが、あなたが行なう変更を表す名前を付けることをお勧めします。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L53_  -->
<!-- By default `git checkout -b` will base your new branch on the branch that is checked out. You can base your new branch on an existing branch that is not checked out by adding the name of the existing branch to the command: -->
デフォルトでは、`git checkout -b`は、今チェックアウトされているブランチに基づいて新しいブランチを作成します。
コマンド末尾に既存のブランチの名前を追加指定することにより、チェックアウトされていない既存のブランチを基にして新しいブランチを作成できます:

```
git checkout -b dev_branch master
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L59_  -->
<!-- Now that you have a development branch, open your text editor and make whatever changes you need to make. It is recommended to make many small commits to your branch; that way, any change that causes issues can be more easily traced and undone if needed. To make your changes, edit and save any files that need to be updated, add them to Git's *staging area*, and then commit them to your branch: -->
これで開発ブランチができたのでテキストエディタを開き必要な変更を加えます。
ブランチに対して多くの小さなコミットを行うことをお勧めします。
そうすることで、問題を引き起こす変更をより簡単に特定し必要に応じて元に戻すことができます。
変更を加えるには、更新が必要なファイルを編集して保存し、Git の *ステージングエリア* に追加してから、ブランチにコミットします:

```
git add path/to/updated_file
git commit -m "My commit message."
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L66_  -->
<!-- `git add` adds files that have been changed to Git's *staging area*, which is Git's "loading zone." This contains the changes that are going to be *committed* by `git commit`, which saves the changes to the repo. Use descriptive commit messages so you can know what was changed at a glance. -->
`git add`は、変更されたファイルを Git の *ステージングエリア* に追加します。
これは、Git の「ロードゾーン」です。
これには、`git commit` によって *コミット* される変更が含まれており、リポジトリへの変更が保存されます。
変更内容が一目でわかるように、説明的なコミットメッセージを使用します。

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L68_  -->
<!-- !> If you've changed a lot of files, but all the files are part of the same change, you can use `git add .` to add all the changed files that are in your current directory, rather than having to add each file individually. -->
!> 多くのファイルを変更したが、すべてのファイルが同じ変更の一部である場合、各ファイルを個別に追加するのではなく、 `git add .` を使用して、現在のディレクトリにあるすべての変更されたファイルを追加できます。

<!-- ### Publishing Your Changes -->
### 変更を公開する

<!-- _Same as #7231:25fdbf2a0:newbs_git_using_your_master_branch.md L72_  -->
<!-- The last step is to push your changes to your fork. To do this, enter `git push`. Git now publishes the current state of `dev_branch` to your fork. -->
最後のステップは、変更をフォークにプッシュすることです。これを行うには、`git push`と入力します。
Git は `dev_branch` の現在の状態をフォークに公開します。

<!-- ## Resolving Merge Conflicts -->
##  マージの競合の解決

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L3_  -->
<!-- Sometimes when your work in a branch takes a long time to complete, changes that have been made by others conflict with changes you have made to your branch when you open a pull request. This is called a *merge conflict*, and is what happens when multiple people edit the same parts of the same files. -->
ブランチでの作業の完了に時間がかかる場合、他の人が行った変更が、プルリクエストを開いたときにブランチに加えた変更と競合することがあります。
これは *マージの競合* と呼ばれ、複数の人が同じファイルの同じ部分を編集すると発生します。

<!-- ### Rebasing Your Changes -->
### 変更のリベース

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L9_  -->
<!-- A *rebase* is Git's way of taking changes that were applied at one point, reversing them, and then applying the same changes to another point. In the case of a merge conflict, you can rebase your branch to grab the changes that were made between when you created your branch and the present time. -->
*リベース* は、ある時点で適用された変更を取得し、それらを元に戻し、次に同じ変更を別のポイントに適用する Git の方法です。
マージの競合が発生した場合、ブランチをリベースして、ブランチを作成してから現在までに行われた変更を取得できます。

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L11_  -->
<!-- To start, run the following: -->
開始するには、次を実行します:

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L18_  -->
<!-- The `git rev-list` command entered here returns the number of commits that differ between the current branch and QMK's master branch. We run `git fetch` first to make sure we have the refs that represent the current state of the upstream repo. The output of the `git rev-list` command entered returns two numbers: -->
ここに入力された `git rev-list` コマンドは、現在のブランチと QMK の master ブランチで異なるコミットの数を返します。
最初に `git fetch` を実行して、upstream リポジトリの現在の状態を表す refs があることを確認します。
入力された `git rev-list` コマンドの出力は2つの数値を返します:

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L25_  -->
<!-- The first number represents the number of commits on the current branch since it was created, and the second number is the number of commits made to `upstream/master` since the current branch was created, and thus, the changes that are not recorded in the current branch. -->
最初の数字は、現在のブランチが作成されてからのコミット数を表し、2番目の数字は、現在のブランチが作成されてから `upstream/master` に対して行われたコミットの数であり、したがって、現在のブランチに記録されていない変更です。

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L27_-->
<!-- Now that the current states of both the current branch and the upstream repo are known, we can start a rebase operation: -->
現在のブランチと upstream リポジトリの両方の現在の状態がわかったので、リベース操作を開始できます:

```
git rebase upstream/master
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L33_  -->
<!-- This tells Git to undo the commits on the current branch, and then reapply them against QMK's master branch. -->
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

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L54_  -->
<!-- This tells us that we have a merge conflict, and gives the name of the file with the conflict. Open the conflicting file in your text editor, and somewhere in the file, you'll find something like this: -->
これにより、マージの競合があることがわかり、競合のあるファイルの名前が示されます。
テキストエディタで競合するファイルを開くと、ファイルのどこかに次のような行があります:

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L64_  -->
<!-- The line `<<<<<<< HEAD` marks the beginning of a merge conflict, and the `>>>>>>> Commit #1` line marks the end, with the conflicting sections separated by `=======`. The part on the `HEAD` side is from the QMK master version of the file, and the part marked with the commit message is from the current branch and commit. -->
行 `<<<<<<< HEAD` はマージ競合の始まりを示し、行 `>>>>>>> commit #1` は終了を示し、競合するセクションは `=======` で区切られます。
`HEAD` 側の部分はファイルの QMK master バージョンからのものであり、コミットメッセージでマークされた部分は現在のブランチとコミットからのものです。

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L66_  -->
<!-- Because Git tracks *changes to files* rather than the contents of the files directly, if Git can't find the text that was in the file previous to the commit that was made, it won't know how to edit the file. Re-editing the file will solve the conflict. Make your changes, and then save the file. -->
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

<!-- _Same as #7231:25fdbf2a0:newbs_git_resolving_merge_conflicts.md L79_  -->
<!-- Git logs the changes to the conflicting file, and continues applying the commits from our branch until it reaches the end. -->
Git は、競合するファイルへの変更をログに記録し、ブランチのコミットが最後に達するまで適用し続けます。
