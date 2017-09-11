module.exports.Upload = async function Upload (keymap, target, right = false) {
  await build(right);

  let board;
  while (board == null) {
    board = IdentifyKeyboard();
    if (board == null) {
      Echo(`Put your keyboard in flash mode`);
    }
  }

  Echo(`Building for ${board.name}`);
  await flash(right, board);
}

module.exports.Build = async function Build (right = false) {
  Echo(`Building ${right ? 'right' : 'left'}`);
  await Exec(`make ergodox_infinity-${KEYMAP} ${right ? 'MASTER=right' : ''}`);
  Echo(`Built ${right ? 'right' : 'left'}`, '');
}

module.exports.Flash = function Flash (right = false, board) {
  return new Promise(async resolve => {
    Echo(`Flashing ${right ? 'right' : 'left'}`);
    try {
      await Exec(`make ergodox_infinity-${KEYMAP}-dfu-util ${right ? 'MASTER=right' : ''}`);
    } catch (err) {
      if (err.message && err.message.includes(`More than one DFU capable USB device found`)) {
        Echo(`QMK flash failed!`);
        Echo(`Flashing manually with dfu-util`);

        await Exec(`dfu-util --device ${board.id} -D .build/ergodox_infinity_default.bin`);
      } else {
        throw err;
      }
    }
    Echo(`Flashed ${right ? 'right' : 'left'}`, '');

    // while (IdentifyKeyboard()) {
    //   Echo(`Unplug your keyboard!`);
    // }
    // TODO: Check to see if the script is done. If it is, then don't require an unplug
    // TODO: Make this actually look for the keyboard to be unplugged
    Echo(`Unplug your keyboard! (you have 15 seconds to do so)`);
    setTimeout(() => resolve(), 15000);
  });
}
