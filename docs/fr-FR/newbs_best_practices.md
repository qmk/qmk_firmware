# Bonnes Pratiques

## Ou, "Comment j'ai appris à ne plus m'en faire et aimer Git."

Ce document a pour but d'apprendre aux novices les meilleures solutions pour faciliter la contribution à QMK. Nous allons étudier le processus de contribution à QMK, détaillant quelques moyens de rendre cette tâche plus simple. Nous allons faire quelques erreurs afin de vous apprendre à les résoudre.

Ce document suppose les choses suivantes:

1. Vous avez un compte GitHub, et avez [créé un "fork" pour le dépôt qmk_firmware](fr-FR/getting_started_github.md) avec votre compte.
2. Vous avez [configuré votre environnement de compilation](fr-FR/newbs_getting_started.md?id=environment-setup).

## La branche master de votre fork: Mettre à jour souvent, ne jamais commit

Il est hautement recommandé pour le développement de QMK, peu importe ce qui est fait ou où, de garder votre branche `master` à jour, mais de ne ***jamais*** commit dessus. A la place, faites tous vos changement dans une branche de développement et crééz des "pull requests" de votre branche lorsque vous développez.

Pour réduire les chances de conflits de fusion (merge) &mdash; des cas où deux ou plus d'utilisateurs ont édité la même section d'un fichier en parallèle &mdash; gardez votre branche `master` relativement à jour et démarrez chaque nouveau développement en créant une nouvelle branche.

### Mettre à jour votre branche master

Pour garder votre branche `master` à jour, il est recommandé d'ajouter le dépôt du firmware QMK comme un dépôt distant (remote) dans git. pour se faire, ouvrez votre interface de ligne de commande Git et entrez:

```bash
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

Pour vérifier que le dépôt a bien été ajouté, lancez la commande `git remote -v`, qui devrait retourner le résultat suivant:

```bash
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

Maintenant que c'est fait, vous pouvez vérifier les mises à jour au dépôt en lançant `git fetch upstream`. Cela récupère les branches et les tags &mdash; appelé de manière générale "refs" &mdash; du dépôt QMK, qui a maintenant le surnom `upstream`. Nous pouvons maintenant comparer les données sur notre "fork" `origin` à celles contenues par QMK.

Pour mettre à jour la branche master de votre "fork", lancez les commandes suivantes (en appuyant sur Enter après chaque ligne):

```bash
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

Cela vous change la branche courante en master, synchronise les données de réferences du dépôt QMK vers votre ordinateur. La commande pull tire les données de réferences vers votre branche courante puis les y téleverse. La commande push permet de pousser la branche courante (master) vers votre fork github.

### Faire des changements

Pour faire des changements, créez une nouvelle branche en entrant:

```bash
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

Ceci crée une branche nommée `dev_branch`, bascule vers cette branche, et ensuite sauvegarde cette nouvelle branche vers votre fork. L'argument `--set-upstream` demande à git d'utiliser votre fork et la branche `dev_branch` à chaque fois que vous utilisez `git push` ou `git pull` depuis cette branche. Vous ne devez l'utiliser que pour le premier "push", après celà, vous pouvez utiliser simplement `git push` ou `git pull`, sans le reste des arguments.

!> Avec `git push`, vous pouvez utiliser `-u` à la place de `--set-upstream` &mdash; `-u` est un alias pour `--set-upstream`.

Vous pouvez appeler votre branche à peu prêt comme vous voulez, toutefois il est recommandé d'utiliser un nom qui est lié aux changements que vous allez faire.

Par défaut, `git checkout -b` va faire de la branche actuelle la branche de base de votre nouvelle branche. Vous pouvez définir la base de votre nouvelle branche comme étant n'importe quelle branche existante qui n'est pas la courante en utilisant la commande:

```bash
git checkout -b dev_branch master
```

Maintenant que vous avez une branche de développement, ouvrez votre éditeur de texte et faites vos changements. Il est recommandé de faire beaucoup de petits commits dans votre branche. Ainsi, un changement qui crée un problème peut être plus facilement retracé et annulé si nécessaire. Pour faire un changement, éditez et sauvez n'importe quel fichier qui doit être mis à jour, ajoutez les à la *zone de staging* de Git, et commitez les vers votre branche:

```bash
git add path/to/updated_file
git commit -m "My commit message."
```

`git add` ajoute les fichiers qui ont été changés dans la *zone de staging* de Git, qui est sa "zone de chargement". Elle contient tous les changements qui vont être *validés* (committed) par `git commit`, qui sauvegarde les changements vers le dépôt. Utilisez des messages de validation descriptifs afin que vous puissiez savoir ce qui a changé d'un coup d'oeil.

!> Si vous changez beaucoup de fichiers, mais tous les fichiers font partie du même changement, vous pouvez utiliser `git add .` pour ajouter tous les fichiers changés dans le répertoire courant, plutôt que d'avoir à ajouter chaque fichiers individuellement.

### Publier Vos Changements

La dernière étape est de pousser vos changements vers votre fork. pour se faire, entrez `git push`. Git publie maintenant l'état courant de `dev_branch` vers votre fork.

## Résoudre Les Conflits De Merge

Parfois, lorsque votre travail sur une branche met beaucoup de temps à se compléter, des changements réalisés par d'autres peuvent entrer en conflit avec les changements que vous avez fait sur votre branche au moment où vous avez ouvert un pull request. Ceci est appelé un *conflit de merge*, et c'est ce qui arrive lorsque plusieurs personnes modifient les mêmes parties de mêmes fichiers.

### Rebaser Vos Changements

Un *rebase* est la manière pour Git de prendre les changements qui ont été faits à un point, les annuler, et les réappliquer sur un autre point. Dans le cas d'un conflit de merge, vous pouvez rebaser votre branche pour récupérer les changements qui ont été faits entre le moment où vous avez créé votre branche et le présent.

Pour démarrer, lancez les commandes suivantes:

```bash
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

La commande `git rev-list` retourne le nombre de commits qui diffère entre la branche courante et la branche master de QMK. Nous lançons `git fetch` en premier afin d'être sûr que les refs qui représentent l'état courant du dépôt upstream soient à jour. Le résultat de la commande `git rev-list` retourne deux nombres:

```bash
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

Le premier nombre représente combien il y a eu de commits sur la branche courante depuis qu'elle a été créée, et le second nombre est combien de commits ont été faits sur la branche `upstream/master` depuis que la branche a été créée et, ainsi, les changements qui ne sont pas enregistrés sur la branche courante.

Maintenant que l'état actuel de la branche courante et la branche upstream sont connus, nous pouvons maintenant démarrer une opération de rebase:

```bash
git rebase upstream/master
```

Ceci dit à Git d'annuler les commits de la branche courrante puis de les réappliquer sur la branche master de QMK.

```bash
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

Ceci nous dit que nous avons un conflit de merge, et nous donne le nom du fichier en conflit. Ouvez le fichier conflictuel dans votre éditeur de texte et, quelque part dans le fichier, vous trouverez quelque chose comme ça:

```bash
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

La ligne `<<<<<<< HEAD` montre le début d'un conflit de merge et la ligne `>>>>>>> Commit #1` indique la fin, avec les sections conflictuelles séparées par `=======`. La partie du côté `HEAD` vient de la version du fichier provenant de la branche master de QMK, et la partie marquée avec le numéro du commit provient de la branche courrante.

Parce que Git suis *les changements des fichiers*, plutôt que les contenus des fichiers directement, si Git ne peut pas trouver le texte qu'il y avait dans le fichier avant que le commit soit fait, il ne saura pas comment modifier le fichier. Modifier le fichier à nouveau va résoudre le conflit. Faites votre changement, et sauvez le fichier.

```bash
<p>Need help? Email support@webhost.us.</p>
```

Maintenant, lancez:

```bash
git add conflicting_file_1.txt
git rebase --continue
```

Git enregistre le changement dans le fichier conflictuel, et continue à appliquer les commits depuis votre branche jusqu'à ce qu'il arrive à la fin.
