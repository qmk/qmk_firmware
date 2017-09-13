const { exec, execSync } = require('child_process');
const Chalk = require('chalk');

function IdentifyKeyboard (name = 'Kiibohd DFU', path, limit = false) {
  const boards = execSync(`dfu-util --list`).toString()
    .split('\n')
    .filter(line => line.match(/(\[\w+\:\w+\])/g) != null)
    .map(line => ({
      name: /name="([\w\s]+)"/g.exec(line)[1],
      path: /path="([\w-]+)"/g.exec(line)[1],
      id: /(\[\w+\:\w+\])/g.exec(line)[1]
    }))
    .filter(device => device.name === name || device.path === path);
  if (limit) {
    return boards[0];
  } else {
    return boards.length > 0 ? boards : undefined;
  }
}
module.exports.IdentifyKeyboard = IdentifyKeyboard;

function Exec (command) {
  return new Promise((resolve, reject) => {
    console.log(Chalk.blue`] $ ` + command);
    const proc = exec(command, (err) => {
      if (err) {
        console.log();
        reject(err);
      } else {
        console.log();
        resolve();
      }
    });
    const line_start = Chalk.blue(']\t');
    proc.stdout.on('data', data => {
      // process.stdout.write(line_start);
      // process.stdout.write(data.toString().replace(/\n/g, `\n`));
      process.stdout.write(data);
    });
  });
}
module.exports.Exec = Exec;

function Echo (...logs) {
  for(const log of logs) {
    if (typeof log === 'string') {
      console.log(log);
    } else {
      console.log((log && log.toString) ? log.toString() : log);
    }
  }
}
module.exports.Echo = Echo;

function Sleep (duration) {
  return new Promise(resolve => setTimeout(resolve, duration));
}
module.exports.Sleep = Sleep;
