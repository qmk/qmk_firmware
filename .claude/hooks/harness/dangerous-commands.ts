import { basename, isAbsolute, relative, resolve } from "node:path";

type Check = (words: string[], projectDir: string) => string | undefined;

const SEPARATORS = /&&|\|\||[;|&()`\n]/;
const COMMAND_PREFIXES = new Set(["sudo", "command", "env", "time", "nohup"]);
const GIT_OPTIONS_WITH_VALUE = new Set(["-C", "-c"]);
const PROTECTED_BRANCHES = ["main", "master"];
const DISCARD_ALL_PATHSPECS = [".", ":/"];
const BROAD_RM_TARGETS = new Set(["/", "/*", "~", "~/", "~/*", ".", "./", "./*", "*", "..", "../"]);

export function findDangerousCommand(command: string, projectDir: string): string | undefined {
  for (const segment of command.split(SEPARATORS)) {
    const words = commandWords(segment);
    for (const check of CHECKS) {
      const reason = check(words, projectDir);
      if (reason) return reason;
    }
  }
  return undefined;
}

function commandWords(segment: string): string[] {
  const words = segment.trim().split(/\s+/).filter(Boolean).map(unquote);
  const start = words.findIndex((word) => !COMMAND_PREFIXES.has(word) && !/^\w+=/.test(word));
  if (start === -1) return [];
  const [program = "", ...args] = words.slice(start);
  return [basename(program), ...args];
}

const unquote = (word: string) => word.replace(/^["']|["']$/g, "");

function gitArgs(words: string[], subcommand: string): string[] | undefined {
  if (words[0] !== "git") return undefined;
  let index = 1;
  while (GIT_OPTIONS_WITH_VALUE.has(words[index] ?? "") || /^--(git-dir|work-tree)=/.test(words[index] ?? "")) {
    index += GIT_OPTIONS_WITH_VALUE.has(words[index] ?? "") ? 2 : 1;
  }
  return words[index] === subcommand ? words.slice(index + 1) : undefined;
}
const positionals = (args: string[]) => args.filter((arg) => !arg.startsWith("-"));
const hasShortFlag = (args: string[], letter: string) =>
  args.some((arg) => /^-[a-zA-Z]+$/.test(arg) && arg.includes(letter));

const forcePush: Check = (words) => {
  const args = gitArgs(words, "push");
  if (!args) return undefined;
  const forced =
    hasShortFlag(args, "f") ||
    args.some((arg) => arg.startsWith("--force")) ||
    positionals(args).some((arg) => arg.startsWith("+"));
  return forced
    ? "Push forcé interdit : il réécrit l'historique partagé. Pousse normalement ; en cas de conflit, rebase ou merge en local."
    : undefined;
};

const pushToProtectedBranch: Check = (words) => {
  const args = gitArgs(words, "push");
  if (!args) return undefined;
  const targets = positionals(args).slice(1).map(targetBranch);
  return targets.some((branch) => PROTECTED_BRANCHES.includes(branch))
    ? "Push direct vers main/master interdit : pousse ta branche de travail et ouvre une PR."
    : undefined;
};

const targetBranch = (refspec: string) =>
  (refspec.split(":").pop() ?? "").replace(/^\+/, "").replace(/^refs\/heads\//, "");

const hardReset: Check = (words) =>
  gitArgs(words, "reset")?.includes("--hard")
    ? "git reset --hard interdit : il détruit le travail non commité. Utilise git stash ou un commit de sauvegarde."
    : undefined;

const forceClean: Check = (words) => {
  const args = gitArgs(words, "clean");
  return args && (hasShortFlag(args, "f") || args.includes("--force"))
    ? "git clean forcé interdit : il supprime des fichiers non suivis. Supprime des chemins précis."
    : undefined;
};

const discardWorktree: Check = (words) => {
  const checkout = gitArgs(words, "checkout");
  const restore = gitArgs(words, "restore");
  const targetsAll = (args: string[]) => DISCARD_ALL_PATHSPECS.some((pathspec) => args.includes(pathspec));
  const discards =
    (checkout && (targetsAll(checkout) || hasShortFlag(checkout, "f") || checkout.includes("--force"))) ||
    (restore && targetsAll(restore) && (!restore.includes("--staged") || restore.includes("--worktree")));
  return discards
    ? "Abandon de tout le travail non commité interdit. Restaure des fichiers précis, ou fais un commit de sauvegarde."
    : undefined;
};

const noVerify: Check = (words) =>
  words.includes("--no-verify") || hasShortFlag(gitArgs(words, "commit") ?? [], "n")
    ?"--no-verify interdit : les hooks git font partie des garde-fous. Corrige ce qu'ils signalent."
    : undefined;

const recursiveForceRemove: Check = (words, projectDir) => {
  if (words[0] !== "rm") return undefined;
  const args = words.slice(1);
  const recursive = hasShortFlag(args, "r") || hasShortFlag(args, "R") || args.includes("--recursive");
  const force = hasShortFlag(args, "f") || args.includes("--force");
  if (!recursive || !force) return undefined;
  const target = positionals(args).find((path) => isDangerousTarget(path, projectDir));
  return target === undefined
    ? undefined
    : `rm -rf sur "${target}" interdit : cible trop large ou hors du projet. Supprime des chemins précis dans le projet.`;
};

function isDangerousTarget(target: string, projectDir: string): boolean {
  if (BROAD_RM_TARGETS.has(target) || target.startsWith("~") || target.startsWith("$")) return true;
  const fromProject = relative(projectDir, resolve(projectDir, target));
  return (
    fromProject === "" ||
    fromProject.startsWith("..") ||
    isAbsolute(fromProject) ||
    fromProject === ".git" ||
    fromProject.startsWith(".git/")
  );
}

const CHECKS: Check[] = [
  forcePush,
  pushToProtectedBranch,
  hardReset,
  forceClean,
  discardWorktree,
  noVerify,
  recursiveForceRemove,
];
