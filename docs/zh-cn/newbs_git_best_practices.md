# QMK所采用的Git最佳实践

<!---
  original document: 0.15.17:docs/newbs_git_best_practices.md 
  git diff 0.15.17 HEAD -- docs/newbs_git_best_practices.md  | cat
-->

*译者注：对于git相关的部分，除广为接受的名词外，会尽量保留git命令及各种术语的英文版本，部分名词及关键部分会附带中文翻译*

## 或者讲，"怎么才能不害怕并喜欢上Git"

本节旨在以最佳方式指导新手在为QMK做贡献时获得流畅的体验。我们将进行一次完整的QMK贡献操作流程，并在部分环节中详细讲述几种便捷的方法，之后我们会故意搞砸一些东西，并教导你如何回到正轨。

该章节做了如下假设：

1. 你已有Github账号且已[fork了qmk_firmware仓库](zh-cn/getting_started_github.md)到你的账号下。
2. 已完成了[构建环境](zh-cn/newbs_getting_started.md#set-up-your-environment)及[QMK](zh-cn/newbs_getting_started.md#set-up-qmk)配置。

---

- 第一节：[在你Fork的主干上：频繁更新，不要提交](zh-cn/newbs_git_using_your_master_branch.md)
- 第二节：[解决合并冲突](zh-cn/newbs_git_resolving_merge_conflicts.md)
- 第三节：[重新同步一个脱离同步状态的Git分支](zh-cn/newbs_git_resynchronize_a_branch.md)
