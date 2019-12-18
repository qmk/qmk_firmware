# QMK で Github を使う方法

<!---
  original document: d598f01cb:getting_started_github.md
  git diff d598f01cb HEAD getting_started_github.md | cat
-->

Github は慣れていない人には少し注意が必要です - このガイドは、QMK におけるフォーク、クローン、プルリクエストのサブミットの各ステップについて説明します。

?> このガイドでは、あなたがコマンドラインでの実行にある程度慣れており、システムに git がインストールされていることを前提にしています。

[QMK Github ページ](https://github.com/qmk/qmk_firmware)を開くと、右上に "Fork" というボタンが見えます:

![Git でのフォーク](http://i.imgur.com/8Toomz4.jpg)

あなたが組織の一員である場合は、どのアカウントにフォークするかを選択する必要があります。ほとんどの場合、あなたの個人のアカウントにフォークしたいでしょう。フォークが完了したら(しばらく時間が掛かる場合があります)、"Clone or Download" ボタンをクリックします:

![Git からダウンロード](http://i.imgur.com/N1NYcSz.jpg)

必ず "HTTPS" を選択し、リンクを選択してコピーします:

![HTTPS リンク](http://i.imgur.com/eGO0ohO.jpg)

ここから、`git clone` をコマンドラインに入力し、リンクを貼り付けます:

```
user@computer:~$ git clone --recurse-submodules https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Counting objects: 46625, done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 46625 (delta 0), reused 0 (delta 0), pack-reused 46623
Receiving objects: 100% (46625/46625), 84.47 MiB | 3.14 MiB/s, done.
Resolving deltas: 100% (29362/29362), done.
Checking out files: 100% (2799/2799), done.
```

ローカルマシンに QMK のフォークができるので、キーマップの追加、コンパイル、キーボードへの書き込みができます。変更に満足したら、以下のようにそれらをフォークへ追加、コミットおよびプッシュすることができます:

```
user@computer:~$ git add .
user@computer:~$ git commit -m "adding my keymap"
[master cccb1608] adding my keymap
 1 file changed, 1 insertion(+)
 create mode 100644 keyboards/planck/keymaps/mine/keymap.c
user@computer:~$ git push
Counting objects: 1, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (1/1), done.
Writing objects: 100% (1/1), 1.64 KiB | 0 bytes/s, done.
Total 1 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local objects.
To https://github.com/whoeveryouare/qmk_firmware.git
 + 20043e64...7da94ac5 master -> master
```

あなたの変更は今では Github 上のフォークにあります - フォーク (`https://github.com/<whoeveryouare>/qmk_firmware`)に戻ると、"New Pull Request" ボタンをクリックすることで新しいプルリクエストを作成することができます:

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

ここでは、コミットした内容を正確に確認することができます - 全て良いように見える場合は、"Create Pull Request" をクリックすることで最終的に承認することができます:

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

サブミットの後で、私たちはあなたの変更について話し、変更を依頼し、最終的にそれを受け入れるでしょう！QMK に貢献してくれてありがとう :)
