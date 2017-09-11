const Inquirer = require('inquirer');

const { Echo, Exec, IdentifyKeyboard } = require('./util');

async function Upload (keymap, path, right = false) {
  await Build(keymap, path, right);

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
  await Flash(keymap, board.path, right);
}
module.exports.Upload = Upload;

async function Build (keymap, path, right = false) {
  Echo(`Building ${right ? 'right' : 'left'}`);
  await Exec(`make ergodox_infinity-${keymap} ${right ? 'MASTER=right' : ''}`);
  await Exec(`make ergodox_infinity-${keymap}-.build/ergodox_infinity_${keymap}.bin ${right ? 'MASTER=right' : ''}`);
  Echo(`Built ${right ? 'right' : 'left'}`, '');
}
module.exports.Build = Build;

function Flash (keymap, path, right = false) {
  return new Promise(async resolve => {
    Echo(`Flashing ${right ? 'right' : 'left'}`);
    // make infinity-<keymap>-.build/ergodox_infinity_<keymap>.bin
    // await Exec(`make ergodox_infinity-${keymap}-dfu-util ${right ? 'MASTER=right' : ''}`);
    await Exec(`dfu-util --path ${path} -D .build/ergodox_infinity_default.bin`);
    Echo(`Flashed ${right ? 'right' : 'left'}`, '');

    // while (IdentifyKeyboard(board.path)) {
    //   Echo(`Unplug your keyboard!`);
    // }
    // TODO: Check to see if the script is done. If it is, then don't require an unplug
    // TODO: Make this actually look for the keyboard to be unplugged
    // Echo(`Unplug your keyboard! (you have 15 seconds to do so)`);
    // setTimeout(() => resolve(), 15000);
    resolve();
  });
}
module.exports.Flash = Flash;
