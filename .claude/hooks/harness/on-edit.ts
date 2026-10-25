import { readOnEditCommands, runOnEdit } from "./edit-commands.ts";
import { exitWithFeedback, projectDirOf, readHookInput } from "./hook-io.ts";

const input = await readHookInput();
const projectDir = projectDirOf(input);
const file = String(input.tool_input.file_path ?? "");

const failures = file ? runOnEdit(file, projectDir, readOnEditCommands(projectDir)) : undefined;
if (failures) exitWithFeedback(`Formatage/lint en échec sur ${file}. Corrige ces problèmes :\n${failures}`);
