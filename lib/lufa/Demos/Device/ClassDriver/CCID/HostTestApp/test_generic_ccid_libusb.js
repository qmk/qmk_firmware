#!/usr/bin/env node

//             LUFA Library
//     Copyright (C) Dean Camera, 2019.
//
//  dean [at] fourwalledcubicle [dot] com
//
//           www.lufa-lib.org

// Copyright 2019  Filipe Rodrigues (filipepazrodrigues [at] gmail [dot] com)
//
// LUFA Generic CCID device demo host test script. This script test multiple
// kinds of CCID messages and shows the result to the console
//
// You have to install the usb and async modules prior to executing this script:
// apt-get install libusb-1.0-0-dev
// npm install usb async sprintf

var usb = require('usb');
var async = require('async');
var sprintf = require('sprintf');

var deviceVid = 0x03EB;
var devicePid = 0x206E;

var CCID_PC_to_RDR_SetParameters        = 0x61;
var CCID_PC_to_RDR_GetParameters        = 0x6C;
var CCID_PC_to_RDR_IccPowerOn           = 0x62;
var CCID_PC_to_RDR_IccPowerOff          = 0x63;
var CCID_PC_to_RDR_GetSlotStatus        = 0x65;
var CCID_PC_to_RDR_XfrBlock             = 0x6f;

function getAndInitCcidDeviceAndInterface()
{
    device = usb.findByIds(deviceVid, devicePid);
    if (!device) {
        console.log('No device found');
        process.exit(1);
    }
    device.open();

    var ccidInterface = device.interface(0);
    if (ccidInterface.isKernelDriverActive()) {
        ccidInterface.detachKernelDriver();
    }
    ccidInterface.claim();

    return {ccidDevice:device, ccidInterface:ccidInterface};
}

function read(ccidInterface, responseSize,  callback)
{
    inEndpoint = ccidInterface.endpoints[0];
    inEndpoint.transfer(responseSize, function(error, data) {
        if (error) {
            console.log(error)
        } else {
            console.log("Received data:", data);
        }
        callback();
    });
}

function write(ccidInterface, message, callback)
{
    outEndpoint = ccidInterface.endpoints[1]
    outEndpoint.transfer(    // Send a Set Report control request
        message,                  // message to be sent
        function(error) {   // callback to be executed upon finishing the transfer
            callback();
        }
    );
}

//CCID functions

function GetParametersMessage(slot, seq, protocolNum, t0Params)
{
    return [
        CCID_PC_to_RDR_GetParameters, //message type
        0, 0, 0, 0, //length
        slot,
        seq,
        0, 0, 0 //RFU
    ];
}

function SetParametersMessage(slot, seq, protocolNum, t0Params)
{
    return [
        CCID_PC_to_RDR_SetParameters, //message type
        t0Params.length, 0, 0, 0, //length
        slot,
        seq,
        protocolNum,
        0, 0 //RFU
    ].concat(t0Params);
}


function IccPowerOnMessage(slot, seq)
{
    return [
        CCID_PC_to_RDR_IccPowerOn, //message type
        0, 0, 0, 0, //length
        slot,
        seq,
        0, //power select: automatic
        0, 0 //RFU
    ];
}

function IccPowerOffMessage(slot, seq)
{
    return [
        CCID_PC_to_RDR_IccPowerOff, //message type
        0, 0, 0, 0, //length
        slot,
        seq,
        0, 0, 0 //RFU
    ];
}

function GetSlotStatusMessage(slot, seq)
{
    return [
        CCID_PC_to_RDR_GetSlotStatus, //message type
        0, 0, 0, 0, //length
        slot,
        seq,
        0, 0, 0 //RFU
    ];
}

function XfrBlockMessage(slot, seq, apdu)
{
    return [
        CCID_PC_to_RDR_XfrBlock, //message type
        apdu.length, 0, 0, 0, //length: only for < 0xFF
        slot,
        seq,
        0, //BWI
        0, 0 //level parameter
    ].concat(apdu);

}

function testCcidMessages()
{
    return [
        function(callback) {
            write(ccidInterface, new Buffer(IccPowerOnMessage(0, 1)), callback);
        },
        function(callback) {
            read(ccidInterface, 10 + 17, callback);
        },
        function(callback) {
            write(ccidInterface, new Buffer(IccPowerOffMessage(0, 2)), callback);
        },
        function(callback) {
            read(ccidInterface, 10, callback);
        },
        function(callback) {
            write(ccidInterface, new Buffer(GetSlotStatusMessage(0, 3)), callback);
        },
        function(callback) {
            read(ccidInterface, 10, callback);
        },
        function(callback) {
            write(ccidInterface, new Buffer(SetParametersMessage(0, 4, 0, [0x11, 0x00, 0x00, 0x0a, 0x00])), callback);
        },
        function(callback) {
            //must return 82 05 00 00 00 00 04 00 80 00 11 00 00 0a 00
            read(ccidInterface, 30, callback);
        },
        function(callback) {
            write(ccidInterface, new Buffer(GetParametersMessage(0, 5, 0)), callback);
        },
        function(callback) {
            //must return 82 05 00 00 00 00 04 00 80 00 11 00 00 0a 00
            read(ccidInterface, 30, callback);
        }];
}

function startTest()
{
    async.series([]
        .concat(testCcidMessages())
    );
}

var ccidDeviceAndInterface = getAndInitCcidDeviceAndInterface();
var ccidDevice = ccidDeviceAndInterface.ccidDevice
var ccidInterface = ccidDeviceAndInterface.ccidInterface;

console.log(sprintf("Connected to device 0x%04X/0x%04X - %s [%s]",
            ccidDevice.deviceDescriptor.idVendor,
            ccidDevice.deviceDescriptor.idProduct,
            ccidDevice.deviceDescriptor.iProduct,
            ccidDevice.deviceDescriptor.iManufacturer));

startTest();
