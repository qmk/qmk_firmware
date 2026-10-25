import { basename } from "node:path";

export const LOCKFILES = [
  "package-lock.json",
  "pnpm-lock.yaml",
  "yarn.lock",
  "bun.lock",
  "bun.lockb",
  "Cargo.lock",
  "poetry.lock",
  "uv.lock",
  "Gemfile.lock",
  "composer.lock",
  "go.sum",
  "packages.lock.json",
];

const SHELL_WRITE_TARGET = /(?:>>?|\btee\s+(?:-a\s+)?)\s*(["']?)([^\s"';|&]+)\1/g;

export function isProtectedPath(path: string): boolean {
  const normalized = path.replaceAll("\\", "/");
  const name = basename(normalized);
  return (
    name === ".env" ||
    name.startsWith(".env.") ||
    LOCKFILES.includes(name) ||
    normalized.includes(".claude/hooks/harness/") ||
    normalized.endsWith(".claude/settings.json")
  );
}

export function findProtectedWrite(command: string): string | undefined {
  const targets = [...command.matchAll(SHELL_WRITE_TARGET)].map((match) => match[2] ?? "");
  return targets.find(isProtectedPath);
}
