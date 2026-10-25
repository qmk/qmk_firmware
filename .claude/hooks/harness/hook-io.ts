export type HookInput = { cwd: string; agentId: string; tool_input: Record<string, unknown> };

export async function readHookInput(): Promise<HookInput> {
  const chunks: Buffer[] = [];
  for await (const chunk of process.stdin) chunks.push(chunk as Buffer);
  const raw: unknown = JSON.parse(Buffer.concat(chunks).toString("utf8"));
  const { cwd, tool_input, agent_id, session_id } = isRecord(raw) ? raw : {};
  return {
    cwd: typeof cwd === "string" ? cwd : process.cwd(),
    agentId: [agent_id, session_id].find((id): id is string => typeof id === "string") ?? "default",
    tool_input: isRecord(tool_input) ? tool_input : {},
  };
}

export const projectDirOf = (input: HookInput) => process.env.CLAUDE_PROJECT_DIR ?? input.cwd;

export function exitWithFeedback(message: string): never {
  process.stderr.write(`${message}\n`);
  process.exit(2);
}

export const isRecord = (value: unknown): value is Record<string, unknown> =>
  typeof value === "object" && value !== null && !Array.isArray(value);
