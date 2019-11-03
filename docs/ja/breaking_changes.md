# 破壊的な変更

このドキュメントはQMKの破壊的な変更のプロセスについて説明します。破壊的な変更とは、互換性が無いあるいは潜在的に危険な方法でQMKが挙動するような修正の変更です。ユーザがQMKツリーを更新してもキーマップが壊れない事を確信できるように、これらの変更を制限します。

破壊的な変更期間は、QMKを危険または予期しない方法で変更するPRをマージする時です。組み込みのテスト期間があるため、問題が起きることはまれか、あるいは予測できないと確信しています。

## 過去の破壊的な変更には何が含まれますか？

* [2019年8月30日](ChangeLog/20190830.md)

## 次の破壊的な変更はいつですか？

次の破壊的な変更は11月29日に予定されています。

### 重要な日付

* [x] 2019 11月21日 - `future` が作成されました。毎週リベースされます。
* [ ] 2019 11月01日 - `future` 新しいPRに対応しません
* [ ] 2019 11月01日 - テスターの募集。
* [ ] 2019 11月27日 - `master`がロックされ、PRはマージされません。
* [ ] 2019 11月29日 - `future` を `master` にマージします。
* [ ] 2019 11月30日 - `master` のロックが解除されます。PRを再びマージすることができます。

## どのような変更が含まれますか？

最新の破壊的な変更候補を見るには、[`breaking_change` ラベル](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+label%3Abreaking_change+is%3Apr)を参照してください。現在と`future` が閉じられる間に新しい変更が追加される可能性があり、そのラベルが適用されたPRはマージされる保証がありません。

このラウンドに破壊的な変更を含めたい場合は、`breaking_change` ラベルを持つPRを作成し、`future` が閉じる前に承認する必要があります。`future` が閉じた後は、新しい破壊的な変更は受け付けられません。

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

## マージの4週間前

* `future` は新しいPRに対して閉じられ、現在のPRの修正のみがマージされます
* テスターの呼び出しを投稿します
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの1週間前

* マスターが <2日前> から終了することを発表します <Day of Merge>
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの2日前

* マスターが2日間閉じられることを発表します
   * [ ] Discord
   * [ ] GitHub PR
   * [ ] https://reddit.com/r/olkb

## マージの日

* `qmk_firmware` git commands
   * [ ] `git checkout future`
   * [ ] `git pull --ff-only`
   * [ ] `git rebase origin/master`
   * [ ] Edit `readme.md`
      * [ ] `future`についてのめもを削除
   * [ ] ChangeLog を1つのファイルにまとめます。
   * [ ] `git commit -m 'Merge point for <DATE> Breaking Change'`
   * [ ] `git push origin future`
* Github アクション
   * [ ] `future`のPRを作成します
   * [ ] travisがクリーンに戻ったことを確認します
   * [ ] `future` PR をマージします
