#!/usr/bin/env node

const Commander = require('commander');

const { Echo } = require('./util');
const { Upload } = require('./commands');

if (!process.cwd().endsWith('/qmk_firmware')) {
  process.chdir(`${__dirname}/../`)
  console.log(process.cwd());
}

Commander
  .option('-k --keyboard [name]', 'Keyboard name', 'ergodox_infinity')
  .option('-m --keymap [name]', 'Keymap name', 'default')
  .option('-p --path [path]', 'DFU device path')
  .option('--half [half]', 'Which half to program (left, right)')
  .parse(process.argv);

(async () => {
  Echo(`${Commander.keyboard} / ${Commander.keymap}`);

  if (Commander.half != null) {
    await Upload(Commander.keyboard, Commander.keymap, Commander.path, Commander.half === 'right');
  } else {
    // Build both halves

    await Upload(Commander.keyboard, Commander.keymap);
    await Upload(Commander.keyboard, Commander.keymap, undefined, true);
  }
})();

process.on('unhandledRejection', err => {
  console.error(err);
  process.exit(1);
});
