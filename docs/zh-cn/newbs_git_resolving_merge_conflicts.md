# Resolving Merge Conflicts

有时当你在一个分支的工作需要很长时间去完成时，其他人的修改会在你打开一个PR时与你对你的分支做出的修改有冲突。这就叫做 *合并冲突*，当不同人编辑同一文件的同一个地方时就会出现这种问题。

?> 阅读本文档需首先了解[你分叉的主分支：总是更新,从不提交](newbs_git_using_your_master_branch.md)。如果你不熟悉该文档，请先阅读，然后继续阅读本文档。

## 重新调整您的更改

*rebase*是Git的一种方法，它获取在某一点上应用的更改，撤销它们，然后将相同的更改应用到另一点。在合并冲突的情况下，您可以重新设置您的分支以获取在创建分支时和当前时间之间的那段时间所做的更改。

运行以下命令来开始：

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

 这里的`git rev-list` 命令返回当前分支和qmk的主分支之间不同提交的数量。我们首先运行`git fetch`，以确保我们有代表upstream仓库状态的refs。 `git rev-list` 命令的回显有两个数字：

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

第一个数字表示自创建以来当前分支的提交数, 第二个数字是自创建当前分支以来对 `upstream/master` 进行的提交数, 因此, 当前分支中未记录这些变动。

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

 `<<<<<<< HEAD`行标记合并冲突的开始, `>>>>>>> Commit #1` 行标记结束, 冲突选项被 `=======`分隔。`HEAD`那部分来自文件的QMK master版本，标记有commit消息的部分来自当前的分支和提交。

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

<!--源文件：https://raw.githubusercontent.com/qmk/qmk_firmware/3152bf572b702109b9b01757ffe900d7f4387faf/docs/newbs_git_resolving_merge_conflicts.md 
    源提交哈希：3152bf572b702109b9b01757ffe900d7f4387faf-->
<!--翻译时间:20200221-17:32(GMT+8)-->
