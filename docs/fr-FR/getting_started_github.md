# Comment utiliser GitHub avec QMK

GitHub peut être un peu compliqué pour ceux qui n'y sont pas familier. Ce guide va vous expliquer chaque étape de "fork", clone et envoi d'un pull request avec QMK.

?> Ce guide part du principe que vous êtes suffisamment à l'aise pour envoyer commandes sur la ligne de commande et que vous avez Git installé sur votre système.

Commencez par la [page GitHub de QMK](https://github.com/qmk/qmk_firmware), et vous verrez un bouton dans le coin en haut à droite qui indique "Fork":

![Fork on Github](http://i.imgur.com/8Toomz4.jpg)

Si vous faites partie d'une organisation, vous aurez besoin de savoir quel compte utiliser pour le fork. Dans la plupart des cas, vous voudrez créer le fork dans votre compte personnel. Une fois le fork complet (cela peut quelque fois prendre un peu de temps), appuyez sur le bouton "Clone or download":

![Download from Github](http://i.imgur.com/N1NYcSz.jpg)

Faites attention à sélectionner "HTTPS", et sélectionnez le liens et copiez-le:

![HTTPS link](http://i.imgur.com/eGO0ohO.jpg)

Ensuite, entrez `git clone` dans la ligne de commande, et collez votre lien:

```
user@computer:~$ git clone https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Counting objects: 46625, done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 46625 (delta 0), reused 0 (delta 0), pack-reused 46623
Receiving objects: 100% (46625/46625), 84.47 MiB | 3.14 MiB/s, done.
Resolving deltas: 100% (29362/29362), done.
Checking out files: 100% (2799/2799), done.
```

Vous avez maintenant votre fork QMK sur votre machine locale, vous pouvez ajouter votre keymap, la compiler et la flasher sur votre board. Une fois heureux avec vos changements, vous pouvez les ajouter, commit, et pousser vers votre fork comme suit:

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

Vos changements existent maintenant dans votre fork sur GitHub. Si vous allez à cete adresse (`https://github.com/<whoeveryouare>/qmk_firmware`), vous pouvez créer un nouveau "Pull Request" en cliquant sur ce bouton:

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

Maintenant, vous pourrez voir exactement ce que vous avez commité. Si ça vous semble bien, vous pouvez le finaliser en cliquant sur "Create Pull Request":

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

Une fois transmis, nous pourrons vous parler de vos changements, vous demander de faire des changements, et éventuellement de les accepter!

Merci de contribuer à QMK :)
