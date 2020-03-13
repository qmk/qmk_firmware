# 重新同步一个失去同步的Git分支

假设你提交到你的 `master` 分支，现在你要升级你的QMK仓库。你需要 `git pull` QMK的 `master` 分支到你自己的，但是Github会告诉你你的分支有很多来自 `qmk:master`的提交, 这会让你在向QMK打开一个PR的时候出问题。

?> 阅读本文档需首先了解[你分叉的主分支：总是更新,从不提交](zh-cn/newbs_git_using_your_master_branch.md)。如果你不熟悉该文档，请先阅读，然后继续阅读本文档。

## 在你的主分支备份修改(可选)

没人想丢掉有用的劳动成果。如果你想要保存你向你`master`分支做出的更改 ，最简单的方法就是为你已经"乱七八糟"的`master`分支创建副本:

```sh
git branch old_master master
```

现在你有一个叫做 `old_master`的分支，它是`master`分支的副本。

## 重新同步你的分支

现在就是同步你的`master`分支的时候了。 这一步你将要在Git中把QMK仓库配置为远程仓库。检查你配置好的远程仓库，运行`git remote -v`，将会返回类似以下内容：

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

如果你发现只有一个分叉被引用：

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/qmk/qmk_firmware.git (fetch)
origin  https://github.com/qmk/qmk_firmware.git (push)
```

使用以下命令添加远程仓库：

```sh
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

然后使用以下语句重定向 `origin` 远程仓库到你自己的分叉：

```sh
git remote set-url origin https://github.com/<your_username>/qmk_firmware.git
```

现在您已经配置了两个远程仓库，现在你需要为QMK的upstream仓库更新引用。运行以下语句：

```sh
git fetch upstream
```

此时，使用以下语句从QMK重新同步你的分支：

```sh
git reset --hard upstream/master
```

这些步骤会更新你电脑上的仓库，但是你GitHub上的分支还是失去同步的。若要同步你Github上的分叉，你需要push到你的Github上，并指引你的Git覆盖所有未体现在你本地仓库的远程更改。于是要运行以下代码：

```sh
git push --force-with-lease
```

!> **千万不要** 在其他的用户post提交的分叉上运行 `git push --force-with-lease` 。这将会消除他们的提交。

现在，你的Github，你的本地文件，和QMK的仓库就一模一样了。现在你可以进行进一步所需的修改，([要用分支！](zh-cn/newbs_git_using_your_master_branch.md#做修改)) 然后正常post即可。

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/26a823082b17ee30aa8a0c5e39a32d854449ce15/docs/newbs_git_resynchronize_a_branch.md 
    源提交哈希：26a823082b17ee30aa8a0c5e39a32d854449ce15-->
<!--翻译时间:20200224-17:20(GMT+8)-->
