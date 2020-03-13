## 你分叉的主分支: 一直在上传，但不要提交

十分推荐您在QMK开发过程中无论开发是否完成都要保持你的 `master` 分支更新，但是 ***一定不要*** 提交。相反，你应该在一个开发分叉中做出你所有修改并在开发时提交pull request。

减少合并冲突的可能性 &mdash; 两个或多个用户同时编辑文件的同一部分的实例 &mdash; 保持 `master` 分支最新，并创建一个新的分支来开始新的开发。

### 更新你的主分支

保持你的 `master` 更新, 推荐你添加QMK Firmware仓库作为Git的远程仓库，想这么做的话, 你可以打开你的Git命令行接口然后输入:

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

?> `upstream` 这个名字其实是随意的这么写是个惯例；你可以按照你的喜好给QMK远程仓库起名字。Git的 `remote` 命令使用 `git remote add <name> <url>`语法， `<name>` 是远程仓库的简称。这个名字可以被很多Git的命令使用，包括但不仅限于 `fetch`，`pull` 和 `push`，它是用来指定被操作的远程仓库的。

运行 `git remote -v`, 来确定这个仓库已经添加，以下是回显:

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

现在添加已完成，你可以用`git fetch upstream`来检查仓库的更新. 这会检索branches 和 tags &mdash; 统称为"refs" &mdash; 从QMK仓库, 也就是 `upstream`。我们可以比较我们的分叉和QMK的 `origin` 数据的不同。

要更新你的分叉的主分支，请运行以下命令，在每行之后按Enter键:

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

这回切换到你的`master` 分支, 检索你QMK仓库的refs, 下载当前QMK `master` 分支到你的电脑, 并上传到你的分叉.

## 做改动

你可以输入以下命令来创建一个新的分支来做改动:

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

这回建立一个叫做 `dev_branch`的新分支, 检查一下, 然后想你的分叉保存分支. 使用 `--set-upstream` 参数来告诉git使用你的分叉并且当每次你对你的分支用`git push` 或 `git pull`时要使用`dev_branch`。 它仅需要在第一次push的时候使用；然后你就可以很安全的用 `git push` 或 `git pull`, 并不需要其他参数了。

!> 使用 `git push`, 你可以用 `-u` 来代替 `--set-upstream` &mdash; `-u`是`--set-upstream`的简写。

您可以将您的分支命名为您想要的任何名称，但建议将其命名为与您要进行的更改相关的内容。

默认情况下 `git checkout -b` 在已经检出的分支上建立新的分支。您可以将新的分支建立在未检出的现有分支的基础上，方法是将现有分支的名称添加到命令：

```
git checkout -b dev_branch master
```

现在您已经有了一个开发分支，那么就打开您的文本编辑器并进行您需要做的任何更改。建议对您的分支进行许多小的提交；这样，任何引起问题的更改都可以在需要时更容易地跟踪和撤消。要进行更改，编辑并保存任何需要更新的文件，请将它们添加到Git的 *暂存区* ，然后将它们提交到您的分支：

```
git add path/to/updated_file
git commit -m "My commit message."
```

` git add`添加已更改到Git的*暂存区*也就是Git的“加载区域”的文件。其中包含使用 `git commit` 命令 *提交* 的并已经保存到仓库的更改。建议您使用描述性的提交消息，这样您就可以一目了然地知道更改了什么。

!> 如果你修改了很多文件，使用`git add -- path/to/file1 path/to/file2 ...`来添加所有你想添加的文件。

## 发布更改

最后一步是将更改推送到您的分叉。 输入 `git push`来推送. 现在Git将`dev_branch`的当前状态发布到您的分叉。

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/3152bf572b702109b9b01757ffe900d7f4387faf/docs/newbs_git_using_your_master_branch.md 
    源提交哈希：3152bf572b702109b9b01757ffe900d7f4387faf-->
<!--翻译时间:20200225-17:55(GMT+8)-->
