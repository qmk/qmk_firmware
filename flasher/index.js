#!/usr/bin/env node

const { execSync, exec } = require('child_process');

const { Echo, Exec, IdentifyKeyboard } = require('./util');
const { Upload } = require('./commands');

const KEYMAP = process.env.KEYMAP || 'default';
const LEFT_TARGET = process.env.LEFT;
const RIGHT_TARGET = process.env.RIGHT;

(async () => {
  Echo(`Keymap: ${KEYMAP}`);

  if (process.env.LEFT || process.env.RIGHT) {
    if (process.env.LEFT) {
      await Upload(KEYMAP);
    }

    if (process.env.RIGHT) {
      await Upload(KEYMAP, undefined, true);
    }
  } else {
    // Build both halves
    await Upload(KEYMAP);

    await Upload(KEYMAP, undefined, true);
  }
})();
