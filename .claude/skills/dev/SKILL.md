---
name: dev
description: Implémente un changement OpenSpec en TDD. Mode pair par défaut (arrêt après chaque rouge et chaque vert), mode autonome avec --auto (implémenteur, gate et reviewer, puis PR). À lancer par l'humain avec /dev.
argument-hint: <nom-du-changement> [--auto]
disable-model-invocation: true
---
<!-- généré par harness : ne pas éditer -->
# /dev : implémenter un changement OpenSpec

Arguments : $ARGUMENTS

Le premier argument est le nom du changement. Avec `--auto`, suis le **mode autonome**, sinon le **mode pair**.

Dès que le changement est connu, affiche : 💡 Nomme la session : `/rename dev-<nom>`, pour la retrouver dans `claude --resume`.

## Préparation (deux modes)

1. **Nom absent** : lance `npx -y @fission-ai/openspec@1.14.2 list --json`, propose le changement en cours et attends la confirmation.
2. **Branche** : `feat/<nom>` existe, créée par `/spec`. Place-toi dessus (`git switch feat/<nom>`).
3. **Plan non commité** : si `openspec/changes/<nom>/` contient des modifications non commitées, c'est le plan validé. Lance `git add openspec/changes/<nom>`, puis commite : `docs(<nom>): propose change`.
4. **Instructions** : lis `npx -y @fission-ai/openspec@1.14.2 instructions apply --change "<nom>" --json`, puis ses `contextFiles` (proposal, design, specs, tasks), son `context` et son `operationGuidance` (les règles d'implémentation du projet). Lis aussi les images de `mockups/` du dossier du changement, s'il y en a. Selon `state` :
   - `ready` : continue, sauf si `warnings` n'est pas vide : dans ce cas, arrête-toi et explique ;
   - `all_done` : toutes les tâches sont cochées, passe directement à la fin de ton mode ;
   - `blocked` : arrête-toi et cite `instruction`.
5. **Commandes** : les commandes du projet (install, test, typecheck) sont dans AGENTS.md. N'utilise que celles qui sont configurées.

## Mode pair

L'humain est ton gate. À chaque ⏸, tu t'arrêtes et tu attends son « ok » ou ses remarques avant de continuer.

Si `tasks.md` contient des groupes `[<repo>]`, le changement touche plusieurs repos : arrête-toi et propose `/dev <nom> --auto`, le seul mode qui les gère.

Prends la première case non cochée de `tasks.md`, une tâche à la fois.

### Tâche testable

1. **Rouge.**
   - Écris le test qui traduit le scénario WHEN/THEN de la tâche.
   - Lance **seulement ce test**. Il doit échouer parce que le comportement manque, pas à cause d'une faute de frappe ou d'un import.
   - ⏸ Montre le test et la sortie de l'échec.
2. **Vert.**
   - Écris le code minimal qui fait passer le test.
   - Relance le test ciblé, puis le typecheck et la suite complète.
   - Si un refactoring rend le code plus expressif, fais-le maintenant, en gardant les tests verts.
   - ⏸ Montre le diff et les sorties.
3. **Commit.**
   - Coche la case dans `tasks.md`.
   - Commite le code, le test et `tasks.md` ensemble : `feat(<nom>): <comportement du scénario>`, ou `fix(<nom>): …` pour une correction.

### Tâche `tdd: false`

1. Fais-la.
2. ⏸ Montre le diff.
3. Coche la case, puis commite : `chore(<nom>): …` ou `docs(<nom>): …`.

### Règles

- Une tâche par commit, jamais plus.
- Ne modifie jamais un test existant pour le faire passer sans le dire, et sans l'ok de l'humain.
- Spec ambiguë ou blocage : arrête-toi et pose la question. Ne réinvente pas la spec.
- Applique les principes de code d'AGENTS.md.

### Fin

1. Vérifie avec `npx -y @fission-ai/openspec@1.14.2 list --json` que `completedTasks` égale `totalTasks` pour `<nom>`. `archive -y` passerait outre des tâches incomplètes.
2. ⏸ Récapitule (tâches faites, tests ajoutés) et demande l'ok pour archiver.
3. Lance `npx -y @fission-ai/openspec@1.14.2 archive "<nom>" -y`, puis commite : `docs(<nom>): archive spec`.
4. ⏸ Demande l'ok pour livrer, puis suis **Livraison** avec une PR prête.

## Mode autonome

L'humain a validé le plan, il n'intervient plus avant la PR, sauf aux arrêts ⛔. Tu es l'**orchestrateur** : tu ne codes pas toi-même.

Règles de shell :
- Ton shell garde son dossier courant d'une commande à l'autre : utilise toujours des chemins absolus.
- N'utilise jamais `git -C` : fais `cd <dossier> && git …`.

Note dès le début :
- `<racine>` : la racine du projet (`git rev-parse --show-toplevel`) ;
- `<principale>` : la branche principale (`main` ou `master`) ;
- `<base locale>` : la branche `localOnly` de `harness.config.json` si elle est renseignée, sinon `<principale>` ;
- `<wt>` : `<racine>/.claude/worktrees/<nom>` ;
- pour chaque repo lié du plan (groupes de tâches `[<repo>]`) : `<chemin>`, le chemin tiré de `repos` dans `harness.config.json` et résolu depuis `<racine>` (chemin absolu), `<principale du repo>` (trouvée comme `<principale>`), `<base du repo>` : la branche `localOnly` de son `harness.config.json` si elle est renseignée, sinon `origin/<principale du repo>`, et `<wt-repo>` = `<chemin>/.claude/worktrees/<nom>`.

0. **Contrôles** ⛔ : si l'un échoue, arrête-toi et explique. Ne passe jamais outre.
   - `git status --porcelain` n'est pas vide : l'arbre de travail n'est pas propre.
   - `git ls-remote --exit-code --heads origin <principale>` échoue : la branche principale n'est pas sur GitHub, la PR n'aurait pas de base. Ne pousse jamais la branche principale toi-même.
   - Un repo touché est archivé : `cd <racine> && gh repo view --json isArchived`, et de même dans chaque `<chemin>`. GitHub refuserait le push.
   - Un groupe `[<repo>]` de `tasks.md` vise un repo absent de `repos`, ou ce repo n'a pas de `harness.config.json` : sans harness, il n'aurait ni gate ni garde-fous.
1. **Worktrees.**
   - `git switch <base locale>`, puis `git worktree add <wt> feat/<nom>`.
   - Pour chaque repo lié : `cd <chemin> && git fetch origin`, puis `cd <chemin> && git worktree add <wt-repo> -b feat/<nom> <base du repo>`.
   - ⛔ Vérifie que `<wt-repo>/harness.config.json` existe : si le harness du repo lié n'est pas encore sur sa branche principale distante, le worktree n'en a pas, et le gate laisserait tout passer. Arrête-toi et demande.
   - Dans chaque worktree, lance la commande `install` de son `harness.config.json` si elle est configurée.
2. **Implémentation.** Un sous-agent `code-implementer` par repo, l'un après l'autre : les repos liés d'abord, car le projet dépend souvent d'eux.
   - Pour un repo lié, donne-lui le nom du changement, `<wt-repo>`, la liste de ses tâches `[<repo>]` et le chemin absolu du dossier du changement, `<wt>/openspec/changes/<nom>/` : il y lit la proposition, le design et les scénarios.
   - Pour le projet, donne-lui le nom du changement et `<wt>`.
   - Note chaque identifiant.
   - Quand l'implémenteur d'un repo lié a fini, coche dans `<wt>/openspec/changes/<nom>/tasks.md` les tâches que son rapport liste comme faites, et elles seulement. Puis commite dans `<wt>` : `chore(<nom>): check <repo> tasks`.
3. **Vérification**, dans chaque worktree. `<base>` vaut `<base locale>` pour le projet, et `<base du repo>` pour un repo lié.
   - Typecheck et suite complète. S'ils sont rouges, le gate est épuisé : passe à **Livraison** avec des brouillons `needs-human`, en citant les échecs.
   - Lint, avec le `harness.config.json` du worktree (pas celui du projet pour un repo lié) :
     1. Si `lintFiles` n'y est pas configuré, passe.
     2. Liste les fichiers modifiés : `cd <worktree> && git diff --name-only --diff-filter=ACMR <base>...HEAD`.
     3. Garde les fichiers de code : les extensions de l'entrée d'`onEdit` qui commence par les deux mêmes mots que `lintFiles` (`npx eslint`, `dotnet format`), ou à défaut `.js .jsx .mjs .cjs .ts .tsx`.
     4. Si la liste est vide, passe : sans fichier, l'outil linterait tout le projet.
     5. Sinon, lance `lintFiles` en remplaçant `{files}` par ces fichiers, chacun entre guillemets. Écris la sortie dans `<racine>/.claude/worktrees/<nom>-<repo ou projet>.lint.txt`.
4. **Review, 3 tours au plus.** À chaque tour :
   1. Pour chaque worktree : `cd <worktree> && git diff <base>...HEAD > <racine>/.claude/worktrees/<nom>-<repo ou projet>.diff`.
   2. Lance un **nouveau** sous-agent `code-reviewer`. Donne-lui :
      - le nom du changement ;
      - les worktrees ;
      - les diffs ;
      - les sorties de lint ;
      - les points bloquants du tour précédent.
   3. Lis la dernière ligne de sa réponse :
      - `VERDICT: APPROVE` : passe à l'étape 5 ;
      - `VERDICT: REQUEST_CHANGES` : reprends le ou les implémenteurs concernés (SendMessage vers leur identifiant) avec leurs points bloquants, puis refais l'étape 3 et un nouveau tour ;
      - verdict illisible : traite-le comme `VERDICT: REQUEST_CHANGES`.

   Au 3e tour, `VERDICT: REQUEST_CHANGES` mène directement à **Livraison** en brouillons `needs-human`, en citant les points restants : pas de correction sans review.
5. **Archivage.**
   - Vérifie que toutes les tâches sont cochées (`cd <wt> && npx -y @fission-ai/openspec@1.14.2 list --json`). S'il reste des tâches non cochées, passe à **Livraison** en brouillons `needs-human`, en les listant.
   - Lance `cd <wt> && npx -y @fission-ai/openspec@1.14.2 archive "<nom>" -y`.
   - Commite : `docs(<nom>): archive spec`.
6. **Livraison**, avec des PR prêtes.

## Livraison

En mode autonome, une PR par repo. Lance chaque commande depuis le worktree concerné, et donne un chemin absolu à chaque fichier.

1. **Brouillon seulement** : si un worktree contient du travail non commité, commite-le (`chore(<nom>): work in progress`) pour que la PR le montre.
2. **Push** : sans `localOnly` dans le `harness.config.json` du dossier, `git push -u origin feat/<nom>`. Avec `localOnly` : `harness publish feat/<nom>` (il rejoue tes commits sans les fichiers du harness ni d'OpenSpec), puis `git push origin harness-publish/feat/<nom>:feat/<nom>`, puis `git fetch origin feat/<nom>` et `git merge -s ours --no-edit origin/feat/<nom>` : la branche de travail enregistre la version publiée sans changer ses fichiers. Si `publish` échoue, montre son erreur et arrête-toi. Si le push est refusé (repo archivé, droits, permission) ⛔ :
   - ne contourne pas ;
   - donne à l'humain la commande de push exacte, puis, pour la suite, la commande `gh pr create` complète avec le chemin de la description ;
   - attends qu'il réponde « poussé », puis reprends à l'étape suivante.
3. **Ordre** : avec des repos liés, crée d'abord leurs PR. Crée ensuite celle du projet, qui cite leurs liens. Enfin, ajoute le lien de la PR du projet à chaque PR liée, dans sa note de livraison et sa liste de liens, avec `gh pr edit <numéro> --body-file <fichier>`.
4. **Description de la PR** : une par repo, dans `<racine>/.claude/worktrees/<nom>-<repo>-pr.md` (`<repo>` vaut `projet` pour le projet), en suivant `.github/pull_request_template.md`. Elle reprend :
   - le résumé de la proposition ;
   - la source ClickUp ;
   - les scénarios ;
   - les tâches et les tests ajoutés ;
   - en mode autonome : le verdict du reviewer, le nombre de tours et les points mineurs ;
   - les liens vers les PR des repos liés ;
   - la note de livraison.

   **Note de livraison** : une section `## Livraison` dans chaque description, même si le modèle de PR n'en a pas : place-la après « Tâches et tests », sinon à la fin. Elle dit comment mettre le changement en production, d'après le diff et `design.md`, en cinq lignes au plus :
   - **Ordre** : les PR à livrer, dans l'ordre, avec leurs liens, et « (cette PR) » sur la sienne ; pour une PR seule, « cette PR seule ». C'est l'ordre des déploiements, sans parler de merge : une PR validée est mergée d'office ;
   - **Migrations** : celles du diff, et comment elles s'appliquent (au déploiement, ou à la main) ;
   - **Scripts manuels** : chaque script à jouer à la main (données SQL, par exemple), avec ses paramètres à remplacer, jamais leurs valeurs ;
   - **Vérification** : ce qu'on contrôle juste après la livraison ;
   - **Retour arrière** : comment revenir à la version précédente, et si la base le permet.

   Omets une ligne qui ne s'applique pas. Sans migration, sans script et sans ordre entre repos, la note tient en une ligne : « Aucune étape particulière ». L'environnement de production est celui que nomment les règles du projet d'AGENTS.md. La note suit les règles de langue d'AGENTS.md, comme le reste de la description. Avec `localOnly`, elle ne parle ni du harness ni d'OpenSpec.

   Avec `localOnly`, la description ne parle pas du harness : résumé, source ClickUp, changements, tests ajoutés, comment tester (les scénarios), note de livraison. Pas de verdict, pas de tours, pas de label `needs-human` : un brouillon dit seulement ce qui bloque.

   Pour un repo lié, la description est courte : ses tâches, ses tests, la note de livraison et le lien vers la PR du projet.
5. **Titre** : au format Conventional Commits, car il deviendra le commit sur la branche principale : `feat(<nom>): <résumé>`, ou `fix(<nom>): …`.
6. **PR** :
   - **prête** : `gh pr create --head feat/<nom> --base <principale> --title "<titre>" --body-file <racine>/.claude/worktrees/<nom>-<repo>-pr.md`. Pour un repo lié, `--base` vaut `<principale du repo>` ;
   - **brouillon** : ajoute `--draft --label needs-human` (sans le label avec `localOnly`). Crée le label au besoin avec `gh label create needs-human --force`. La description explique ce qui bloque.
7. **ClickUp** : seulement si `proposal.md` cite une tâche ClickUp, avec les outils MCP ClickUp.
   - **PR prête** : passe la tâche au statut `clickup.statuses.review` de `harness.config.json`, puis commente avec les liens des PR.
   - **Brouillon** : ne change pas le statut. Commente avec les liens et ce qui bloque.
   - **MCP ClickUp indisponible** : dis-le dans ton rapport.
8. **Nettoyage**, en mode autonome, que les PR soient prêtes ou en brouillon :
   - Pour chaque worktree : `cd <dossier du repo>`, puis `git worktree remove <worktree>`. Si git refuse parce que le worktree n'est pas propre, n'utilise jamais `--force` : garde-le et signale-le.
   - Supprime ces fichiers, et seulement eux : `<racine>/.claude/worktrees/<nom>-<repo>.diff`, `<nom>-<repo>.lint.txt` et `<nom>-<repo>-pr.md`, pour chaque repo (`projet` compris). Ne supprime jamais un dossier de worktree gardé.
9. **Fin** : donne les liens des PR, et la suite : recette locale avec `/qa-local <nom>`. En mode autonome, si le gate a été épuisé ou si la review a pris au moins 2 tours, 💡 Un échec à retenir ? `/lecon`
