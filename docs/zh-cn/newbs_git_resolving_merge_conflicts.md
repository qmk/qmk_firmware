# 解决合并冲突

<!---
  original document: 0.15.17:docs/newbs_git_resolving_merge_conflicts.md 
  git diff 0.15.17 HEAD -- docs/newbs_git_resolving_merge_conflicts.md  | cat
-->

有时在你致力于一个较长周期才能完成的分支时，其它人提交的变更会与你提交的pull request中的变更发生冲突。我们将这种多个人编辑同一个模块同一个文件时产生的场景叫做 *合并冲突*

?> 本文中的场景基于[在你Fork的主干上：频繁更新，不要提交](zh-cn/newbs_git_using_your_master_branch.md)一文。如果你对那篇文章不熟悉，请先阅读它，再回来继续。

## 变基/衍合（rebase）


Git的*变基*操作会将提交历史中的提交节点摘除并回滚，然后统一提交到一个新节点上。在解决合并冲突时，可以通过对当前分支进行变基，来获取从分支拉取到当前时刻的所有变更。

从执行如下命令开始：

```
git fetch upstream
git rev-list --left-right --count HEAD...upstram/master
```

此处输入的 `git rev-list` 命令可以得到当前分支与QMK主干分支间的提交数量差。而先执行 `git fetch` 是为了确保我们有上游仓库（upstream repo）的最新状态。`git rev-list` 命令会返回两个数字：

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

第一个数字为当前分支自创建后新增的提交数量。第二个数字为当前分支创建后在 `upstream/master` 上的提交数量，而这部分就是我们当前分支上缺失的提交记录。

在我们了解了当前分支以及上游仓库的状态后，可以发起变基操作了：

```
git rebase upstream/master
```

这样可以让Git回滚该分支的提交，然后基于QMK的主干版本重新应用这些提交。

*译注：以下内容在中文Git下大同小异，且仅作为示例，不进行翻译*
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

以上内容是在告诉我们有合并冲突存在，并给出了冲突所在的文件名。在编辑器中打开该文件，可以在某处发现类似如下形式的内容：

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

`<<<<<<< HEAD` 标记了合并冲突的起始行，直至 `>>>>>>> Commit #1` 标记的结束行，中间通过 `=======` 分隔开冲突双方。其中 `HEAD` 部分为QMK主干上的版本，标记了提交日志的部分为当前分支的本地提交。

由于Git存储的是*文件差异部分*而非整个文件，所以当Git无法在文件中找到一个变更发生前的内容时，就无法知道如何去进行文件变更，重新编辑一下可以解决问题。在更改完成后，保存文件。

```
<p>Need help? Email support@webhost.us.</p>
```

之后，执行：

```
git add conflicting_file_1.txt
git rebase --continue
```

Git即会记录对文件冲突做出的变更，并继续处理剩余的提交，直至全部完成。
