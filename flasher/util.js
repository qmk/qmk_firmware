const Chalk = require('chalk');

module.exports.IdentifyKeyboard = function IdentifyKeyboard (name = 'Kiibohd DFU', path, limit = true) {
  const boards = execSync(`dfu-util --list`).toString()
    .split('\n')
    .filter(line => line.match(/(\[\w+\:\w+\])/g) != null)
    .map(line => ({
      name: /name="([\w\s]+)"/g.exec(line)[1],
      id: /(\[\w+\:\w+\])/g.exec(line)[1]
    }))
    .filter(device => device.name === name && path != null ? device.path === path : true);
  if (limit) {
    return boards[0];
  } else {
    return boards;
  }
}

module.exports.Exec = function Exec (command) {
  return new Promise((resolve, reject) => {
    console.log(command);
    const proc = exec(command, (err) => {
      if (err) {
        reject(err);
      } else {
        resolve();
      }
    });
    const line_start = Chalk.blue(']\t');
    proc.stdout.on('data', data => console.log(line_start + data.replace(/\n$/, '').replace(/\n/g, `\n${line_start}`)));
  });
}

module.exports.Echo = function Echo (...logs) {
  for(const log of logs) {
    if (typeof log === 'string') {
      console.log(log);
    } else {
      console.log(log.toString ? log.toString() : log);
    }
  }
}
