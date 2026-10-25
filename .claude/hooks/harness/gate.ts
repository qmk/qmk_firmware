import { exitWithFeedback, readHookInput } from "./hook-io.ts";
import { runCommands } from "./project.ts";
import { attemptsFile, evaluateGate, readGateCommands, worktreeRoot } from "./stop-gate.ts";

// Budget total sous le délai du hook (600 s) : un hook tué laisserait passer l'arrêt en silence.
const GATE_TIMEOUT_MS = 540_000;

const input = await readHookInput();
const root = worktreeRoot(input.cwd);
const failures = runCommands(readGateCommands(root), root, GATE_TIMEOUT_MS);
const message = evaluateGate(failures, attemptsFile(input.agentId));
if (message) exitWithFeedback(message);
