# 重新同步已失去同步状态的Git分支

<!---
  original document: 0.15.17:docs/newbs_git_resynchronize_a_branch.md 
  git diff 0.15.17 HEAD -- docs/newbs_git_resynchronize_a_branch.md  | cat
-->

假设你在自己的 `master` 分支之上有提交，并且想和QMK仓库进行同步，可以通过 `git pull` 拉取QMK的 `master` 分支到你的库，但同时Github也会提醒你当前分支相比 `qmk:master` 有几个领先的提交，会在你向QMK发起pr时造成麻烦。

?> 本文中的场景基于[在你Fork的主干上：频繁更新，不要提交](zh-cn/newbs_git_using_your_master_branch.md)一文。如果你对那篇文章不熟悉，请先阅读它，再回来继续。

## 备份你在自己的主干分支上的所有变更（可选）

不会有人想把有用的成果弄丢的。如果你想将你的 `master` 分支上的变更另存一份，简便的方法是直接创建一个当前“脏” `master` 分支的副本：

```
git branch old_master master
```

现在 `master` 分支拥有了一个副本分支 `old_master`。

## 重新同步分支

现在可以重新同步 `master` 分支了，这里，我们将QMK仓库设置为Git的远程仓库。通过执行 `git remote -v` 可以确认远程仓库配置，输出信息应类似于：

```
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

如果你只能看到一个仓库：

```
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/qmk/qmk_firmware.git (fetch)
origin  https://github.com/qmk/qmk_firmware.git (push)
```

通过如下命令添加新的远程仓库：

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

然后，重新将 `origin` 远程仓库设置为自己的fork：

```
git remote set-url origin https://github.com/<your_username>/qmk_firmware.git
```

在两个远程仓库配置完毕后，需要从QMK的 upstream 仓库中获取到更新，执行：

```
git fetch upstream
```

此时，重新同步你的分支到QMK的版本：

```
git reset --hard upstream/master
```

以上操作会更新你的本地仓库，而你的Github远程仓库仍然处于未同步状态，通过推送，可以让其进入已同步状态。可以通过如下命令来指引Git强行覆盖掉那些仅在你远程仓库中存在的提交：

```
git push --force-with-lease
```

!> **不要**在其它使用者也会提交的分支上执行 `git push --force-with-lease`，否则会覆盖掉他人的提交。

此时你的Github fork，本地文件副本，以及QMK仓库就是一致的了。之后再进行变更（[在分支上！](zh-cn/newbs_git_using_your_master_branch.md#making-changes)）和提交。
