import { findDangerousCommand } from "./dangerous-commands.ts";
import { exitWithFeedback, projectDirOf, readHookInput } from "./hook-io.ts";
import { findProtectedWrite } from "./protected-files.ts";

const input = await readHookInput();
const command = String(input.tool_input.command ?? "");

const reason = findDangerousCommand(command, projectDirOf(input));
if (reason) exitWithFeedback(`Bloqué par harness : ${reason}`);

const protectedFile = findProtectedWrite(command);
if (protectedFile) {
  exitWithFeedback(
    `Bloqué par harness : écriture dans "${protectedFile}" interdite (secrets, lockfile ou garde-fou du harness). Demande à l'humain de le faire.`,
  );
}
