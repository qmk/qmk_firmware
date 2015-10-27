#!/usr/bin/env node

//             LUFA Library
//     Copyright (C) Dean Camera, 2014.
//
//  dean [at] fourwalledcubicle [dot] com
//           www.lufa-lib.org

// LUFA Generic HID device demo host test script. This script will send a
// continuous stream of generic reports to the device, to show a variable LED
// pattern on the target board. Send and received report data is printed to
// the terminal.
//
// You have to install the usb and async modules prior to executing this script:
// apt-get install libusb-1.0-0-dev
// npm install usb async sprintf

var usb = require('usb');
var async = require('async');
var sprintf = require('sprintf');

var deviceVid = 0x03EB;
var devicePid = 0x204F;
var reportLength = 8;

function getAndInitHidDeviceAndInterface()
{
    device = usb.findByIds(deviceVid, devicePid);
    if (!device) {
        console.log('No device found');
        process.exit(1);
    }
    device.open();

    var hidInterface = device.interface(0);
    if (hidInterface.isKernelDriverActive()) {
        hidInterface.detachKernelDriver();
    }
    hidInterface.claim();

    async.series([
        function(callback) {
            setConfiguration(0, function(error, data) {
                callback();
            });
        }
    ]);

    return {hidDevice:device, hidInterface:hidInterface};
}

function read(hidInterface, callback)
{
    endpoint = hidInterface.endpoints[0];
    endpoint.transfer(reportLength, function(error, data) {
        if (error) {
            console.log(error)
        } else {
            console.log("Received LED Pattern:", data.slice(0, 4));
        }
        callback();
    });
}

function write(hidDevice, message, callback)
{
    hidDevice.controlTransfer(    // Send a Set Report control request
        parseInt('00100001', 2),  // bmRequestType (constant for this control request)
        0x09,                     // bmRequest (constant for this control request)
        0x0809,                   // wValue (MSB is report type, LSB is report number)
        0,                        // wIndex (interface number)
        message,                  // message to be sent
        function(error, data) {   // callback to be executed upon finishing the transfer
            console.log("Sent LED Pattern:", message.slice(1, 5))
            callback();
        }
    );
}

function setConfiguration(configurationNumber, callback)
{
    device.controlTransfer(                 // Send a Set Configuration control request
        parseInt('00000000', 2),            // bmRequestType
        0x09,                               // bmRequest
        0,                                  // wValue (Configuration value)
        0,                                  // wIndex
        new Buffer(0),                      // message to be sent
        callback                            // callback to be executed upon finishing the transfer
    );
}

// @TODO: Fix this function because apparently it doesn't work for some reason.
function getStringDescriptor(stringId, languageId, callback)
{
    var STRING_DESCRIPTOR_TYPE = 0x03;
    var wValue = (STRING_DESCRIPTOR_TYPE << 8) | stringId;

    device.controlTransfer(       // Send a Get Descriptor control request
        parseInt('10000000', 2),  // bmRequestType
        0x06,                     // bmRequest
        wValue,                   // wValue
        languageId,               // wIndex
        64,                       // response length
        callback                  // callback to be executed upon finishing the transfer
    );
}

function setNextPattern()
{
    var pattern = [
        hidInterface.interface,
        (p >> 3) & 1,
        (p >> 2) & 1,
        (p >> 1) & 1,
        (p >> 0) & 1
    ];

    async.series([
        function(callback) {
            write(hidDevice, new Buffer(pattern), callback);
        },
        function(callback) {
            read(hidInterface, callback);
        },
        function(callback) {
            p = (p + 1) % 16
            setTimeout(setNextPattern, 200);
            callback();
        }]);
}

var hidDeviceAndInterface = getAndInitHidDeviceAndInterface();
var hidDevice = hidDeviceAndInterface.hidDevice
var hidInterface = hidDeviceAndInterface.hidInterface;

console.log(sprintf("Connected to device 0x%04X/0x%04X - %s [%s]",
            hidDevice.deviceDescriptor.idVendor,
            hidDevice.deviceDescriptor.idProduct,
            hidDevice.deviceDescriptor.iProduct,
            hidDevice.deviceDescriptor.iManufacturer));

p = 0
setNextPattern();
