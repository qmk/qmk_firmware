# Best Practices GIT

## Ou, « Comment j’ai appris à cesser de m’inquiéter et à aimer Git »

Ce document a pour objectif d’apprendre à des débutants les meilleurs moyens pour avoir une bonne experience dans la contribution à QMK. Nous allons parcourir le processus de contribution et détailler certains moyens de rendre les taches plus faciles. Par la suite, nous allons provoquer des problèmes volontairement pour vous apprendre comment les résoudre.

Ce document part des principes suivant :

1. Vous avez un compte Github, et vous avez [forké le dépôt QMK](getting_started_github.md) avec votre compte.
2. Vous avez [mis en place votre environnement de compilation](newbs_getting_started.md?id=environment-setup).

## Sur la master de votre fork : Souvent se mettre à jour , ne jamais commiter

Il est très fortement recommandé pour les développements QMK, peut-importe ce qui doit être fait et ou, que vous gardiez votre branche `master` à jour, mais que vous ne commitiez ***jamais*** sur celle-ci.
À la place, réalisez tous vos changements sur une branche principale de développement et effectuez des pull-requests à partir de vos branches vers celle-ci.

Pour réduire les chances d’avoir des conflits de merge &mdash; ce qui se produit quand deux ou plus d’utilisateurs ont édité la même section d’un fichier en même temps &mdash; gardez votre branche `master` relativement à jour et commencer tous vos développments sur de nouvelles branches.

### Maintenir votre branche `master` à jour

Pour maintenir votre `master` à jour, il est fortement recommandé d’ajouter le dépôt QMK (« repo ») comme un dépôt distant (« remote ») sur git. Pour faire ceci, ouvrez votre terminal git et saisissez :

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

Pour vérifier que ce dépôt a bien été ajouté, saisissez `git remote -v`, qui doit retourner les informations suivantes :

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

Maintenant que cela est fait, vous vérifier les mises-à-jour en lançant `git fetch upstream`. Cela retrouve toutes les branches et les tags &mdash; que l’on appellera des réferences `refs` &mdash; du dépôt QMK, qui a désormais le surnom `upstream`. Il est désormais possible de comparer les données de notre fork `origin` to celles détenues sur QMK.

Pour mettre à jour la master de votre fork, lancez ces commandes en utilisant la touche Entrée entre chacunes :

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

Cela vous change la branche courante en `master`, synchronise les données de réferences du dépôt QMK vers votre ordinateur. La commande pull tire les données de réferences vers votre branche courante puis les y téleverse. La commande push permet de pousser la branche courante (`master`) vers votre fork github.

### Faire des modifications

Pour faire des modifications, créez une nouvelle branche en entrant les commandes suivantes :

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

Cela permet de créer une branche nommée `dev_branch` puis la place en branche courante. La commande push vas pousser votre nouvelle branche sur votre dépôt github fork. L’argument `--set-upstream` n’a besoin d’être utilisé qu’une fois. Il permet de relier la branche locale `dev_branch` à la branche de même nom sur le dépôt distant de votre fork. Une fois avoir saisi cet argument, vous pourrez utiliser `git push` ou `git pull` sans le préciser à nouveau.

!> Avec `git push`, vous pouvez utiliser l’argument `-u` à la place de `--set-upstream` &mdash; `-u` est un alias de `--set-upstream`.

Vous pouvez nommer vos branches de la manière que vous souhaitez. Cependant il est recommandé de les nommer de manière à représenter les changements que vous souhaitez faire.

Par défaut `git checkout -b` permet de créer une branche à partir de l’état actuel de votre branche courrante. Il est tout a fait possible de créer une branche à partir d’une autre branche que la branche courrante en stipulant son nom à la commande :

```
git checkout -b dev_branch master
```

Maintenant que vous avez une branche de développement, ouvrez votre éditeur de texte et réalisez une modification dont vous avez besoin. Il est recommandé de réaliser des petits commits sur votre branche. De cette manière, le moindre changement qui causera un problème pourra être plus facilement identifié ou annulé si besoin. Pour faire vos changements il vous faudra modifier et sauvegarder chacun des fichiers qui doivent être changés puis les ajouter dans la « Git’s *staging area* » et les commiter :

```
git add path/to/updated_file
git commit -m "My commit message."
```

`git add` ajoutera tous les fichiers listés dans la *staging area*.
Les fichiers dans la staging area sont tout simplement les fichiers dont vous actez qu’ils seront commités. Ainsi il vous sera possible de sélectionner parmi vos changements ceux devant être commités avec un `git commit`.

`git commit` sauvegarde les changements de la *staging area* sur la branche courante du dépôt local. Utilisez des messages de commit vous permettant de savoir ce que vous avez changé en regardant l’historique.

!> Si vous avez modifié de nombreux fichiers et qu’ils sont tous modifiés dans le cadre d’un même changement alors vous pouvez utiliser `git add .` pour ajouter tous les fichiers de votre dossier courrant plutôt que de les ajouter individuellement.

### Publier vos changements

La dernière étape est de pousser vos changements dans votre fork github. Pour faire ceci, utilisez `git push`. Git vas publier l’état actuel des commits de votre branche courrante `dev_branch` dans votre fork sur github.


## Résoudre des conflits sur votre branche

Parfois vous pourrez travailler sur une branche pendant suffisament de temps pour que certains de vos changements sur votre branche soient en conflit avec certains changements d’autres utilisateurs. Vous vous en rendrez compte en ouvrant un pull-request. Ces conflits se nomme *merge conflict* et ils surviennent quand plusieurs personnes modifient la même partie du même fichier.

### Rebaser vos changements

Un *rebase* est le moye pour git de prendre des changements appliqué à un moment, les annuler, et les réappliquer à un autre moment. Dans le cas d’un *merge conflict*, vous devrez rebaser votre branche pour intégrer les changements des autres utilisateurs avant les votre.

Pour réaliser cela, utilisez les commandes suivantes :

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

La commande `git rev-list` affichera le nombre de commits qui diffèrent entre votre branche courrante et la branche `master` de QMK. Nous lançons `git fetch` préalablement pour être sur que nos réferences représentent l’état courrant du dépôt `upstream` (le dépôt principale de QMK). La sortie de `git rev-list` vas présenter deux nombres :

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

Le premier représente le nombre de commits de la branche courante depuis qu’elle a été créée. Le second montre le nombre de commits qui ont étés réalisée dans `upstream/master` depuis que la branche courrante a été créée, et donc, les changements qui ne sont pas présents dans la branche courrante.

Maintenant que l’état de la branche courante et de la branche distante sont connus alors nous pouvons lancer l’opération de rebase :

```
git rebase upstream/master
```

Cette commande demande à Git d’annuler tous les commits de la branche courante, puis de les réappliquer sur l’état actuel de la branche `master` de QMK.

```
$ git rebase upstream/master
First, rewinding head to replay your work on top of it...
Applying: Commit #1
Using index info to reconstruct a base tree...
M       conflicting_file_1.txt
Falling back to patching base and 3-way merge...
Auto-merging conflicting_file_1.txt
CONFLICT (content): Merge conflict in conflicting_file_1.txt
error: Failed to merge in the changes.
hint: Use 'git am --show-current-patch' to see the failed patch
Patch failed at 0001 Commit #1

Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
```

Si vous obtenez cette sortie, c’est que vous avez des merge-conflicts. Cela nous donne le nombre de fichier avec des conflits. Ouvrez les fichiers en conflit avec votre éditeur de texte, et dans le fichier vous trouverez quelque chose comme ceci :

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

La ligne `<<<<<<< HEAD` marque le début d’un conflit et la ligne `>>>>>>> Commit #1` en marque la fin. Chaque section en conflit sera séparé par `=======`. La section `HEAD` est la version de la branche `master` de QMK du fichier, et la section marqué avec le message de commit est l’état de votre branche courrante et du commit en cours de ré-application.

Git traque les *changements des fichiers* plutôt que les contenus des fichiers directement et il peut arriver qu’il ne trouve pas le texte présent dans le fichier avant un de vos commit. Alors il ne saura pas comment modifier le fichier, et il faudra modifier le fichier à la main pour corriger le conflit. Réalisez vos changements et sauvegardez le fichier.

```
<p>Besoin d’aide ? Contactez support@webhost.us.</p>
```

Une fois fait, lancez la commande suivante :

```
git add conflicting_file_1.txt
git rebase --continue
```

Git vas tracer tous les changements du fichier en conflit, et vas continuer d’appliquer les commits de la branche tant jusqu’à la fin des commits.
