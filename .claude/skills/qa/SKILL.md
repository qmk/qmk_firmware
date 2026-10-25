---
name: qa
description: Recette d'un changement sur un environnement déployé (dev, puis d'autres). Déploie le changement (commentaire `/deploy`) une fois les checks verts, attend des pods sains et revient en arrière en cas d'échec, pilote le navigateur en headless avec Playwright CLI, exécute et capture les scénarios WHEN/THEN, fait confirmer le verdict et écrit le rapport. À lancer par l'humain avec /qa.
argument-hint: <env> <branche | url de PR>
disable-model-invocation: true
---
<!-- généré par harness : ne pas éditer -->
# /qa : recette d'un changement sur un environnement déployé

Arguments : $ARGUMENTS (`<env>` puis la branche du changement, `feat/<nom>` ou `<nom>`, ou l'URL d'une PR). `<nom>` = la branche sans `feat/` : c'est le nom du changement OpenSpec, le même pour les PR liées de tous les repos. Avec une URL de PR, d'un repo du projet ou d'un repo lié, la tienne ou celle d'un collègue : lis la branche avec `gh pr view <url> --json headRefName`. Si la branche ne commence pas par `feat/`, arrête-toi : `/qa` recette un changement OpenSpec. Sans branche : `npx -y @fission-ai/openspec@1.14.2 list --json`, propose le changement et attends la confirmation. Sans `<env>` : donne la liste des environnements de `remote.envs` et arrête-toi.

Dès que les deux sont connus, affiche : 💡 Nomme la session : `/rename qa-<env>-<nom>`, pour la retrouver dans `claude --resume`.

Tu lances toi-même `deploy`, et `revert` dans les cas prévus ci-dessous. Tu ne publies rien et ne joues aucun script : l'humain le fait. Chaque commande pour l'humain suit la règle 👺 d'AGENTS.md. Utilise toujours des chemins absolus.

Note :
- `<racine>`, la racine du projet ; pour chaque repo touché (groupes `[<repo>]` de `tasks.md`) : `<chemin>`, tiré de `repos` et résolu depuis `<racine>`. Le projet est un repo touché seulement si sa PR pour `feat/<nom>` existe et que `gh pr diff <url> --name-only` liste autre chose que `openspec/` : sinon, il n'est ni contrôlé ni déployé ;
- `<url>` et `<session>` : les valeurs de `"url"` et `"session"` de `remote.envs.<env>` ; `<browser>` : celle de `"browser"`, facultative, ajoutée à chaque `open` (par exemple `--browser chromium --profile /Users/<toi>/.playwright-profiles/crisys-dev`). Le profil doit être un chemin absolu : un chemin relatif dépend du dossier courant, et la session de l'agent ne verrait pas la connexion de l'humain ;
- le dossier du changement : `openspec/changes/<nom>/`, ou `openspec/changes/archive/<date>-<nom>/` s'il est archivé. S'il n'est pas dans ta copie de travail (`localOnly`, ou la PR d'un collègue), lis ses fichiers sur `<ref>` avec `git -C <racine> show <ref>:<chemin du fichier>`, sans créer de worktree. `<ref>` = `feat/<nom>` si cette branche locale existe ; sinon lance `git -C <racine> fetch origin feat/<nom>`, et `<ref>` = `origin/feat/<nom>` ;
- `<rapports>` = `<racine>/.claude/qa-reports/` (ignoré par git).

## 0. Contrôles ⛔

Si l'un échoue, arrête-toi et explique.

1. **Config** : `remote.envs.<env>` existe. `"url"` et `"session"` se lisent dans le `harness.config.json` du projet ; `"deploy"`, `"revert"` et `"current"` dans celui de chaque repo touché (`<racine ou chemin>/harness.config.json`, comme `localOnly`), car chaque repo a son propre overlay. Un repo touché sans `remote.envs.<env>` : nomme-le. Sinon, montre cet exemple et arrête-toi :
   ```json
   "remote": { "envs": { "dev": {
     "url": "https://dev.crisys-road.net",
     "deploy": "gh pr comment {pr} --body \"/deploy dev\"",
     "revert": "gh pr comment {pr} --body \"/deploy dev revert\"",
     "current": "git log -1 --format=%s origin/main -- deploy/overlays/test/patch-helmrelease.yaml",
     "session": "crisys-dev",
     "version": "kubectl get deploy {service} -n crisys-test -o jsonpath='{.spec.template.spec.containers[0].image}'",
     "ready": "kubectl rollout status deploy/{service} -n crisys-test --timeout=9m"
   } } }
   ```
   `{pr}` : l'URL de la PR du repo. Un repo lié n'a besoin que de `deploy`, `revert` et `current`. Chaque repo peut ajouter `"version"` et `"ready"`, facultatives : `version` affiche l'image ou le tag que sert réellement `<env>`, `ready` attend que les pods du service soient prêts et échoue sinon. `{service}` est remplacé par chaque service cité dans la réponse du bot. Le namespace est écrit dans les commandes de chaque environnement, après le verbe `kubectl` (seuls `kubectl get deploy`, `kubectl get pods` et `kubectl rollout status` sont autorisés).
2. **PR** : pour chaque repo touché (le projet compris s'il l'est, voir la Note), `cd <racine ou chemin> && gh pr view feat/<nom> --json url,state,body` renvoie une PR ouverte. Garde son URL et sa description.
3. **Ordre** : la section `## Livraison` des descriptions donne l'ordre des déploiements. Sans note, l'ordre est : les repos liés, puis le projet.
4. **Outil** : `playwright-cli --version` répond. Sinon, donne la commande d'installation `npm install -g @playwright/cli@0.1.22`.

## 1. Occupation de l'environnement

Dans chaque repo touché, `git fetch origin`, puis lance `current`. Montre ce qui tourne sur `<env>` (la PR ou le tag de la principale) et préviens que le déploiement le remplacera. ⏸ Attends l'accord de l'humain : il vaut pour lancer les déploiements de tous les repos touchés.

## 2. Déploiement

Lance les attentes longues (`gh pr checks --watch`, `ready`) avec `run_in_background`, et attends leur fin : un appel coupé par le délai de l'outil n'est pas un échec, relance-le.

Avant le premier `deploy`, attends les checks de toutes les PR : `gh pr checks <url> --watch` pour chacune. Le bot refuse `/deploy` tant qu'un check n'est pas vert. Un check en échec : cite-le et arrête-toi, rien n'est déployé.

Puis, repo par repo, dans l'ordre de la note de livraison :
1. Lance toi-même la commande `deploy` du repo, `{pr}` remplacé.
2. Lis `gh pr view <url> --json comments` toutes les 30 secondes, 20 minutes au plus, jusqu'à la réponse du bot postée après la commande. Un refus du bot (checks en cours ou en échec, image absente, accès) : cite sa raison, c'est un échec. Sans réponse du bot après 20 minutes, fais comme pour un refus. Un bot qui ne cite aucun service : même chose.
3. Note chaque service cité par le bot et son tag (par exemple « **anomaly-service** `sha-…` is being deployed »). Un repo est déployé quand le bot a répondu qu'il le déploie.
4. Pour chaque service, `{service}` remplacé : relance `version` jusqu'à ce qu'elle affiche le tag noté, 15 minutes au plus, puis lance `ready`. N'utilise pas `kubectl get pods | grep` : un pod de l'ancienne version est lui aussi `Running` tant que Flux ne l'a pas remplacé. Sans `version` ni `ready`, ⏸ fais confirmer par l'humain que la nouvelle version est en ligne.

**Échec** (refus ou silence du bot, `version` ou `ready`) : lance toi-même `revert` pour chaque repo déployé par cette recette, jamais pour un autre : `<env>` ne reste pas dans un état mixte. Avant chaque `revert` d'échec, relance `current` : si `<env>` ne sert plus ta version (un collègue a déployé entre-temps), ne reverte pas ce repo, signale-le. En cas de silence, ne reverte pas le repo dont le bot n'a pas répondu : son `/deploy` est peut-être encore en file ; dis à l'humain de vérifier. Puis explique à l'humain : l'étape, la commande, sa sortie, et pour `ready` la sortie de `kubectl get pods -n <namespace>` (le namespace de `ready`). Arrête la recette.

## 3. Scripts manuels

Pour chaque script de la ligne « Scripts manuels » de la note de livraison : donne son chemin et ses paramètres à remplacer, demande leurs valeurs pour `<env>`, puis donne la commande ou les étapes pour le jouer, et ⏸ attends que l'humain l'ait joué. Ne joue jamais un script toi-même. Rappelle que les migrations et les scripts joués restent dans la base de `<env>`, même après `revert`.

## 4. Navigateur

1. Ouvre la session en headless : `playwright-cli -s=<session> open <url> <browser> --persistent`.
2. Si la page affichée est une page de connexion (`login.microsoftonline.com`, ou tout formulaire d'identifiants), ⏸ donne à l'humain `playwright-cli -s=<session> close` puis `playwright-cli -s=<session> open <url> --headed <browser> --persistent`, attends qu'il se soit connecté et ait fermé la fenêtre, puis rouvre en headless. Ne saisis jamais d'identifiants.
3. Même règle si la connexion expire pendant la recette.

## 5. Recette

1. Liste les scénarios, numérotés : chaque `#### Scenario` des specs delta du dossier du changement, avec ses WHEN/THEN. Ajoute un scénario par image de `mockups/` (même dossier) : « Mise en page conforme à `<image>` ». Si le dossier est lu sur `<ref>`, trouve les chemins avec `git -C <racine> ls-tree -r --name-only <ref> -- openspec/changes/`, et extrais chaque image pour pouvoir la lire : `git -C <racine> show <ref>:<chemin de l'image> > <rapports>/<nom>-<env>/maquette-<image>`.
2. Pour chaque scénario :
   - exécute-le avec `playwright-cli -s=<session>` : `snapshot` pour obtenir les références, puis `click`, `fill`, `select`, `goto`… ;
   - capture `playwright-cli -s=<session> screenshot --filename=<rapports>/<nom>-<env>/<n>.png` ;
   - propose OK ou KO, avec une phrase de preuve (ce que montre la page). Pour une maquette, lis l'image et la capture, et compare-les ;
   - un scénario que le navigateur ne peut pas vérifier (un appel d'API seul, un autre rôle, une donnée absente de `<env>`) : propose-le « à vérifier par l'humain », avec ce qu'il doit regarder.
3. Fais confirmer ou corriger ton verdict avec `AskUserQuestion` et `multiSelect: true` : 4 scénarios par question, 4 questions par appel, autant d'appels que nécessaire. Chaque option est un scénario (`<n>. <titre court>`) ; le texte de la question rappelle ceux que tu proposes OK. L'humain coche les scénarios **OK** ; un scénario non coché est KO. Un dernier groupe d'un seul scénario devient une question à deux options, « OK » et « KO ».
4. En un seul message, demande un commentaire pour chaque KO.

## 6. Rapport

Relance `current` dans chaque repo déployé. Si `<env>` ne sert plus ta version (un autre déploiement est passé pendant la recette), dis-le dans le rapport : les scénarios exécutés après ce moment ne valent rien, et ne propose pas `revert` pour ce repo, il écraserait le déploiement d'un autre.

1. Écris `<rapports>/<nom>-<env>.md`, soit `.claude/qa-reports/<nom>-<env>.md` (il remplace le précédent), dans la langue des règles du projet d'AGENTS.md : environnement, date, tag ou SHA déployé de chaque repo, scripts joués, tableau des scénarios (OK ou KO, commentaire, chemin de la capture).
2. Affiche-le, puis donne, pour chaque PR, `gh pr comment <url> --body-file <chemin absolu du rapport>`. Ne publie jamais le rapport toi-même. `gh` ne joint pas d'images : dis à l'humain où sont les captures, pour les glisser à la main dans la PR s'il le souhaite.

## 7. Fin

1. `playwright-cli -s=<session> close` : le profil persistant est gardé pour la prochaine recette.
2. Propose `revert` pour chaque repo déployé qui sert encore ta version (vérifié à l'étape 6) : sur un oui explicite, lance-le toi-même. Rappelle ce qui reste dans la base de `<env>`.
3. Tout OK : la recette est validée sur `<env>`. Un KO ou plus : résume-les et propose `/fix <nom>`, puis une nouvelle recette avec `/qa <env> feat/<nom>`.
