# Comment utiliser GitHub avec QMK

GitHub peut être un peu compliqué pour ceux qui n'y sont pas familier. Ce guide va vous expliquer chaque étape de "fork", clone et envoi d'un pull request avec QMK.

?> Ce guide part du principe que vous êtes suffisamment à l'aise pour envoyer commandes sur la ligne de commande et que vous avez Git installé sur votre système.

Commencez par la [page GitHub de QMK](https://github.com/qmk/qmk_firmware), et vous verrez un bouton dans le coin en haut à droite qui indique "Fork":

![Fork on GitHub](http://i.imgur.com/8Toomz4.jpg)

Si vous faites partie d'une organisation, vous aurez besoin de savoir quel compte utiliser pour le fork. Dans la plupart des cas, vous voudrez créer le fork dans votre compte personnel. Une fois le fork complet (cela peut quelques fois prendre un peu de temps), appuyez sur le bouton "Clone or download":

![Download from GitHub](http://i.imgur.com/N1NYcSz.jpg)

Faites attention à sélectionner "HTTPS", et sélectionnez le lien et copiez-le:

![HTTPS link](http://i.imgur.com/eGO0ohO.jpg)

Ensuite, entrez `git clone --recurse-submodules ` dans la ligne de commande, et collez votre lien:

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

Vos changements existent maintenant dans votre fork sur GitHub. Si vous allez à cette adresse (`https://github.com/<whoeveryouare>/qmk_firmware`), vous pouvez créer un nouveau "Pull Request" en cliquant sur ce bouton:

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

Maintenant, vous pourrez voir exactement ce que vous avez commité. Si ça vous semble bien, vous pouvez le finaliser en cliquant sur "Create Pull Request":

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

Une fois transmis, nous pourrons vous parler de vos changements, vous demander de faire des changements, et éventuellement de les accepter!

Merci de contribuer à QMK :)
