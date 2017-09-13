const Inquirer = require('inquirer');
const Chalk = require('chalk');

const { Echo, Exec, IdentifyKeyboard, Sleep } = require('./util');

async function Upload (keyboard, keymap, path, right = false) {
  await Build(keyboard, keymap, path, right);

  // Find a keyboard to flash
  let board;
  process.stdout.write(Chalk.yellow`Put your keyboard in flash mode`);
  while (board == null) {
    board = IdentifyKeyboard(undefined, path);
    if (board == null) {
      process.stdout.write(Chalk.yellow`.`);
      await Sleep(1000);
    }
  }
  console.log('\n\n');

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

  Echo(Chalk.blue(`Building for ${board.name} (${board.path})`));
  await Flash(keyboard, keymap, board, right);
}
module.exports.Upload = Upload;

async function Build (keyboard, keymap, path, right = false) {
  Echo(Chalk.blue(`Building ${right ? 'right' : 'left'}`));
  await Exec(`make ${keyboard}-${keymap} ${right ? 'MASTER=right' : ''}`);
  await Exec(`make ${keyboard}-${keymap}-.build/${keyboard}_${keymap}.bin ${right ? 'MASTER=right' : ''}`);
  Echo(Chalk.green(`Built ${right ? 'right' : 'left'}`), '');
}
module.exports.Build = Build;

async function Flash (keyboard, keymap, board, right = false) {
  Echo(Chalk.blue(`Flashing ${right ? 'right' : 'left'}`));
  await Exec(`dfu-util --device ${board.id} --path ${board.path} -D .build/${keyboard}_${keymap}.bin`);
  Echo(Chalk.green(`Flashed ${right ? 'right' : 'left'}`), '');
}
module.exports.Flash = Flash;
