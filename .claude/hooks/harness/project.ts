import { spawnSync } from "node:child_process";
import { readFileSync } from "node:fs";
import { join } from "node:path";
import { isRecord } from "./hook-io.ts";

const CONFIG_FILE = "harness.config.json";
const OUTPUT_LIMIT = 2000;

export function readHarnessConfig(dir: string): Record<string, unknown> {
  try {
    const raw: unknown = JSON.parse(readFileSync(join(dir, CONFIG_FILE), "utf8"));
    return isRecord(raw) ? raw : {};
  } catch {
    return {};
  }
}

export function runCommands(commands: string[], cwd: string, totalTimeoutMs: number): string | undefined {
  const deadline = Date.now() + totalTimeoutMs;
  const failures = commands
    .map((command) => runCommand(command, cwd, Math.max(deadline - Date.now(), 1)))
    .filter((failure): failure is string => failure !== undefined);
  return failures.length === 0 ? undefined : failures.join("\n\n");
}

function runCommand(command: string, cwd: string, timeoutMs: number): string | undefined {
  const result = spawnSync(command, { cwd, shell: true, encoding: "utf8", timeout: timeoutMs });
  if (result.status === 0) return undefined;
  const output = `${result.stdout ?? ""}${result.stderr ?? ""}`.trim();
  return `$ ${command}\n${output.slice(-OUTPUT_LIMIT)}`;
}
