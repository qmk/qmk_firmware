# QMK Compiler Development Guide

This page attempts to introduce developers to the QMK Compiler. It does not go into nitty gritty details- for that you should read code. What this will give you is a framework to hang your understanding on as you read the code.

# Overview

The QMK Compile API consists of a few moving parts:

![Architecture Diagram](https://raw.githubusercontent.com/qmk/qmk_api/master/docs/architecture.svg)

API Clients interact exclusively with the API service. This is where they submit jobs, check status, and download results. The API service inserts compile jobs into [Redis Queue](https://python-rq.org) and checks both RQ and S3 for the results of those jobs.

Workers fetch new compile jobs from RQ, compile them, and then upload the source and the binary to an S3 compatible storage engine.

# Workers

QMK Compiler Workers are responsible for doing the actual building. When a worker pulls a job from RQ it does several things to complete that job:

* Make a fresh qmk_firmware checkout
* Use the supplied layers and keyboard metadata to build a `keymap.c`
* Build the firmware
* Zip a copy of the source
* Upload the firmware, source zip, and a metadata file to S3.
* Report the status of the job to RQ

# API Service

The API service is a relatively simple Flask application. There are a few main views you should understand.

## @app.route('/v1/compile', methods=['POST'])

This is the main entrypoint for the API. A client's interaction starts here. The client POST's a JSON document describing their keyboard, and the API does some (very) basic validation of that JSON before submitting the compile job.

## @app.route('/v1/compile/&lt;string:job_id&gt;', methods=['GET'])

This is the most frequently called endpoint. It pulls the job details from redis, if they're still available, or the cached job details on S3 if they're not.

## @app.route('/v1/compile/&lt;string:job_id&gt;/download', methods=['GET'])

This method allows users to download the compiled firmware file.

## @app.route('/v1/compile/&lt;string:job_id&gt;/source', methods=['GET'])

This method allows users to download the source for their firmware.
