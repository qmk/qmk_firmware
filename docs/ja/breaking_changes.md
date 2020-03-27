# 破壊的な変更

<!---
  grep --no-filename "^[ ]*git diff" docs/ja/*.md | sh
  original document: 0.8.75:docs/breaking_changes.md
  git diff 0.8.75 HEAD -- docs/breaking_changes.md | cat
-->

このドキュメントは QMK の破壊的な変更のプロセスについて説明します。破壊的な変更とは、互換性が無いあるいは潜在的に危険な方法で QMK が挙動するような修正の変更です。ユーザが QMK ツリーを更新してもキーマップが壊れない事を確信できるように、これらの変更を制限します。

破壊的な変更期間は、QMK を危険または予期しない方法で変更する PR をマージする時です。組み込みのテスト期間があるため、問題が起きることはまれか、あるいは予測できないと確信しています。

## 過去の破壊的な変更には何が含まれますか？

* [2020年年2月29日](ja/ChangeLog/20200229.md)
* [2019年8月30日](ja/ChangeLog/20190830.md)

## 次の破壊的な変更はいつですか？

次の破壊的な変更は2020年5月30日に予定されています。

### 重要な日付

* [x] 2020年 2月29日 - `future` が作成されました。毎週リベースされます。
* [ ] 2020年 5月02日 - `future` 新しいPRに対応しません
* [ ] 2020年 5月02日 - テスターの募集。
* [ ] 2020年 5月28日 - `master`がロックされ、PRはマージされません。
* [ ] 2020年 5月30日 - `future` を `master` にマージします。
* [ ] 2020年 5月30日 - `master` のロックが解除されます。PRを再びマージすることができます。

## どのような変更が含まれますか？

最新の破壊的な変更候補を見るには、[`breaking_change` ラベル](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+label%3Abreaking_change+is%3Apr)を参照してください。現在と`future` が閉じられる間に新しい変更が追加される可能性があり、そのラベルが適用されたPRはマージされる保証がありません。

このラウンドに破壊的な変更を含めたい場合は、`breaking_change` ラベルを持つ PR を作成し、`future` が閉じる前に承認する必要があります。`future` が閉じた後は、新しい破壊的な変更は受け付けられません。

受け入れの基準:

* PR が完了し、マージの準備ができている
* PR が ChangeLog を持つ

# チェックリスト

この章では、破壊的な変更プロセスを実行する時に使用する様々なプロセスについて説明します。

## `master`から `future` をリベースします

これは`future`が開いている間、毎週金曜日に実行されます。

プロセス:

```
cd qmk_firmware
git checkout master
git pull --ff-only
git checkout future
git rebase master
git push --force
```

## `future`ブランチの作成

以前の`future`ブランチがマージされた直後に、これが発生します。

* `qmk_firmware` git commands
   * [ ] `git checkout master`
   * [ ] `git pull --ff-only`
   * [ ] `git checkout -b future`
   * [ ] Edit `readme.md`
      * [ ] これがテストブランチであることを上部に大きな通知で追加します。
      * [ ] このドキュメントへのリンクを含める
   * [ ] `git commit -m 'Branch point for <DATE> Breaking Change'`
   * [ ] `git tag breakpoint_<YYYY>_<MM>_<DD>`
   * [ ] `git tag <next_version>` # ブレーキング ポイント タグがバージョンの増分を混乱させないようにします
   * [ ] `git push origin future`
   * [ ] `git push --tags`

## マージの 4 週間前

* `future` は新しい PR に対して閉じられ、現在の PR の修正のみがマージされます
* テスターの呼び出しを投稿します
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの 1 週間前

* マスターが < 2 日前> から終了することを発表します <Day of Merge>
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの 2 日前

* マスターが 2 日間閉じられることを発表します
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの日

* `qmk_firmware` git commands
   * [ ] `git checkout future`
   * [ ] `git pull --ff-only`
   * [ ] `git rebase origin/master`
   * [ ] Edit `readme.md`
      * [ ] `future` についてのめもを削除
   * [ ] ChangeLog を 1 つのファイルにまとめます。
   * [ ] `git commit -m 'Merge point for <DATE> Breaking Change'`
   * [ ] `git push origin future`
* Github アクション
   * [ ] `future`の PR を作成します
   * [ ] travis がクリーンに戻ったことを確認します
   * [ ] `future` PR をマージします
