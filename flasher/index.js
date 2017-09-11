#!/usr/bin/env node

const Commander = require('commander');

const { Echo } = require('./util');
const { Upload } = require('./commands');

if (!process.cwd().endsWith('/qmk_firmware')) {
  process.chdir(`${__dirname}/../`)
  console.log(process.cwd());
}

Commander
  .option('-m --keymap [name]', 'Keymap name', 'default')
  .option('-p --path [path]', 'DFU device path')
  .option('--half [half]', 'Which half to program (left, right)')
  .parse(process.argv);

(async () => {
  Echo(`Keymap: ${Commander.keymap}`);

  if (Commander.half != null) {
    await Upload(Commander.keymap, Commander.path, Commander.half === 'right');
  } else {
    // Build both halves

    await Upload(Commander.keymap);
    await Upload(Commander.keymap, undefined, true);
  }
})();

process.on('unhandledRejection', err => {
  console.error(err);
  process.exit(1);
});
