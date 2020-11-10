# group `SERIAL_USB` {#group___s_e_r_i_a_l___u_s_b}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`_qmk_usb_driver_data`](#group___s_e_r_i_a_l___u_s_b_1ga623f2c1e20bb296cf3cbdc88d153b6c9)            | `SerialDriver` specific data.
`define `[`_qmk_usb_driver_methods`](#group___s_e_r_i_a_l___u_s_b_1ga798bce936d06cb5332a1c0e545b84dbb)            | `SerialUSBDriver` specific methods.
`enum `[`qmkusbstate_t`](#group___s_e_r_i_a_l___u_s_b_1ga534e1c5933a7c4785f5882ad21674302)            | Driver state machine possible states.
`public static bool `[`qmkusb_start_receive`](#group___s_e_r_i_a_l___u_s_b_1ga4a2db2450b14c2a07c681b5d9429d76e)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | 
`public static size_t `[`_write`](#group___s_e_r_i_a_l___u_s_b_1ga5e8117f4f91892c3d46076b0853b9116)`(void * ip,const uint8_t * bp,size_t n)`            | 
`public static size_t `[`_read`](#group___s_e_r_i_a_l___u_s_b_1gac07ed241c806363b6d298d7b4e2c3dad)`(void * ip,uint8_t * bp,size_t n)`            | 
`public static msg_t `[`_put`](#group___s_e_r_i_a_l___u_s_b_1ga240a53ff8cbb972b8e9ccdd4cdbcaedd)`(void * ip,uint8_t b)`            | 
`public static msg_t `[`_get`](#group___s_e_r_i_a_l___u_s_b_1ga0ef118239efc83deca980513e7330658)`(void * ip)`            | 
`public static msg_t `[`_putt`](#group___s_e_r_i_a_l___u_s_b_1ga63abfd1c739742e5ae219f15824e47ca)`(void * ip,uint8_t b,sysinterval_t timeout)`            | 
`public static msg_t `[`_gett`](#group___s_e_r_i_a_l___u_s_b_1ga122f8c98aa183cf27022ea53a7cac4d5)`(void * ip,sysinterval_t timeout)`            | 
`public static size_t `[`_writet`](#group___s_e_r_i_a_l___u_s_b_1ga015a4300ed5207dec4541348a9a04671)`(void * ip,const uint8_t * bp,size_t n,sysinterval_t timeout)`            | 
`public static size_t `[`_readt`](#group___s_e_r_i_a_l___u_s_b_1ga87af5dde7865331b7634b63a3b004914)`(void * ip,uint8_t * bp,size_t n,sysinterval_t timeout)`            | 
`public static void `[`ibnotify`](#group___s_e_r_i_a_l___u_s_b_1ga278a0b24aa52959889f37ab7e8041698)`(io_buffers_queue_t * bqp)`            | Notification of empty buffer released into the input buffers queue.
`public static void `[`obnotify`](#group___s_e_r_i_a_l___u_s_b_1gaf0e8ad9d01f2cbe14aa5a4e49f099547)`(io_buffers_queue_t * bqp)`            | Notification of filled buffer inserted into the output buffers queue.
`public void `[`qmkusbInit`](#group___s_e_r_i_a_l___u_s_b_1ga3853659326b42a6df413177ff65d7c15)`(void)`            | Serial Driver initialization.
`public void `[`qmkusbObjectInit`](#group___s_e_r_i_a_l___u_s_b_1gaf8ba926d88993cb4fab100f1ef427e0b)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp,const `[`QMKUSBConfig`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_config)` * config)`            | Initializes a generic full duplex driver object.
`public void `[`qmkusbStart`](#group___s_e_r_i_a_l___u_s_b_1ga82f3c032f7fb6832a60d6048f69c3e3d)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp,const `[`QMKUSBConfig`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_config)` * config)`            | Configures and starts the driver.
`public void `[`qmkusbStop`](#group___s_e_r_i_a_l___u_s_b_1gaa032aca2a467800dc0dc0e205b4757d5)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | Stops the driver.
`public void `[`qmkusbSuspendHookI`](#group___s_e_r_i_a_l___u_s_b_1gad59935eea3dab7a0584fd759c884e814)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | USB device suspend handler.
`public void `[`qmkusbWakeupHookI`](#group___s_e_r_i_a_l___u_s_b_1ga9bc8dd88462d0e3b39f7fdfec2c3ee55)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | USB device wakeup handler.
`public void `[`qmkusbConfigureHookI`](#group___s_e_r_i_a_l___u_s_b_1ga920acd9f8890b819614515b73923b72f)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | USB device configured handler.
`public bool `[`qmkusbRequestsHook`](#group___s_e_r_i_a_l___u_s_b_1gabae5bdec8abeac31be61c976301c37ba)`(USBDriver * usbp)`            | Default requests hook.
`public void `[`qmkusbSOFHookI`](#group___s_e_r_i_a_l___u_s_b_1ga6db1c065c87835f96ffa248b80dbf381)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)`            | SOF handler.
`public void `[`qmkusbDataTransmitted`](#group___s_e_r_i_a_l___u_s_b_1ga2baecc9d4f4ec49c7e26b5dd0740c7cd)`(USBDriver * usbp,usbep_t ep)`            | Default data transmitted callback.
`public void `[`qmkusbDataReceived`](#group___s_e_r_i_a_l___u_s_b_1gafb6e37d8a2dd4fe37aabf86d18275546)`(USBDriver * usbp,usbep_t ep)`            | Default data received callback.
`public void `[`qmkusbInterruptTransmitted`](#group___s_e_r_i_a_l___u_s_b_1ga67ee1fd2c4129831dc15194d5284cf52)`(USBDriver * usbp,usbep_t ep)`            | Default data received callback.
`struct `[`QMKUSBConfig`](#struct_q_m_k_u_s_b_config) | Serial over USB Driver configuration structure.
`struct `[`QMKUSBDriverVMT`](#struct_q_m_k_u_s_b_driver_v_m_t) | `SerialDriver` virtual methods table.
`struct `[`QMKUSBDriver`](#struct_q_m_k_u_s_b_driver) | Full duplex serial driver class.

## Members

#### `define `[`_qmk_usb_driver_data`](#group___s_e_r_i_a_l___u_s_b_1ga623f2c1e20bb296cf3cbdc88d153b6c9) {#group___s_e_r_i_a_l___u_s_b_1ga623f2c1e20bb296cf3cbdc88d153b6c9}

`SerialDriver` specific data.

#### `define `[`_qmk_usb_driver_methods`](#group___s_e_r_i_a_l___u_s_b_1ga798bce936d06cb5332a1c0e545b84dbb) {#group___s_e_r_i_a_l___u_s_b_1ga798bce936d06cb5332a1c0e545b84dbb}

`SerialUSBDriver` specific methods.

#### `enum `[`qmkusbstate_t`](#group___s_e_r_i_a_l___u_s_b_1ga534e1c5933a7c4785f5882ad21674302) {#group___s_e_r_i_a_l___u_s_b_1ga534e1c5933a7c4785f5882ad21674302}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
QMKUSB_UNINIT            | Not initialized.
QMKUSB_STOP            | Stopped.
QMKUSB_READY            | Ready.

Driver state machine possible states.

#### `public static bool `[`qmkusb_start_receive`](#group___s_e_r_i_a_l___u_s_b_1ga4a2db2450b14c2a07c681b5d9429d76e)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1ga4a2db2450b14c2a07c681b5d9429d76e}

#### `public static size_t `[`_write`](#group___s_e_r_i_a_l___u_s_b_1ga5e8117f4f91892c3d46076b0853b9116)`(void * ip,const uint8_t * bp,size_t n)` {#group___s_e_r_i_a_l___u_s_b_1ga5e8117f4f91892c3d46076b0853b9116}

#### `public static size_t `[`_read`](#group___s_e_r_i_a_l___u_s_b_1gac07ed241c806363b6d298d7b4e2c3dad)`(void * ip,uint8_t * bp,size_t n)` {#group___s_e_r_i_a_l___u_s_b_1gac07ed241c806363b6d298d7b4e2c3dad}

#### `public static msg_t `[`_put`](#group___s_e_r_i_a_l___u_s_b_1ga240a53ff8cbb972b8e9ccdd4cdbcaedd)`(void * ip,uint8_t b)` {#group___s_e_r_i_a_l___u_s_b_1ga240a53ff8cbb972b8e9ccdd4cdbcaedd}

#### `public static msg_t `[`_get`](#group___s_e_r_i_a_l___u_s_b_1ga0ef118239efc83deca980513e7330658)`(void * ip)` {#group___s_e_r_i_a_l___u_s_b_1ga0ef118239efc83deca980513e7330658}

#### `public static msg_t `[`_putt`](#group___s_e_r_i_a_l___u_s_b_1ga63abfd1c739742e5ae219f15824e47ca)`(void * ip,uint8_t b,sysinterval_t timeout)` {#group___s_e_r_i_a_l___u_s_b_1ga63abfd1c739742e5ae219f15824e47ca}

#### `public static msg_t `[`_gett`](#group___s_e_r_i_a_l___u_s_b_1ga122f8c98aa183cf27022ea53a7cac4d5)`(void * ip,sysinterval_t timeout)` {#group___s_e_r_i_a_l___u_s_b_1ga122f8c98aa183cf27022ea53a7cac4d5}

#### `public static size_t `[`_writet`](#group___s_e_r_i_a_l___u_s_b_1ga015a4300ed5207dec4541348a9a04671)`(void * ip,const uint8_t * bp,size_t n,sysinterval_t timeout)` {#group___s_e_r_i_a_l___u_s_b_1ga015a4300ed5207dec4541348a9a04671}

#### `public static size_t `[`_readt`](#group___s_e_r_i_a_l___u_s_b_1ga87af5dde7865331b7634b63a3b004914)`(void * ip,uint8_t * bp,size_t n,sysinterval_t timeout)` {#group___s_e_r_i_a_l___u_s_b_1ga87af5dde7865331b7634b63a3b004914}

#### `public static void `[`ibnotify`](#group___s_e_r_i_a_l___u_s_b_1ga278a0b24aa52959889f37ab7e8041698)`(io_buffers_queue_t * bqp)` {#group___s_e_r_i_a_l___u_s_b_1ga278a0b24aa52959889f37ab7e8041698}

Notification of empty buffer released into the input buffers queue.

#### Parameters
* `bqp` the buffers queue pointer.

#### `public static void `[`obnotify`](#group___s_e_r_i_a_l___u_s_b_1gaf0e8ad9d01f2cbe14aa5a4e49f099547)`(io_buffers_queue_t * bqp)` {#group___s_e_r_i_a_l___u_s_b_1gaf0e8ad9d01f2cbe14aa5a4e49f099547}

Notification of filled buffer inserted into the output buffers queue.

#### Parameters
* `bqp` the buffers queue pointer.

#### `public void `[`qmkusbInit`](#group___s_e_r_i_a_l___u_s_b_1ga3853659326b42a6df413177ff65d7c15)`(void)` {#group___s_e_r_i_a_l___u_s_b_1ga3853659326b42a6df413177ff65d7c15}

Serial Driver initialization.

This function is implicitly invoked by `halInit()`, there is no need to explicitly initialize the driver.

#### `public void `[`qmkusbObjectInit`](#group___s_e_r_i_a_l___u_s_b_1gaf8ba926d88993cb4fab100f1ef427e0b)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp,const `[`QMKUSBConfig`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_config)` * config)` {#group___s_e_r_i_a_l___u_s_b_1gaf8ba926d88993cb4fab100f1ef427e0b}

Initializes a generic full duplex driver object.

The HW dependent part of the initialization has to be performed outside, usually in the hardware initialization code.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` structure

#### `public void `[`qmkusbStart`](#group___s_e_r_i_a_l___u_s_b_1ga82f3c032f7fb6832a60d6048f69c3e3d)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp,const `[`QMKUSBConfig`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_config)` * config)` {#group___s_e_r_i_a_l___u_s_b_1ga82f3c032f7fb6832a60d6048f69c3e3d}

Configures and starts the driver.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object 

* `config` the serial over USB driver configuration

#### `public void `[`qmkusbStop`](#group___s_e_r_i_a_l___u_s_b_1gaa032aca2a467800dc0dc0e205b4757d5)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1gaa032aca2a467800dc0dc0e205b4757d5}

Stops the driver.

Any thread waiting on the driver's queues will be awakened with the message `MSG_RESET`.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object

#### `public void `[`qmkusbSuspendHookI`](#group___s_e_r_i_a_l___u_s_b_1gad59935eea3dab7a0584fd759c884e814)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1gad59935eea3dab7a0584fd759c884e814}

USB device suspend handler.

Generates a `CHN_DISCONNECT` event and puts queues in non-blocking mode, this way the application cannot get stuck in the middle of an I/O operations. If this function is not called from an ISR then an explicit call to `osalOsRescheduleS()` in necessary afterward.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object

#### `public void `[`qmkusbWakeupHookI`](#group___s_e_r_i_a_l___u_s_b_1ga9bc8dd88462d0e3b39f7fdfec2c3ee55)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1ga9bc8dd88462d0e3b39f7fdfec2c3ee55}

USB device wakeup handler.

Generates a `CHN_CONNECT` event and resumes normal queues operations.

If this function is not called from an ISR then an explicit call to `osalOsRescheduleS()` in necessary afterward.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object

#### `public void `[`qmkusbConfigureHookI`](#group___s_e_r_i_a_l___u_s_b_1ga920acd9f8890b819614515b73923b72f)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1ga920acd9f8890b819614515b73923b72f}

USB device configured handler.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object

#### `public bool `[`qmkusbRequestsHook`](#group___s_e_r_i_a_l___u_s_b_1gabae5bdec8abeac31be61c976301c37ba)`(USBDriver * usbp)` {#group___s_e_r_i_a_l___u_s_b_1gabae5bdec8abeac31be61c976301c37ba}

Default requests hook.

Applications wanting to use the Serial over USB driver can use this function as requests hook in the USB configuration. The following requests are emulated:

* CDC_GET_LINE_CODING.

* CDC_SET_LINE_CODING.

* CDC_SET_CONTROL_LINE_STATE.

#### Parameters
* `usbp` pointer to the `USBDriver` object 

#### Returns
The hook status. 

#### Parameters
* `true` Message handled internally. 

* `false` Message not handled.

#### `public void `[`qmkusbSOFHookI`](#group___s_e_r_i_a_l___u_s_b_1ga6db1c065c87835f96ffa248b80dbf381)`(`[`QMKUSBDriver`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` * qmkusbp)` {#group___s_e_r_i_a_l___u_s_b_1ga6db1c065c87835f96ffa248b80dbf381}

SOF handler.

The SOF interrupt is used for automatic flushing of incomplete buffers pending in the output queue.

#### Parameters
* `qmkusbp` pointer to a `[QMKUSBDriver](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver)` object

#### `public void `[`qmkusbDataTransmitted`](#group___s_e_r_i_a_l___u_s_b_1ga2baecc9d4f4ec49c7e26b5dd0740c7cd)`(USBDriver * usbp,usbep_t ep)` {#group___s_e_r_i_a_l___u_s_b_1ga2baecc9d4f4ec49c7e26b5dd0740c7cd}

Default data transmitted callback.

The application must use this function as callback for the IN data endpoint.

#### Parameters
* `usbp` pointer to the `USBDriver` object 

* `ep` IN endpoint number

#### `public void `[`qmkusbDataReceived`](#group___s_e_r_i_a_l___u_s_b_1gafb6e37d8a2dd4fe37aabf86d18275546)`(USBDriver * usbp,usbep_t ep)` {#group___s_e_r_i_a_l___u_s_b_1gafb6e37d8a2dd4fe37aabf86d18275546}

Default data received callback.

The application must use this function as callback for the OUT data endpoint.

#### Parameters
* `usbp` pointer to the `USBDriver` object 

* `ep` OUT endpoint number

#### `public void `[`qmkusbInterruptTransmitted`](#group___s_e_r_i_a_l___u_s_b_1ga67ee1fd2c4129831dc15194d5284cf52)`(USBDriver * usbp,usbep_t ep)` {#group___s_e_r_i_a_l___u_s_b_1ga67ee1fd2c4129831dc15194d5284cf52}

Default data received callback.

The application must use this function as callback for the IN interrupt endpoint.

#### Parameters
* `usbp` pointer to the `USBDriver` object 

* `ep` endpoint number

# struct `QMKUSBConfig` {#struct_q_m_k_u_s_b_config}

Serial over USB Driver configuration structure.

An instance of this structure must be passed to `sduStart()` in order to configure and start the driver operations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public USBDriver * `[`usbp`](#struct_q_m_k_u_s_b_config_1ada1ea0b2aba306995949dbaa24fdf71d) | USB driver to use.
`public usbep_t `[`bulk_in`](#struct_q_m_k_u_s_b_config_1afa43b7b434054546af9f4ec651c5f97e) | Bulk IN endpoint used for outgoing data transfer.
`public usbep_t `[`bulk_out`](#struct_q_m_k_u_s_b_config_1a88cf95319b2e27fb5bcdb6d3bb116ba5) | Bulk OUT endpoint used for incoming data transfer.
`public usbep_t `[`int_in`](#struct_q_m_k_u_s_b_config_1a475ce337f1cac40f24657c2030a2f268) | Interrupt IN endpoint used for notifications.
`public size_t `[`in_buffers`](#struct_q_m_k_u_s_b_config_1a983983e0ca22143fd32e8dc3383c174e) | The number of buffers in the queues.
`public size_t `[`out_buffers`](#struct_q_m_k_u_s_b_config_1a481eeab48689523b99a95e1666b2cb96) | 
`public size_t `[`in_size`](#struct_q_m_k_u_s_b_config_1a600c0d75ca3fa7bafc2e38ce9bb0bf6e) | The size of each buffer in the queue, typically the same as the endpoint size.
`public size_t `[`out_size`](#struct_q_m_k_u_s_b_config_1ac5e66af2f4fed2cf04fcbd77f1114bfb) | 
`public bool `[`fixed_size`](#struct_q_m_k_u_s_b_config_1ad90e1bf1d310f5fbf5e8ce49b596f94b) | Always send full buffers in_size (the rest is filled with zeroes)
`public uint8_t * `[`ib`](#struct_q_m_k_u_s_b_config_1ae3be5d8a14227ab7003a9523994cae54) | 
`public uint8_t * `[`ob`](#struct_q_m_k_u_s_b_config_1a66f479912494377c5a80dc78ac2702cc) | 

## Members

#### `public USBDriver * `[`usbp`](#struct_q_m_k_u_s_b_config_1ada1ea0b2aba306995949dbaa24fdf71d) {#struct_q_m_k_u_s_b_config_1ada1ea0b2aba306995949dbaa24fdf71d}

USB driver to use.

#### `public usbep_t `[`bulk_in`](#struct_q_m_k_u_s_b_config_1afa43b7b434054546af9f4ec651c5f97e) {#struct_q_m_k_u_s_b_config_1afa43b7b434054546af9f4ec651c5f97e}

Bulk IN endpoint used for outgoing data transfer.

#### `public usbep_t `[`bulk_out`](#struct_q_m_k_u_s_b_config_1a88cf95319b2e27fb5bcdb6d3bb116ba5) {#struct_q_m_k_u_s_b_config_1a88cf95319b2e27fb5bcdb6d3bb116ba5}

Bulk OUT endpoint used for incoming data transfer.

#### `public usbep_t `[`int_in`](#struct_q_m_k_u_s_b_config_1a475ce337f1cac40f24657c2030a2f268) {#struct_q_m_k_u_s_b_config_1a475ce337f1cac40f24657c2030a2f268}

Interrupt IN endpoint used for notifications.

If set to zero then the INT endpoint is assumed to be not present, USB descriptors must be changed accordingly.

#### `public size_t `[`in_buffers`](#struct_q_m_k_u_s_b_config_1a983983e0ca22143fd32e8dc3383c174e) {#struct_q_m_k_u_s_b_config_1a983983e0ca22143fd32e8dc3383c174e}

The number of buffers in the queues.

#### `public size_t `[`out_buffers`](#struct_q_m_k_u_s_b_config_1a481eeab48689523b99a95e1666b2cb96) {#struct_q_m_k_u_s_b_config_1a481eeab48689523b99a95e1666b2cb96}

#### `public size_t `[`in_size`](#struct_q_m_k_u_s_b_config_1a600c0d75ca3fa7bafc2e38ce9bb0bf6e) {#struct_q_m_k_u_s_b_config_1a600c0d75ca3fa7bafc2e38ce9bb0bf6e}

The size of each buffer in the queue, typically the same as the endpoint size.

#### `public size_t `[`out_size`](#struct_q_m_k_u_s_b_config_1ac5e66af2f4fed2cf04fcbd77f1114bfb) {#struct_q_m_k_u_s_b_config_1ac5e66af2f4fed2cf04fcbd77f1114bfb}

#### `public bool `[`fixed_size`](#struct_q_m_k_u_s_b_config_1ad90e1bf1d310f5fbf5e8ce49b596f94b) {#struct_q_m_k_u_s_b_config_1ad90e1bf1d310f5fbf5e8ce49b596f94b}

Always send full buffers in_size (the rest is filled with zeroes)

#### `public uint8_t * `[`ib`](#struct_q_m_k_u_s_b_config_1ae3be5d8a14227ab7003a9523994cae54) {#struct_q_m_k_u_s_b_config_1ae3be5d8a14227ab7003a9523994cae54}

#### `public uint8_t * `[`ob`](#struct_q_m_k_u_s_b_config_1a66f479912494377c5a80dc78ac2702cc) {#struct_q_m_k_u_s_b_config_1a66f479912494377c5a80dc78ac2702cc}

# struct `QMKUSBDriverVMT` {#struct_q_m_k_u_s_b_driver_v_m_t}

```
struct QMKUSBDriverVMT
  : public BaseAsynchronousChannelVMT
```  

`SerialDriver` virtual methods table.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# struct `QMKUSBDriver` {#struct_q_m_k_u_s_b_driver}

```
struct QMKUSBDriver
  : public BaseAsynchronousChannel
```  

Full duplex serial driver class.

This class extends `BaseAsynchronousChannel` by adding physical I/O queues.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const struct `[`QMKUSBDriverVMT`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver_v_m_t)` * `[`vmt`](#struct_q_m_k_u_s_b_driver_1aa84464b0edad252f9f93af83c669501e) | Virtual Methods Table.

## Members

#### `public const struct `[`QMKUSBDriverVMT`](.build/docs/internals_SERIAL_USB.md#struct_q_m_k_u_s_b_driver_v_m_t)` * `[`vmt`](#struct_q_m_k_u_s_b_driver_1aa84464b0edad252f9f93af83c669501e) {#struct_q_m_k_u_s_b_driver_1aa84464b0edad252f9f93af83c669501e}

Virtual Methods Table.

