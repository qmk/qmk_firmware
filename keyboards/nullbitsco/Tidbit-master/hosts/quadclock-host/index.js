const Bree = require('bree');
const Graceful = require('@ladjs/graceful');

const bree = new Bree({
  jobs: [
    {
      name: 'clock',
      timeout: 0,
      cron: '* * * * *',
    },
  ],
});

const graceful = new Graceful({ brees: [bree] });
graceful.listen();

bree.start();
