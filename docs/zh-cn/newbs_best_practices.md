# 最佳实践

## 或者说, "我应如何学会不再担心并开始爱上Git。"

本文档旨在指导新手以最佳方式获得为QMK做出贡献的丝滑体验。我们将介绍为QMK做出贡献的过程，详细介绍使这项任务更容易的一些方法，然后我们将制造一些问题，来教你如何解决它们。

本文假设了一些内容:

1. 一有个GitHub账户, 并[创建qmk_firmware仓库分叉](getting_started_github.md)到你的帐户.
2. 你已经[建立你的构建环境](newbs_getting_started.md?id=environment-setup).


## 你分叉的主分支: 一直在上传，但不要提交

十分推荐您在QMK开发过程中无论开发是否完成都要保持你的 `master` 分支更新，但是 ***一定不要*** 提交。相反，你应该在一个开发分叉中做出你所有修改并在开发时提交pull request。

减少合并冲突的可能性 &mdash; 两个或多个用户同时编辑文件的同一部分的实例 &mdash; 保持 `master` 分支最新，并创建一个新的分支来开始新的开发。

### 更新你的主分支

保持你的 `master` 更新, 推荐你添加QMK Firmware仓库作为Git的远程仓库，想这么做的话, 你可以打开你的Git命令行接口然后输入:

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

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

### 做改动

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

现在您已经有了一个开发分支，那么就打开您的文本编辑器并进行您需要做的任何更改。建议对您的分支进行许多小的提交；这样，任何引起问题的更改都可以在需要时更容易地跟踪和撤消。要进行更改，编辑并保存任何需要更新的文件，请将它们添加到Git的 *staging area* ，然后将它们提交到您的分支：

```
git add path/to/updated_file
git commit -m "My commit message."
```

` git add`添加已更改到Git的*临时区域*也就是Git的“加载区域”的文件。其中包含使用 `git commit` 命令 *提交* 的并已经保存到仓库的更改。建议您使用描述性的提交消息，这样您就可以一目了然地知道更改了什么。

!> 如果你修改了很多文件，但所有的文件都是同一个更改的一部分，你可以用 `git add .` 来添加当前目录中所有已更改的文件而不是单独添加每个文件.

### 发布更改

最后一步是将更改推送到您的分叉。 输入 `git push`来推送. 现在Git将`dev_branch`的当前状态发布到您的分叉。


## 解决合并冲突

有时，当您在某个分支中的工作需要很长时间才能完成时，其他人所做的更改与您在打开pull request时对该分支所做的更改相冲突。这称为*rebase* 即合并冲突，当多个人编辑同一文件的同一部分时会发生这种情况。

### 重新调整您的更改

*rebase*是Git的一种方法，它获取在某一点上应用的更改，撤销它们，然后将相同的更改应用到另一点。在合并冲突的情况下，您可以重新设置您的分支以获取在创建分支时和当前时间之间的那段时间所做的更改。

运行以下命令来开始：

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

 这里的`git rev-list` 命令返回当前分支和qmk的主分支之间不同的提交数。我们首先运行`git fetch`，以确保我们有代表upstream仓库的refs。 `git rev-list` 命令的回显有两个数字：

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

第一个数字表示自创建以来当前分支的提交数, 第二个数字是自创建当前分支以来对 `upstream/master` 进行的提交数, 因此, 当前分支中未记录变动。

既然知道当前分支和upstream仓库的当前状态，我们可以开始一个rebase操作：

```
git rebase upstream/master
```

这就是让Git撤销当前分支上的提交，然后根据QMK的主分支重新应用它们。

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

这告诉我们有一个合并冲突，并给出带有冲突的文件的名称。在文本编辑器中打开冲突的文件，在该文件的某个位置，您会发现如下内容：

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

 `<<<<<<< HEAD`行标记合并冲突的开始, `>>>>>>> Commit #1` 行标记结束, 冲突选项被 `=======`分隔。`HEAD`那端的部分来自文件的qmk master版本，标记有commit消息的部分来自当前的分支持和提交。

因为Git跟踪 *对文件的更改* 而不是直接跟踪文件的内容，所以如果Git在提交之前找不到文件中的文本，它将不知道如何编辑该文件。重新编辑文件将解决冲突。进行更改，然后保存文件。

```
<p>Need help? Email support@webhost.us.</p>
```

现在运行:

```
git add conflicting_file_1.txt
git rebase --continue
```

Git记录对冲突文件的更改，并继续应用来自我们的分支的提交，直到它到达末尾。
