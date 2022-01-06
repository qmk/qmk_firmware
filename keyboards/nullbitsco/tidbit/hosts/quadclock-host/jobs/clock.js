const HID = require('node-hid');
const format = require('date-fns/format');
const { parentPort } = require('worker_threads');

const VENDOR_ID = 0x6e61;
const PRODUCT_ID = 0x6061;
const USAGE_PAGE = 0xff60;
const USAGE_ID = 0x61;

const CLOCK_RAW_HID_FORMAT = 'yyyy,MM,dd,HH,mm,ss,SSS';
const RAW_HID_SKIPPED_BYTE = 0x00;
const VIA_RAW_HID_COMMAND_ID = 0x03; // id_set_keyboard_value
const VIA_RAW_HID_COMMAND_DATA = 0x00; // https://github.com/qmk/qmk_firmware/blob/master/quantum/via.c#L252

let hid;

function getDevice() {
  const result = HID.devices().find(
    (d) =>
      d.vendorId === VENDOR_ID &&
      d.productId === PRODUCT_ID &&
      d.usagePage === USAGE_PAGE &&
      d.usage === USAGE_ID
  );
  if (!result) return null;

  return result;
}

function serializeString(input) {
  const buffer = Buffer.from(input);

  // NOTE: The first HID byte is skipped and in VIA we must send a dummy "Command ID" and "Command Data" byte
  // so that `raw_hid_receive_kb()` gets called.
  // See: https://github.com/qmk/qmk_firmware/blob/master/quantum/via.c#L252
  const result = [
    RAW_HID_SKIPPED_BYTE,
    VIA_RAW_HID_COMMAND_ID,
    VIA_RAW_HID_COMMAND_DATA,
    ...buffer,
  ];

  return result;
}

function cancel() {
  if (hid) hid.close();

  if (parentPort) parentPort.postMessage('cancel');
  else process.exit(0);
}

// Get device
const device = getDevice();
if (!device) {
  console.log('Device not found.');
  if (parentPort) parentPort.postMessage('done');
  else process.exit(0);
  return;
}

console.log('Device found.');
console.log(`  Manufacturer: '${device.manufacturer}'`);
console.log(`  Product: '${device.product}'`);

// Handle cancellation
if (parentPort) {
  parentPort.once('message', (message) => {
    if (message === 'cancel') return cancel();
  });
}

// Create HID and timestamp data
hid = new HID.HID(device.path);
const str = `${format(new Date(), CLOCK_RAW_HID_FORMAT)}`;
const data = serializeString(str);

// Write data
console.log(`Writing '${str}'.`);
try {
  hid.write(data);
} finally {
  hid.close();
}

// Done
console.log('Done.');
if (parentPort) parentPort.postMessage('done');
else process.exit(0);
