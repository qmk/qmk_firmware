# QMK における Git 運用作法 :id=best-git-practices-for-working-with-qmk

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.9.0:docs/newbs_git_best_practices.md
  git diff 0.9.0 HEAD -- docs/newbs_git_best_practices.md | cat
-->

## または、"如何にして私は心配することをやめて Git を愛することを学んだか。"

このセクションは、QMK への貢献をスムーズに行なう最もよい方法を初心者に教えることを目的としています。
QMK に貢献するプロセスを順を追って説明し、この作業を簡単にするいくつかの方法を詳しく説明します。
その後、意図的に一部を壊してみせて、それらを修正する方法を説明します。

このセクションは以下のことを前提としています:

1. あなたは GitHub アカウントがあり、アカウントに [qmk_firmware リポジトリをフォーク](ja/getting_started_github.md) している。
2. あなたは、[環境構築](ja/newbs_getting_started.md#set-up-your-environment) と [QMK の設定](ja/newbs_getting_started.md#set-up-qmk) を両方とも完了している。

---

- パート 1: [あなたのフォークの master ブランチ: 更新は頻繁に、コミットはしないこと](ja/newbs_git_using_your_master_branch.md)
- パート 2: [マージの競合の解決](ja/newbs_git_resolving_merge_conflicts.md)
- パート 3: [同期のとれていない git ブランチの再同期](ja/newbs_git_resynchronize_a_branch.md)
