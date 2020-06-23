# ドキュメントベストプラクティス

<!---
  original document: 0.9.19:docs/documentation_best_practices.md
  git diff 0.9.19 HEAD -- docs/documentation_best_practices.md | cat
-->

このページは QMK のためのドキュメントを作成する時のベストプラクティスを文章化するために存在します。これらのガイドラインに従うことで、一貫したトーンとスタイルを維持することに役立ちます。これは他の人が QMK をより簡単に理解するのに役立ちます。

# ページの開始

ドキュメントページは通常 H1 ヘッダから始まり、ユーザがこのページで見つける内容の一段落の説明が続く必要があります。この見出しと段落は目次の次にあるため、見出しを短くして、空白の無い長い文字列を避けるように気を付けてください。

例:

```
# My Page Title

This page covers my super cool feature. You can use this feature to make coffee, squeeze fresh oj, and have an egg mcmuffin and hashbrowns delivered from your local macca's by drone.
```

# 見出し

通常、ページには複数の "H1" 見出しが必要です。目次には H1 と H2 見出しのみが含まれるため、適切に計画してください。目次が広くなりすぎないように、H1 と H2 の見出しでは幅を広げないようにしてください。

# スタイル付きのヒントボックス

注目を集めるためにテキストの周囲にスタイル付きのヒントボックスを描画することができます。

### Important

```
!> This is important
```

以下のように描画されます:

!> This is important

### 一般的なヒント

```
?> This is a helpful tip.
```

以下のように描画されます:

?> This is a helpful tip.


# 文章化機能

QMK のために新しい機能を作成した場合、そのドキュメントページを作成してください。長い必要は無く、機能を説明する幾つかの文と、関連するキーコードをリストした表で十分です。以下は基本的なテンプレートです:

```markdown
# My Cool Feature

This page describes my cool feature. You can use my cool feature to make coffee and order cream and sugar to be delivered via drone.

## My Cool Feature Keycodes

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_COFFEE||Make Coffee|
|KC_CREAM||Order Cream|
|KC_SUGAR||Order Sugar|
```

ドキュメントを `docs/feature_<my_cool_feature>.md` に配置し、そのファイルを `docs/_sidebar.md` の適切な場所に追加します。キーコードを追加した場合は、機能ページに戻るリンクとともに `docs/keycodes.md` に追加するようにしてください。
