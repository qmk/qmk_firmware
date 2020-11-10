# group `group_sam0_utils_status_codes` {#group__group__sam0__utils__status__codes}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`STATUS_CATEGORY_MASK`](#group__group__sam0__utils__status__codes_1ga5bf938a904077896054cd093bf7d8fa8)            | Mask to retrieve the error category of a status code.
`define `[`STATUS_ERROR_MASK`](#group__group__sam0__utils__status__codes_1ga4c46d8f176ca46ab775db0fe270d2f98)            | Mask to retrieve the error code within the category of a status code.
`enum `[`status_categories`](#group__group__sam0__utils__status__codes_1ga477539e8a67b0cab096e8ecda6f5d7d6)            | Status code error categories.
`enum `[`status_code`](#group__group__sam0__utils__status__codes_1ga751c892e5a46b8e7d282085a5a5bf151)            | Status code that may be returned by shell commands and protocol implementations.
`enum `[`status_code_wireless`](#group__group__sam0__utils__status__codes_1ga29235ed38b6f02861f29daae665ac3a2)            | Status codes used by MAC stack.

## Members

#### `define `[`STATUS_CATEGORY_MASK`](#group__group__sam0__utils__status__codes_1ga5bf938a904077896054cd093bf7d8fa8) {#group__group__sam0__utils__status__codes_1ga5bf938a904077896054cd093bf7d8fa8}

Mask to retrieve the error category of a status code.

#### `define `[`STATUS_ERROR_MASK`](#group__group__sam0__utils__status__codes_1ga4c46d8f176ca46ab775db0fe270d2f98) {#group__group__sam0__utils__status__codes_1ga4c46d8f176ca46ab775db0fe270d2f98}

Mask to retrieve the error code within the category of a status code.

#### `enum `[`status_categories`](#group__group__sam0__utils__status__codes_1ga477539e8a67b0cab096e8ecda6f5d7d6) {#group__group__sam0__utils__status__codes_1ga477539e8a67b0cab096e8ecda6f5d7d6}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
STATUS_CATEGORY_OK            | 
STATUS_CATEGORY_COMMON            | 
STATUS_CATEGORY_ANALOG            | 
STATUS_CATEGORY_COM            | 
STATUS_CATEGORY_IO            | 

Status code error categories.

#### `enum `[`status_code`](#group__group__sam0__utils__status__codes_1ga751c892e5a46b8e7d282085a5a5bf151) {#group__group__sam0__utils__status__codes_1ga751c892e5a46b8e7d282085a5a5bf151}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
STATUS_OK            | 
STATUS_VALID_DATA            | 
STATUS_NO_CHANGE            | 
STATUS_ABORTED            | 
STATUS_BUSY            | 
STATUS_SUSPEND            | 
STATUS_ERR_IO            | 
STATUS_ERR_REQ_FLUSHED            | 
STATUS_ERR_TIMEOUT            | 
STATUS_ERR_BAD_DATA            | 
STATUS_ERR_NOT_FOUND            | 
STATUS_ERR_UNSUPPORTED_DEV            | 
STATUS_ERR_NO_MEMORY            | 
STATUS_ERR_INVALID_ARG            | 
STATUS_ERR_BAD_ADDRESS            | 
STATUS_ERR_BAD_FORMAT            | 
STATUS_ERR_BAD_FRQ            | 
STATUS_ERR_DENIED            | 
STATUS_ERR_ALREADY_INITIALIZED            | 
STATUS_ERR_OVERFLOW            | 
STATUS_ERR_NOT_INITIALIZED            | 
STATUS_ERR_SAMPLERATE_UNAVAILABLE            | 
STATUS_ERR_RESOLUTION_UNAVAILABLE            | 
STATUS_ERR_BAUDRATE_UNAVAILABLE            | 
STATUS_ERR_PACKET_COLLISION            | 
STATUS_ERR_PROTOCOL            | 
STATUS_ERR_PIN_MUX_INVALID            | 

Status code that may be returned by shell commands and protocol implementations.

Any change to these status codes and the corresponding message strings is strictly forbidden. New codes can be added, however, but make sure that any message string tables are updated at the same time.

#### `enum `[`status_code_wireless`](#group__group__sam0__utils__status__codes_1ga29235ed38b6f02861f29daae665ac3a2) {#group__group__sam0__utils__status__codes_1ga29235ed38b6f02861f29daae665ac3a2}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
ERR_IO_ERROR            | I/O error.
ERR_FLUSHED            | Request flushed from queue.
ERR_TIMEOUT            | Operation timed out.
ERR_BAD_DATA            | Data integrity check failed.
ERR_PROTOCOL            | Protocol error.
ERR_UNSUPPORTED_DEV            | Unsupported device.
ERR_NO_MEMORY            | Insufficient memory.
ERR_INVALID_ARG            | Invalid argument.
ERR_BAD_ADDRESS            | Bad address.
ERR_BUSY            | Resource is busy.
ERR_BAD_FORMAT            | Data format not recognized.
ERR_NO_TIMER            | No timer available.
ERR_TIMER_ALREADY_RUNNING            | Timer already running.
ERR_TIMER_NOT_RUNNING            | Timer not running.
OPERATION_IN_PROGRESS            | Operation in progress.

Status codes used by MAC stack.

