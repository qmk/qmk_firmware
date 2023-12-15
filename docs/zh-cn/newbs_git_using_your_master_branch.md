# 在你Fork的主干上：频繁更新，不要提交

<!---
  original document: 0.15.17:docs/newbs_git_using_your_master_branch.md 
  git diff 0.15.17 HEAD -- docs/newbs_git_using_your_master_branch.md  | cat
-->

我们强烈推荐所有QMK开发者，无论在哪里做什么改动，频繁更新你的 `master` 分支，但***不要***在其上提交。相对地，将你所有的改动提交到开发分支上并提交一个pull request。

为了减少冲突 &mdash; 多人同时编辑同一个文件 &mdash; 保持你的 `master` 分支更新到最新，并在新创建的分支上进行开发。

## 更新master分支

为了保持 `master` 更新到最新，推荐将QMK固件仓库（"repo"）设置为git远程仓库。打开Git命令行界面并键入：

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

?> 名称 `upstream` 部分可以任意，这里给的是常用的；你可以将QMK远程仓库名称改成你想要的。Git的 `remote` 命令语法为 `git remote add <name> <url>`, `<name>` 是远程仓库的简写名称，这个名称可以在很多Git命令中使用，包括但不限于 `fetch`，`pull` 及 `push`，以指定目标远程仓库。

要验证是否添加成功，可以执行 `git remote -v`，输出应该类似于：

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

在以上操作完成后，可以通过执行 `git fetch upstream` 来检查仓库是否有更新。该命令从QMK仓库拉取的分支（branches）及标签（tags） &mdash; 统称为“refs（引用）” &mdash;现在也被称作 `upstream`（上游）。此时我们可以比对自己fork版本的 `origin` 与QMK维护的分支的差异了。

要更新你的fork的master分支，执行以下指令，每一行结束都需要按回车：

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

以上操作会切换到 `master` 分支，从QMK仓库拉取refs，下载QMK `master` 分支的当前版本，并上传至你的fork中。

## 进行编辑 :id=making-changes

要进行编辑，通过如下命令创建一个新分支：

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

以上操作会创建 `dev_branch` 新分支，检出（check out）并保存到你的fork中。`--set-upstream` 参数用于告知git使用你的fork仓库来处理 `dev_branch` 分支下的 `git push` 及 `git pull` 命令，且仅需要在第一次执行push命令时指定，之后再次执行 `git push` 或是 `git pull` 都无需加入该参数了。

?> 在 `git push` 时，可以使用 `-u` 替代 `--set-upstram` &mdash; `-u` 为 `--set-upsream` 参数的别名。

你可以任意命名该分支，但仍建议对分支起一个可以描述将在该分支下要做的工作的名称。

默认情况下 `git checkout -b` 会基于你当前检出的分支作为新分支的基准。可以在后面追加已存在但未检出的分支名来指定新分支的基准：

```
git checkout -b dev_branch master
```

此时你便有了一个开发用分支，可以打开编辑器并进行你期望的变更了。通常推荐提交大量的小规模提交（commit），这样在需要时会更容易地定位并回滚造成问题的提交。若要提交更改，编辑并保存要更新的文件，并将其添加到*暂存区（staged area）*，然后提交到分支中：

```
git add path/to/updated_file
git commit -m "My commit message."
```

`git add` 会将更改后的文件放到Git的*暂存区*，也称作Git的“装载区”。这里留存着即将通过 `git commit` 所提交并保存到仓库中的变更。请使用确切的描述来填写提交日志，以便于快速了解改动内容。

?> 如果更改了多个文件，可以通过 `git add -- path/to/file1 path/to/file2 ...` 来添加所有项目。

## 发布变更

最后一步为上传你的变更到你的fork中。通过执行 `git push`，Git将发布 `dev_branch` 分支的所有变更至你的fork中。
