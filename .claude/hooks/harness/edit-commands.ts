import { extname, isAbsolute, relative } from "node:path";
import { isRecord } from "./hook-io.ts";
import { readHarnessConfig, runCommands } from "./project.ts";

export type OnEditCommand = { command: string; extensions?: string[] };

const COMMAND_TIMEOUT_MS = 60_000;
// Fichiers du harness : le formatage du projet les réécrirait, jusque dans le bloc géré d'AGENTS.md.
const HARNESS_FILES = ["AGENTS.md", "CLAUDE.md", "harness.config.json"];
const HARNESS_DIRS = [".claude/", "openspec/"];

export function readOnEditCommands(projectDir: string): OnEditCommand[] {
  const onEdit = readHarnessConfig(projectDir).onEdit;
  return Array.isArray(onEdit) ? onEdit.flatMap(toOnEditCommand) : [];
}

export function runOnEdit(file: string, projectDir: string, commands: OnEditCommand[]): string | undefined {
  const fromProject = relative(projectDir, file);
  if (fromProject.startsWith("..") || isAbsolute(fromProject)) return undefined;
  const path = fromProject.replaceAll("\\", "/");
  if (isHarnessFile(path)) return undefined;
  const quoted = quote(path);
  const applicable = commands.filter((command) => appliesTo(command, file));
  return runCommands(
    applicable.map(({ command }) => command.replaceAll("{file}", quoted)),
    projectDir,
    COMMAND_TIMEOUT_MS,
  );
}

function toOnEditCommand(entry: unknown): OnEditCommand[] {
  if (typeof entry === "string") return [{ command: entry }];
  if (!isRecord(entry) || typeof entry.command !== "string") return [];
  const extensions = Array.isArray(entry.extensions) ? entry.extensions.filter((ext) => typeof ext === "string") : undefined;
  return [extensions ? { command: entry.command, extensions } : { command: entry.command }];
}

const appliesTo = ({ extensions }: OnEditCommand, file: string) =>
  extensions === undefined || extensions.includes(extname(file).toLowerCase());

const isHarnessFile = (path: string) => HARNESS_FILES.includes(path) || HARNESS_DIRS.some((dir) => path.startsWith(dir));

const quote = (path: string) => `"${path.replace(/(["$`\\])/g, "\\$1")}"`;
