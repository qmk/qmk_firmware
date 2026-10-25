import { spawnSync } from "node:child_process";
import { mkdirSync, readFileSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { dirname, join } from "node:path";
import { isRecord } from "./hook-io.ts";
import { readHarnessConfig } from "./project.ts";

export const MAX_ATTEMPTS = 3;
const GATE_COMMANDS = ["typecheck", "test"];

export function readGateCommands(dir: string): string[] {
  const commands = readHarnessConfig(dir).commands;
  if (!isRecord(commands)) return [];
  return GATE_COMMANDS.map((name) => commands[name]).filter(
    (command): command is string => typeof command === "string" && command !== "",
  );
}

export function worktreeRoot(cwd: string): string {
  const result = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd, encoding: "utf8" });
  return result.status === 0 ? result.stdout.trim() : cwd;
}

export const attemptsFile = (agentId: string) =>
  join(tmpdir(), "harness-gate", `${agentId.replace(/[^\w-]/g, "_")}.count`);

// Après MAX_ATTEMPTS refus, on laisse l'agent s'arrêter : l'orchestrateur constate le rouge et passe la main à l'humain.
export function evaluateGate(failures: string | undefined, stateFile: string): string | undefined {
  if (failures === undefined) {
    rmSync(stateFile, { force: true });
    return undefined;
  }
  const attempt = readAttempts(stateFile) + 1;
  if (attempt > MAX_ATTEMPTS) {
    rmSync(stateFile, { force: true });
    return undefined;
  }
  mkdirSync(dirname(stateFile), { recursive: true });
  writeFileSync(stateFile, String(attempt));
  return `Gate harness (tentative ${attempt}/${MAX_ATTEMPTS}) : typecheck ou tests en échec. Corrige avant de t'arrêter.\n${failures}`;
}

function readAttempts(stateFile: string): number {
  try {
    return Number(readFileSync(stateFile, "utf8")) || 0;
  } catch {
    return 0;
  }
}
