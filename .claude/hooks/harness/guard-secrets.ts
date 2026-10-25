import { exitWithFeedback, readHookInput } from "./hook-io.ts";
import { findSecret, writtenText } from "./secrets.ts";

const input = await readHookInput();
const secret = findSecret(writtenText(input.tool_input));
if (secret) {
  exitWithFeedback(
    `Bloqué par harness : le contenu contient un secret (${secret}). Lis-le depuis une variable d'environnement au lieu de l'écrire dans le code.`,
  );
}
