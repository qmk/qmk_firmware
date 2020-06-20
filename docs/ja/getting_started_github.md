# QMK で GitHub を使う方法

<!---
  original document: 0.8.82:docs/getting_started_github.md
  git diff 0.8.82 HEAD -- docs/getting_started_github.md | cat
-->

GitHub は慣れていない人には少し注意が必要です - このガイドは、QMK におけるフォーク、クローン、プルリクエストのサブミットの各ステップについて説明します。

?> このガイドでは、あなたがコマンドラインでの実行にある程度慣れており、システムに git がインストールされていることを前提にしています。

[QMK GitHub ページ](https://github.com/qmk/qmk_firmware)を開くと、右上に "Fork" というボタンが見えます:

![Git でのフォーク](http://i.imgur.com/8Toomz4.jpg)

あなたが組織の一員である場合は、どのアカウントにフォークするかを選択する必要があります。ほとんどの場合、あなたの個人のアカウントにフォークしたいでしょう。フォークが完了したら(しばらく時間が掛かる場合があります)、"Clone or Download" ボタンをクリックします:

![Git からダウンロード](http://i.imgur.com/N1NYcSz.jpg)

必ず "HTTPS" を選択し、リンクを選択してコピーします:

![HTTPS リンク](http://i.imgur.com/eGO0ohO.jpg)

ここから、`git clone --recurse-submodules ` をコマンドラインに入力し、リンクを貼り付けます:

```
user@computer:~$ git clone --recurse-submodules https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Enumerating objects: 9, done.
remote: Counting objects: 100% (9/9), done.
remote: Compressing objects: 100% (5/5), done.
remote: Total 183883 (delta 5), reused 4 (delta 4), pack-reused 183874
Receiving objects: 100% (183883/183883), 132.90 MiB | 9.57 MiB/s, done.
Resolving deltas: 100% (119972/119972), done.
...
Submodule path 'lib/chibios': checked out '587968d6cbc2b0e1c7147540872f2a67e59ca18b'
Submodule path 'lib/chibios-contrib': checked out 'ede48346eee4b8d6847c19bc01420bee76a5e486'
Submodule path 'lib/googletest': checked out 'ec44c6c1675c25b9827aacd08c02433cccde7780'
Submodule path 'lib/lufa': checked out 'ce10f7642b0459e409839b23cc91498945119b4d'
Submodule path 'lib/ugfx': checked out '3e97b74e03c93631cdd3ddb2ce43b963fdce19b2'
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

あなたの変更は今では GitHub 上のフォークにあります - フォーク (`https://github.com/<whoeveryouare>/qmk_firmware`)に戻ると、"New Pull Request" ボタンをクリックすることで新しいプルリクエストを作成することができます:

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

ここでは、コミットした内容を正確に確認することができます - 全て良いように見える場合は、"Create Pull Request" をクリックすることで最終的に承認することができます:

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

サブミットの後で、私たちはあなたの変更について話し、変更を依頼し、最終的にそれを受け入れるでしょう！QMK に貢献してくれてありがとう :)
