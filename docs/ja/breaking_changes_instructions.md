# 破壊的な変更: プルリクエストにフラグが付けられた

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.8.75:docs/breaking_changes_instructions.md
  git diff 0.8.75 HEAD -- docs/breaking_changes_instructions.md | cat
-->

QMK のメンバーがあなたのプルリクエストに返信し、あなたの提出したものは破壊的な変更であると述べている場合があります。メンバーの判断では、あなたが提案した変更は QMK やその利用者にとってより大きな意味を持つと考えられます。

プルリクエストにフラグが立てられる原因となるものには、以下のようなものがあります:

- **ユーザーのキーマップに対する編集**
  ユーザーが自分のキーマップを QMK に提出した後、しばらくしてさらに更新してプルリクエストを開いたところ、それが `qmk/qmk_firmware` リポジトリで編集されていたためにマージできなかったことに気づくことがあるかもしれません。すべてのユーザーが Git や GitHub を使いこなせるわけではないので、ユーザー自身で問題を修正できないことに気づくかもしれません。
- **期待される動作の変更**
  QMK の動作を変更した場合、既存の QMK 機能への変更を組み込んだ新しいファームウェアをフラッシュし、希望する動作を復元する手段がないことに気付いた場合、ユーザーはハードウェアまたは QMK が壊れていると考えるようになる可能性があります。
- **ユーザーのアクションを必要とする変更**
  また、ツールチェインを更新したり、Git で何らかのアクションを取るなど、変更はユーザーが行う必要がある場合もあります。
- **精査が必要な変更**
  時には、投稿がプロジェクトとしての QMK に影響を与えることもあります。これは、著作権やライセンスの問題、コーディング規約、大規模な機能のオーバーホール、コミュニティによるより広範なテストを必要とする「リスクの高い」変更、あるいは全く別のものである可能性があります。
- **エンドユーザーとのコミュニケーションを必要とする変更**
  これには、将来の非推奨化への警告、時代遅れの慣習、その他伝えなければならないが上記のカテゴリのどれかに当てはまらないものが含まれます。

## 何をすればいいのか?

提出したものが破壊的な変更だと判断された場合、手続きをスムーズに進めるためにできることがいくつかあります。

### PRを分割することを検討する

If you are contributing core code, and the only reason it needs to go through breaking changes is that you are updating keymaps to match your change, consider whether you can submit your feature in a way that the old keymaps continue to work. Then submit a separate PR that goes through the breaking changes process to remove the old code.

### ChangeLog エントリの提供

We require submissions that go through the Breaking Change process to include a changelog entry. The entry should be a short summary of the changes your pull request makes &ndash; [each section here started as a changelog](ChangeLog/20190830.md "n.b. This should link to the 2019 Aug 30 Breaking Changes doc  - @noroadsleft").

Your changelog should be located at `docs/ChangeLog/YYYYMMDD/PR####.md`, where `YYYYMMDD` is the date on which QMK's breaking change branch &ndash; usually named `future` &ndash; will be merged into the `master` branch, and `####` is the number of your pull request.

If your submission requires action on the part of users, your changelog should instruct users what action(s) must be taken, or link to a location that does so.

### 変更点を文書化する

Understanding the purpose for your submission, and possible implications or actions it will require can make the review process more straightforward. A changelog may suffice for this purpose, but more extensive changes may require a level of detail that is ill-suited for a changelog.

Commenting on your pull request and being responsive to questions, comments, and change requests is much appreciated.

### 助けを求める

あなたの提出物にフラグが立ったことで、あなたは油断してしまったかもしれません。もし、あなた自身が脅かされたり、圧倒されたりしていることに気付いたら、私たちに知らせてください。プルリクエストについてコメントするか、[DiscordでQMKチームに連絡を取る](https://discord.gg/Uq7gcHh)。
