const Inquirer = require('inquirer');

const { Echo, Exec, IdentifyKeyboard } = require('./util');

async function Upload (keymap, path, right = false) {
  await Build(keymap, path, right);

  // Find a keyboard to flash
  let board;
  while (board == null) {
    board = IdentifyKeyboard(undefined, path);
    if (board == null) {
      Echo(`Put your keyboard in flash mode`);
    }
  }
  if (board.length > 1) {
    const answer = await Inquirer.prompt({
      name: 'path',
      type: 'list',
      message: `Select a the keyboard's ${right ? 'right' : 'left'} half`,
      choices: board.map(board => ({
        name: `${board.name} (${board.path})`,
        value: board.path
      }))
    });
    board = board.find(board => board.path === answer.path);
  } else if (board.length === 1) {
    board = board[0];
  }

  Echo(`Building for ${board.name} (${board.path})`);
  await Flash(keymap, board, right);
}
module.exports.Upload = Upload;

async function Build (keymap, path, right = false) {
  Echo(`Building ${right ? 'right' : 'left'}`);
  await Exec(`make ergodox_infinity-${keymap} ${right ? 'MASTER=right' : ''}`);
  await Exec(`make ergodox_infinity-${keymap}-.build/ergodox_infinity_${keymap}.bin ${right ? 'MASTER=right' : ''}`);
  Echo(`Built ${right ? 'right' : 'left'}`, '');
}
module.exports.Build = Build;

async function Flash (keymap, board, right = false) {
  Echo(`Flashing ${right ? 'right' : 'left'}`);
  await Exec(`dfu-util --device ${board.id} --path ${board.path} -D .build/ergodox_infinity_${keymap}.bin`);
  Echo(`Flashed ${right ? 'right' : 'left'}`, '');
}
module.exports.Flash = Flash;
