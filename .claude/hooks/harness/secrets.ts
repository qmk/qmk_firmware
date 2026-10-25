const SECRET_PATTERNS: ReadonlyArray<{ name: string; pattern: RegExp }> = [
  { name: "clé privée", pattern: /-----BEGIN [A-Z ]*PRIVATE KEY-----/ },
  { name: "clé d'accès AWS", pattern: /\b(?:AKIA|ASIA)[0-9A-Z]{16}\b/ },
  { name: "token GitHub", pattern: /\b(?:gh[pousr]_[A-Za-z0-9]{36,}|github_pat_[A-Za-z0-9_]{22,})/ },
  { name: "clé API Anthropic", pattern: /\bsk-ant-[A-Za-z0-9_-]{20,}/ },
  { name: "clé API OpenAI", pattern: /\bsk-(?:proj-)?(?=[A-Za-z0-9_-]*\d)[A-Za-z0-9_-]{20,}/ },
  { name: "token Slack", pattern: /\bxox[baprs]-[A-Za-z0-9-]{10,}/ },
  { name: "clé Stripe live", pattern: /\b[rs]k_live_[A-Za-z0-9]{20,}/ },
  { name: "clé API Google", pattern: /\bAIza[0-9A-Za-z_-]{35}/ },
];

export function findSecret(text: string): string | undefined {
  return SECRET_PATTERNS.find(({ pattern }) => pattern.test(text))?.name;
}

export function writtenText(toolInput: Record<string, unknown>): string {
  const edits = Array.isArray(toolInput.edits) ? toolInput.edits : [];
  const parts = [
    toolInput.content,
    toolInput.new_string,
    toolInput.new_source,
    ...edits.map((edit: unknown) => (typeof edit === "object" && edit !== null ? (edit as Record<string, unknown>).new_string : undefined)),
  ];
  return parts.filter((part): part is string => typeof part === "string").join("\n");
}
