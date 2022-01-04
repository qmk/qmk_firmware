# Quadclock Host

Host for the `quadclock` keymap that sends the current time over HID every minute as a job.

## Quick Start

- Install [Node.js](https://nodejs.org/)
- Install dependencies with [npm](https://www.npmjs.com/): `npm i`
- Run the app: `npm start`

When the host successfully sends an update you will see output similar to the following:

```shell
Worker for job "clock" online undefined
Device found.
Worker for job "clock" signaled completion { message: 'done' }
```
