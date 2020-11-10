# group `usb_protocol_group` {#group__usb__protocol__group}

This module defines constants and data structures provided by the USB 2.0 specification.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`USB_V2_0`](#group__usb__protocol__group_1ga9bccec980a4f41a481b389b4f0c9c690)            | Value for field bcdUSB.
`define `[`USB_V2_1`](#group__usb__protocol__group_1ga98059f51cd65930412083d423a70dd17)            | USB Specification version 2.01.
`define `[`USB_REQ_DIR_OUT`](#group__usb__protocol__group_1ga3fae7189eea003bf79ac2949b0f50584)            | USB request data transfer direction (bmRequestType)
`define `[`USB_REQ_DIR_IN`](#group__usb__protocol__group_1ga3d3c24265f68a720887ae4ff7158d605)            | Device to host.
`define `[`USB_REQ_DIR_MASK`](#group__usb__protocol__group_1gac94f5ec9106e17f2e6d927eeac3d530f)            | Mask.
`define `[`USB_REQ_TYPE_STANDARD`](#group__usb__protocol__group_1ga3eb781776ab6dcbc6fa96e1b0ed18011)            | USB request types (bmRequestType)
`define `[`USB_REQ_TYPE_CLASS`](#group__usb__protocol__group_1gaff9ee0044c6cb131b2908356adc37dff)            | Class-specific request.
`define `[`USB_REQ_TYPE_VENDOR`](#group__usb__protocol__group_1ga71855621792f72443ed5497b313a2517)            | Vendor-specific request.
`define `[`USB_REQ_TYPE_MASK`](#group__usb__protocol__group_1ga8be8332e2da1e54c74c5f2a2230b0a28)            | Mask.
`define `[`USB_REQ_RECIP_DEVICE`](#group__usb__protocol__group_1ga65c1569b970837dd4a2ad8e1b4097589)            | USB recipient codes (bmRequestType)
`define `[`USB_REQ_RECIP_INTERFACE`](#group__usb__protocol__group_1gad3d0e7d70c610967cc2ee12c5298ac69)            | Recipient interface.
`define `[`USB_REQ_RECIP_ENDPOINT`](#group__usb__protocol__group_1ga1be00350ff83d022d41b4eae81f1e2b2)            | Recipient endpoint.
`define `[`USB_REQ_RECIP_OTHER`](#group__usb__protocol__group_1gabb5706061604f770d2ce1f3891ab0296)            | Recipient other.
`define `[`USB_REQ_RECIP_MASK`](#group__usb__protocol__group_1gab1738c19d49fe1d4c7edccff90e9e9e4)            | Mask.
`define `[`HIRD_50_US`](#group__usb__protocol__group_1ga63ce14c89bdb5349988cb983b7176740)            | 
`define `[`HIRD_125_US`](#group__usb__protocol__group_1ga8fa50bfccd00843cd32719521720f7f6)            | 
`define `[`HIRD_200_US`](#group__usb__protocol__group_1gad6f9ff2585cbc2b0ca161ee12a11b154)            | 
`define `[`HIRD_275_US`](#group__usb__protocol__group_1ga51c55e5d7938a80a53084b5a2a93b9b3)            | 
`define `[`HIRD_350_US`](#group__usb__protocol__group_1ga28a9220cf691f45fa880638ad92ed95a)            | 
`define `[`HIRD_425_US`](#group__usb__protocol__group_1gab0f175ff5b6a35c08d4730f3b82e3290)            | 
`define `[`HIRD_500_US`](#group__usb__protocol__group_1gaf75c36a22358dbe9d27fa2122d39ac32)            | 
`define `[`HIRD_575_US`](#group__usb__protocol__group_1ga27244f075c4ae2c34bcdeecca8921e9d)            | 
`define `[`HIRD_650_US`](#group__usb__protocol__group_1ga33e1236c9694d97c574677ed36da8ce4)            | 
`define `[`HIRD_725_US`](#group__usb__protocol__group_1gab1cfbd6207cc526b33a65593379f1802)            | 
`define `[`HIRD_800_US`](#group__usb__protocol__group_1gaec9c3475ae7a1a2deefdb7f844ab25b4)            | 
`define `[`HIRD_875_US`](#group__usb__protocol__group_1ga39eaf9efa2c721560ae7e6d4463ed353)            | 
`define `[`HIRD_950_US`](#group__usb__protocol__group_1ga6a950e4e5666cd014db36bd4971ac888)            | 
`define `[`HIRD_1025_US`](#group__usb__protocol__group_1ga07cfb9848da18f98190ff86ca5349b53)            | 
`define `[`HIRD_1100_US`](#group__usb__protocol__group_1ga52b2c19a0df1c72ed04a97ccb3b9152e)            | 
`define `[`HIRD_1175_US`](#group__usb__protocol__group_1ga29284c56fb4827b69c00332b7a4fdb76)            | 
`define `[`USB_LPM_ATTRIBUT_BLINKSTATE_MASK`](#group__usb__protocol__group_1gaf39d50c3bb01f68fa434e7fdf3a44e22)            | Fields definition from a LPM TOKEN
`define `[`USB_LPM_ATTRIBUT_FIRD_MASK`](#group__usb__protocol__group_1gaf53a7676592b02f9bb846e1062af463c)            | 
`define `[`USB_LPM_ATTRIBUT_REMOTEWAKE_MASK`](#group__usb__protocol__group_1ga9c1618c348394534d968097c8d76c092)            | 
`define `[`USB_LPM_ATTRIBUT_BLINKSTATE`](#group__usb__protocol__group_1ga1deb3dda1fc39b7425359c72eb548b0d)            | 
`define `[`USB_LPM_ATTRIBUT_FIRD`](#group__usb__protocol__group_1ga0eb84fe948d5e4650a39d6081b959c70)            | 
`define `[`USB_LPM_ATTRIBUT_REMOTEWAKE`](#group__usb__protocol__group_1ga7482138e5ce2d2ec9482bcd5dbd9bd64)            | 
`define `[`USB_LPM_ATTRIBUT_BLINKSTATE_L1`](#group__usb__protocol__group_1ga02be6765d15e86d37fd66ce6862a16fc)            | 
`define `[`USB_EP_ADDR_MASK`](#group__usb__protocol__group_1ga0316d8f43a1648b76df257332b26aeb9)            | Mask selecting the index part of an endpoint address.
`define `[`USB_EP_DIR_IN`](#group__usb__protocol__group_1gaae8411e95f26738326bc25a0161dde99)            | Endpoint transfer direction is IN.
`define `[`USB_EP_DIR_OUT`](#group__usb__protocol__group_1ga0510b0a04d9cef144e4d9793310abccf)            | Endpoint transfer direction is OUT.
`define `[`USB_MAX_DESC_LEN`](#group__usb__protocol__group_1ga27dacd4e0b04d4ef7b8aadf6ea886f3c)            | Maximum length in bytes of a USB descriptor.
`define `[`USB_CONFIG_ATTR_MUST_SET`](#group__usb__protocol__group_1gac7063e965def0eaeb4d45a6f9048dc53)            | Must always be set.
`define `[`USB_CONFIG_ATTR_BUS_POWERED`](#group__usb__protocol__group_1ga10945c8d92454009444979c38b9d2cca)            | Bus-powered.
`define `[`USB_CONFIG_ATTR_SELF_POWERED`](#group__usb__protocol__group_1gaf1b445db8c331630bbedb383544ed80b)            | Self-powered.
`define `[`USB_CONFIG_ATTR_REMOTE_WAKEUP`](#group__usb__protocol__group_1gab8f513d1888f75d8e18960e1b1f3f747)            | remote wakeup supported
`define `[`USB_CONFIG_MAX_POWER`](#group__usb__protocol__group_1ga55d9db758a4f408eebf4b26c6001ac9b)            | Max power in mA.
`enum `[`usb_reqid`](#group__usb__protocol__group_1gab43332ff8dbad3dd3c8c882b1bd68a89)            | Standard USB requests (bRequest)
`enum `[`usb_device_status`](#group__usb__protocol__group_1ga5c6f61a70ef0fda1a1d6f9a34f2f0f1c)            | Standard USB device status flags.
`enum `[`usb_interface_status`](#group__usb__protocol__group_1ga61c6d9f1bcc6112f394333fac658d627)            | Standard USB Interface status flags.
`enum `[`usb_endpoint_status`](#group__usb__protocol__group_1gaf926ff975fcda57f214001b51f15092d)            | Standard USB endpoint status flags.
`enum `[`usb_device_feature`](#group__usb__protocol__group_1gab9975b89ad7079085d0300eab037c3ac)            | Standard USB device feature flags.
`enum `[`usb_device_hs_test_mode`](#group__usb__protocol__group_1ga9027bb283d3666e351fe5c403292cf2e)            | Test Mode possible on HS USB device.
`enum `[`usb_endpoint_feature`](#group__usb__protocol__group_1gac46bc23132eb03cefa56ba47024ced5d)            | Standard USB endpoint feature/status flags.
`enum `[`usb_test_mode_selector`](#group__usb__protocol__group_1gade3fc5b71e88ed167a8c8d67ee087db3)            | Standard USB Test Mode Selectors.
`enum `[`usb_descriptor_type`](#group__usb__protocol__group_1ga87d46dd117d939964c939f1518dec93f)            | Standard USB descriptor types.
`enum `[`usb_capability_type`](#group__usb__protocol__group_1gab4eef94a7d2be2570193c4f9400a6fa6)            | USB Device Capability types.
`enum `[`usb_capability_extension_attr`](#group__usb__protocol__group_1ga4fa8bfac1cf05037ee2ef05aaa190299)            | USB Device Capability - USB 2.0 Extension To fill bmAttributes field of usb_capa_ext_desc_t structure.
`enum `[`usb_ep_type`](#group__usb__protocol__group_1ga666def795a15032e5bf93a450f79113f)            | Standard USB endpoint transfer types.
`enum `[`usb_langid`](#group__usb__protocol__group_1ga1f92deaf695c06566999f0c5343978c1)            | Standard USB language IDs for string descriptors.
`struct `[`usb_setup_req_t`](#structusb__setup__req__t) | A USB Device SETUP request.
`struct `[`usb_dev_desc_t`](#structusb__dev__desc__t) | Standard USB device descriptor structure.
`struct `[`usb_dev_qual_desc_t`](#structusb__dev__qual__desc__t) | Standard USB device qualifier descriptor structure.
`struct `[`usb_dev_bos_desc_t`](#structusb__dev__bos__desc__t) | USB Device BOS descriptor structure.
`struct `[`usb_dev_capa_ext_desc_t`](#structusb__dev__capa__ext__desc__t) | USB Device Capabilities - USB 2.0 Extension Descriptor structure.
`struct `[`usb_dev_lpm_desc_t`](#structusb__dev__lpm__desc__t) | USB Device LPM Descriptor structure.
`struct `[`usb_association_desc_t`](#structusb__association__desc__t) | Standard USB Interface Association Descriptor structure.
`struct `[`usb_conf_desc_t`](#structusb__conf__desc__t) | Standard USB configuration descriptor structure.
`struct `[`usb_iad_desc_t`](#structusb__iad__desc__t) | Standard USB association descriptor structure.
`struct `[`usb_iface_desc_t`](#structusb__iface__desc__t) | Standard USB interface descriptor structure.
`struct `[`usb_ep_desc_t`](#structusb__ep__desc__t) | Standard USB endpoint descriptor structure.
`struct `[`usb_str_desc_t`](#structusb__str__desc__t) | A standard USB string descriptor structure.
`struct `[`usb_str_lgid_desc_t`](#structusb__str__lgid__desc__t) | 

## Members

#### `define `[`USB_V2_0`](#group__usb__protocol__group_1ga9bccec980a4f41a481b389b4f0c9c690) {#group__usb__protocol__group_1ga9bccec980a4f41a481b389b4f0c9c690}

Value for field bcdUSB.

USB Specification version 2.00

#### `define `[`USB_V2_1`](#group__usb__protocol__group_1ga98059f51cd65930412083d423a70dd17) {#group__usb__protocol__group_1ga98059f51cd65930412083d423a70dd17}

USB Specification version 2.01.

#### `define `[`USB_REQ_DIR_OUT`](#group__usb__protocol__group_1ga3fae7189eea003bf79ac2949b0f50584) {#group__usb__protocol__group_1ga3fae7189eea003bf79ac2949b0f50584}

USB request data transfer direction (bmRequestType)

Host to device

#### `define `[`USB_REQ_DIR_IN`](#group__usb__protocol__group_1ga3d3c24265f68a720887ae4ff7158d605) {#group__usb__protocol__group_1ga3d3c24265f68a720887ae4ff7158d605}

Device to host.

#### `define `[`USB_REQ_DIR_MASK`](#group__usb__protocol__group_1gac94f5ec9106e17f2e6d927eeac3d530f) {#group__usb__protocol__group_1gac94f5ec9106e17f2e6d927eeac3d530f}

Mask.

#### `define `[`USB_REQ_TYPE_STANDARD`](#group__usb__protocol__group_1ga3eb781776ab6dcbc6fa96e1b0ed18011) {#group__usb__protocol__group_1ga3eb781776ab6dcbc6fa96e1b0ed18011}

USB request types (bmRequestType)

Standard request

#### `define `[`USB_REQ_TYPE_CLASS`](#group__usb__protocol__group_1gaff9ee0044c6cb131b2908356adc37dff) {#group__usb__protocol__group_1gaff9ee0044c6cb131b2908356adc37dff}

Class-specific request.

#### `define `[`USB_REQ_TYPE_VENDOR`](#group__usb__protocol__group_1ga71855621792f72443ed5497b313a2517) {#group__usb__protocol__group_1ga71855621792f72443ed5497b313a2517}

Vendor-specific request.

#### `define `[`USB_REQ_TYPE_MASK`](#group__usb__protocol__group_1ga8be8332e2da1e54c74c5f2a2230b0a28) {#group__usb__protocol__group_1ga8be8332e2da1e54c74c5f2a2230b0a28}

Mask.

#### `define `[`USB_REQ_RECIP_DEVICE`](#group__usb__protocol__group_1ga65c1569b970837dd4a2ad8e1b4097589) {#group__usb__protocol__group_1ga65c1569b970837dd4a2ad8e1b4097589}

USB recipient codes (bmRequestType)

Recipient device

#### `define `[`USB_REQ_RECIP_INTERFACE`](#group__usb__protocol__group_1gad3d0e7d70c610967cc2ee12c5298ac69) {#group__usb__protocol__group_1gad3d0e7d70c610967cc2ee12c5298ac69}

Recipient interface.

#### `define `[`USB_REQ_RECIP_ENDPOINT`](#group__usb__protocol__group_1ga1be00350ff83d022d41b4eae81f1e2b2) {#group__usb__protocol__group_1ga1be00350ff83d022d41b4eae81f1e2b2}

Recipient endpoint.

#### `define `[`USB_REQ_RECIP_OTHER`](#group__usb__protocol__group_1gabb5706061604f770d2ce1f3891ab0296) {#group__usb__protocol__group_1gabb5706061604f770d2ce1f3891ab0296}

Recipient other.

#### `define `[`USB_REQ_RECIP_MASK`](#group__usb__protocol__group_1gab1738c19d49fe1d4c7edccff90e9e9e4) {#group__usb__protocol__group_1gab1738c19d49fe1d4c7edccff90e9e9e4}

Mask.

#### `define `[`HIRD_50_US`](#group__usb__protocol__group_1ga63ce14c89bdb5349988cb983b7176740) {#group__usb__protocol__group_1ga63ce14c89bdb5349988cb983b7176740}

#### `define `[`HIRD_125_US`](#group__usb__protocol__group_1ga8fa50bfccd00843cd32719521720f7f6) {#group__usb__protocol__group_1ga8fa50bfccd00843cd32719521720f7f6}

#### `define `[`HIRD_200_US`](#group__usb__protocol__group_1gad6f9ff2585cbc2b0ca161ee12a11b154) {#group__usb__protocol__group_1gad6f9ff2585cbc2b0ca161ee12a11b154}

#### `define `[`HIRD_275_US`](#group__usb__protocol__group_1ga51c55e5d7938a80a53084b5a2a93b9b3) {#group__usb__protocol__group_1ga51c55e5d7938a80a53084b5a2a93b9b3}

#### `define `[`HIRD_350_US`](#group__usb__protocol__group_1ga28a9220cf691f45fa880638ad92ed95a) {#group__usb__protocol__group_1ga28a9220cf691f45fa880638ad92ed95a}

#### `define `[`HIRD_425_US`](#group__usb__protocol__group_1gab0f175ff5b6a35c08d4730f3b82e3290) {#group__usb__protocol__group_1gab0f175ff5b6a35c08d4730f3b82e3290}

#### `define `[`HIRD_500_US`](#group__usb__protocol__group_1gaf75c36a22358dbe9d27fa2122d39ac32) {#group__usb__protocol__group_1gaf75c36a22358dbe9d27fa2122d39ac32}

#### `define `[`HIRD_575_US`](#group__usb__protocol__group_1ga27244f075c4ae2c34bcdeecca8921e9d) {#group__usb__protocol__group_1ga27244f075c4ae2c34bcdeecca8921e9d}

#### `define `[`HIRD_650_US`](#group__usb__protocol__group_1ga33e1236c9694d97c574677ed36da8ce4) {#group__usb__protocol__group_1ga33e1236c9694d97c574677ed36da8ce4}

#### `define `[`HIRD_725_US`](#group__usb__protocol__group_1gab1cfbd6207cc526b33a65593379f1802) {#group__usb__protocol__group_1gab1cfbd6207cc526b33a65593379f1802}

#### `define `[`HIRD_800_US`](#group__usb__protocol__group_1gaec9c3475ae7a1a2deefdb7f844ab25b4) {#group__usb__protocol__group_1gaec9c3475ae7a1a2deefdb7f844ab25b4}

#### `define `[`HIRD_875_US`](#group__usb__protocol__group_1ga39eaf9efa2c721560ae7e6d4463ed353) {#group__usb__protocol__group_1ga39eaf9efa2c721560ae7e6d4463ed353}

#### `define `[`HIRD_950_US`](#group__usb__protocol__group_1ga6a950e4e5666cd014db36bd4971ac888) {#group__usb__protocol__group_1ga6a950e4e5666cd014db36bd4971ac888}

#### `define `[`HIRD_1025_US`](#group__usb__protocol__group_1ga07cfb9848da18f98190ff86ca5349b53) {#group__usb__protocol__group_1ga07cfb9848da18f98190ff86ca5349b53}

#### `define `[`HIRD_1100_US`](#group__usb__protocol__group_1ga52b2c19a0df1c72ed04a97ccb3b9152e) {#group__usb__protocol__group_1ga52b2c19a0df1c72ed04a97ccb3b9152e}

#### `define `[`HIRD_1175_US`](#group__usb__protocol__group_1ga29284c56fb4827b69c00332b7a4fdb76) {#group__usb__protocol__group_1ga29284c56fb4827b69c00332b7a4fdb76}

#### `define `[`USB_LPM_ATTRIBUT_BLINKSTATE_MASK`](#group__usb__protocol__group_1gaf39d50c3bb01f68fa434e7fdf3a44e22) {#group__usb__protocol__group_1gaf39d50c3bb01f68fa434e7fdf3a44e22}

Fields definition from a LPM TOKEN

#### `define `[`USB_LPM_ATTRIBUT_FIRD_MASK`](#group__usb__protocol__group_1gaf53a7676592b02f9bb846e1062af463c) {#group__usb__protocol__group_1gaf53a7676592b02f9bb846e1062af463c}

#### `define `[`USB_LPM_ATTRIBUT_REMOTEWAKE_MASK`](#group__usb__protocol__group_1ga9c1618c348394534d968097c8d76c092) {#group__usb__protocol__group_1ga9c1618c348394534d968097c8d76c092}

#### `define `[`USB_LPM_ATTRIBUT_BLINKSTATE`](#group__usb__protocol__group_1ga1deb3dda1fc39b7425359c72eb548b0d) {#group__usb__protocol__group_1ga1deb3dda1fc39b7425359c72eb548b0d}

#### `define `[`USB_LPM_ATTRIBUT_FIRD`](#group__usb__protocol__group_1ga0eb84fe948d5e4650a39d6081b959c70) {#group__usb__protocol__group_1ga0eb84fe948d5e4650a39d6081b959c70}

#### `define `[`USB_LPM_ATTRIBUT_REMOTEWAKE`](#group__usb__protocol__group_1ga7482138e5ce2d2ec9482bcd5dbd9bd64) {#group__usb__protocol__group_1ga7482138e5ce2d2ec9482bcd5dbd9bd64}

#### `define `[`USB_LPM_ATTRIBUT_BLINKSTATE_L1`](#group__usb__protocol__group_1ga02be6765d15e86d37fd66ce6862a16fc) {#group__usb__protocol__group_1ga02be6765d15e86d37fd66ce6862a16fc}

#### `define `[`USB_EP_ADDR_MASK`](#group__usb__protocol__group_1ga0316d8f43a1648b76df257332b26aeb9) {#group__usb__protocol__group_1ga0316d8f43a1648b76df257332b26aeb9}

Mask selecting the index part of an endpoint address.

#### `define `[`USB_EP_DIR_IN`](#group__usb__protocol__group_1gaae8411e95f26738326bc25a0161dde99) {#group__usb__protocol__group_1gaae8411e95f26738326bc25a0161dde99}

Endpoint transfer direction is IN.

#### `define `[`USB_EP_DIR_OUT`](#group__usb__protocol__group_1ga0510b0a04d9cef144e4d9793310abccf) {#group__usb__protocol__group_1ga0510b0a04d9cef144e4d9793310abccf}

Endpoint transfer direction is OUT.

#### `define `[`USB_MAX_DESC_LEN`](#group__usb__protocol__group_1ga27dacd4e0b04d4ef7b8aadf6ea886f3c) {#group__usb__protocol__group_1ga27dacd4e0b04d4ef7b8aadf6ea886f3c}

Maximum length in bytes of a USB descriptor.

The maximum length of a USB descriptor is limited by the 8-bit bLength field.

#### `define `[`USB_CONFIG_ATTR_MUST_SET`](#group__usb__protocol__group_1gac7063e965def0eaeb4d45a6f9048dc53) {#group__usb__protocol__group_1gac7063e965def0eaeb4d45a6f9048dc53}

Must always be set.

#### `define `[`USB_CONFIG_ATTR_BUS_POWERED`](#group__usb__protocol__group_1ga10945c8d92454009444979c38b9d2cca) {#group__usb__protocol__group_1ga10945c8d92454009444979c38b9d2cca}

Bus-powered.

#### `define `[`USB_CONFIG_ATTR_SELF_POWERED`](#group__usb__protocol__group_1gaf1b445db8c331630bbedb383544ed80b) {#group__usb__protocol__group_1gaf1b445db8c331630bbedb383544ed80b}

Self-powered.

#### `define `[`USB_CONFIG_ATTR_REMOTE_WAKEUP`](#group__usb__protocol__group_1gab8f513d1888f75d8e18960e1b1f3f747) {#group__usb__protocol__group_1gab8f513d1888f75d8e18960e1b1f3f747}

remote wakeup supported

#### `define `[`USB_CONFIG_MAX_POWER`](#group__usb__protocol__group_1ga55d9db758a4f408eebf4b26c6001ac9b) {#group__usb__protocol__group_1ga55d9db758a4f408eebf4b26c6001ac9b}

Max power in mA.

#### `enum `[`usb_reqid`](#group__usb__protocol__group_1gab43332ff8dbad3dd3c8c882b1bd68a89) {#group__usb__protocol__group_1gab43332ff8dbad3dd3c8c882b1bd68a89}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_REQ_GET_STATUS            | 
USB_REQ_CLEAR_FEATURE            | 
USB_REQ_SET_FEATURE            | 
USB_REQ_SET_ADDRESS            | 
USB_REQ_GET_DESCRIPTOR            | 
USB_REQ_SET_DESCRIPTOR            | 
USB_REQ_GET_CONFIGURATION            | 
USB_REQ_SET_CONFIGURATION            | 
USB_REQ_GET_INTERFACE            | 
USB_REQ_SET_INTERFACE            | 
USB_REQ_SYNCH_FRAME            | 

Standard USB requests (bRequest)

#### `enum `[`usb_device_status`](#group__usb__protocol__group_1ga5c6f61a70ef0fda1a1d6f9a34f2f0f1c) {#group__usb__protocol__group_1ga5c6f61a70ef0fda1a1d6f9a34f2f0f1c}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DEV_STATUS_BUS_POWERED            | 
USB_DEV_STATUS_SELF_POWERED            | 
USB_DEV_STATUS_REMOTEWAKEUP            | 

Standard USB device status flags.

#### `enum `[`usb_interface_status`](#group__usb__protocol__group_1ga61c6d9f1bcc6112f394333fac658d627) {#group__usb__protocol__group_1ga61c6d9f1bcc6112f394333fac658d627}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_IFACE_STATUS_RESERVED            | 

Standard USB Interface status flags.

#### `enum `[`usb_endpoint_status`](#group__usb__protocol__group_1gaf926ff975fcda57f214001b51f15092d) {#group__usb__protocol__group_1gaf926ff975fcda57f214001b51f15092d}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_EP_STATUS_HALTED            | 

Standard USB endpoint status flags.

#### `enum `[`usb_device_feature`](#group__usb__protocol__group_1gab9975b89ad7079085d0300eab037c3ac) {#group__usb__protocol__group_1gab9975b89ad7079085d0300eab037c3ac}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DEV_FEATURE_REMOTE_WAKEUP            | Remote wakeup enabled.
USB_DEV_FEATURE_TEST_MODE            | USB test mode.
USB_DEV_FEATURE_OTG_B_HNP_ENABLE            | 
USB_DEV_FEATURE_OTG_A_HNP_SUPPORT            | 
USB_DEV_FEATURE_OTG_A_ALT_HNP_SUPPORT            | 

Standard USB device feature flags.

valid for SetFeature request.

#### `enum `[`usb_device_hs_test_mode`](#group__usb__protocol__group_1ga9027bb283d3666e351fe5c403292cf2e) {#group__usb__protocol__group_1ga9027bb283d3666e351fe5c403292cf2e}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DEV_TEST_MODE_J            | 
USB_DEV_TEST_MODE_K            | 
USB_DEV_TEST_MODE_SE0_NAK            | 
USB_DEV_TEST_MODE_PACKET            | 
USB_DEV_TEST_MODE_FORCE_ENABLE            | 

Test Mode possible on HS USB device.

valid for USB_DEV_FEATURE_TEST_MODE request.

#### `enum `[`usb_endpoint_feature`](#group__usb__protocol__group_1gac46bc23132eb03cefa56ba47024ced5d) {#group__usb__protocol__group_1gac46bc23132eb03cefa56ba47024ced5d}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_EP_FEATURE_HALT            | 

Standard USB endpoint feature/status flags.

#### `enum `[`usb_test_mode_selector`](#group__usb__protocol__group_1gade3fc5b71e88ed167a8c8d67ee087db3) {#group__usb__protocol__group_1gade3fc5b71e88ed167a8c8d67ee087db3}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_TEST_J            | 
USB_TEST_K            | 
USB_TEST_SE0_NAK            | 
USB_TEST_PACKET            | 
USB_TEST_FORCE_ENABLE            | 

Standard USB Test Mode Selectors.

#### `enum `[`usb_descriptor_type`](#group__usb__protocol__group_1ga87d46dd117d939964c939f1518dec93f) {#group__usb__protocol__group_1ga87d46dd117d939964c939f1518dec93f}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DT_DEVICE            | 
USB_DT_CONFIGURATION            | 
USB_DT_STRING            | 
USB_DT_INTERFACE            | 
USB_DT_ENDPOINT            | 
USB_DT_DEVICE_QUALIFIER            | 
USB_DT_OTHER_SPEED_CONFIGURATION            | 
USB_DT_INTERFACE_POWER            | 
USB_DT_OTG            | 
USB_DT_IAD            | 
USB_DT_BOS            | 
USB_DT_DEVICE_CAPABILITY            | 

Standard USB descriptor types.

#### `enum `[`usb_capability_type`](#group__usb__protocol__group_1gab4eef94a7d2be2570193c4f9400a6fa6) {#group__usb__protocol__group_1gab4eef94a7d2be2570193c4f9400a6fa6}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DC_USB20_EXTENSION            | 

USB Device Capability types.

#### `enum `[`usb_capability_extension_attr`](#group__usb__protocol__group_1ga4fa8bfac1cf05037ee2ef05aaa190299) {#group__usb__protocol__group_1ga4fa8bfac1cf05037ee2ef05aaa190299}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DC_EXT_LPM            | 

USB Device Capability - USB 2.0 Extension To fill bmAttributes field of usb_capa_ext_desc_t structure.

#### `enum `[`usb_ep_type`](#group__usb__protocol__group_1ga666def795a15032e5bf93a450f79113f) {#group__usb__protocol__group_1ga666def795a15032e5bf93a450f79113f}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_EP_TYPE_CONTROL            | 
USB_EP_TYPE_ISOCHRONOUS            | 
USB_EP_TYPE_BULK            | 
USB_EP_TYPE_INTERRUPT            | 
USB_EP_TYPE_MASK            | 

Standard USB endpoint transfer types.

#### `enum `[`usb_langid`](#group__usb__protocol__group_1ga1f92deaf695c06566999f0c5343978c1) {#group__usb__protocol__group_1ga1f92deaf695c06566999f0c5343978c1}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_LANGID_EN_US            | English (United States)

Standard USB language IDs for string descriptors.

# struct `usb_setup_req_t` {#structusb__setup__req__t}

A USB Device SETUP request.

The data payload of SETUP packets always follows this structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bmRequestType`](#structusb__setup__req__t_1abea120ea756eb0abdb8aafb8713f61f4) | 
`public uint8_t `[`bRequest`](#structusb__setup__req__t_1a1e7be110861bd4ff75c86d5214f31543) | 
`public le16_t `[`wValue`](#structusb__setup__req__t_1a3f4a2e5f861f69f5ff919187c77997df) | 
`public le16_t `[`wIndex`](#structusb__setup__req__t_1ab714cf061bdd655bcf61fdd06e79582f) | 
`public le16_t `[`wLength`](#structusb__setup__req__t_1aa89ae35360f472f2cf0ea6374dde429e) | 

## Members

#### `public uint8_t `[`bmRequestType`](#structusb__setup__req__t_1abea120ea756eb0abdb8aafb8713f61f4) {#structusb__setup__req__t_1abea120ea756eb0abdb8aafb8713f61f4}

#### `public uint8_t `[`bRequest`](#structusb__setup__req__t_1a1e7be110861bd4ff75c86d5214f31543) {#structusb__setup__req__t_1a1e7be110861bd4ff75c86d5214f31543}

#### `public le16_t `[`wValue`](#structusb__setup__req__t_1a3f4a2e5f861f69f5ff919187c77997df) {#structusb__setup__req__t_1a3f4a2e5f861f69f5ff919187c77997df}

#### `public le16_t `[`wIndex`](#structusb__setup__req__t_1ab714cf061bdd655bcf61fdd06e79582f) {#structusb__setup__req__t_1ab714cf061bdd655bcf61fdd06e79582f}

#### `public le16_t `[`wLength`](#structusb__setup__req__t_1aa89ae35360f472f2cf0ea6374dde429e) {#structusb__setup__req__t_1aa89ae35360f472f2cf0ea6374dde429e}

# struct `usb_dev_desc_t` {#structusb__dev__desc__t}

Standard USB device descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__dev__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__dev__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public le16_t `[`bcdUSB`](#structusb__dev__desc__t_1a56cc8699d8752ad2ed929093577b524d) | 
`public uint8_t `[`bDeviceClass`](#structusb__dev__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4) | 
`public uint8_t `[`bDeviceSubClass`](#structusb__dev__desc__t_1a260eec0b4e7279e6ecae808ca34c2604) | 
`public uint8_t `[`bDeviceProtocol`](#structusb__dev__desc__t_1a44e204b5f7158f4048edcb944351ce27) | 
`public uint8_t `[`bMaxPacketSize0`](#structusb__dev__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2) | 
`public le16_t `[`idVendor`](#structusb__dev__desc__t_1a936f0362af0151f7370e3d18cdaa567c) | 
`public le16_t `[`idProduct`](#structusb__dev__desc__t_1ae8d97f443c3dc80e3f1d37f3d45c6d57) | 
`public le16_t `[`bcdDevice`](#structusb__dev__desc__t_1a55f0af10047f350be74d3e8c3884c035) | 
`public uint8_t `[`iManufacturer`](#structusb__dev__desc__t_1a7ee6ae41b483f3c49d1ddb39a83a8a43) | 
`public uint8_t `[`iProduct`](#structusb__dev__desc__t_1a77c33850b90ff7617243c40ce61d9168) | 
`public uint8_t `[`iSerialNumber`](#structusb__dev__desc__t_1aeb129fc0d41494f69369da70d73eac11) | 
`public uint8_t `[`bNumConfigurations`](#structusb__dev__desc__t_1abde4f60e84b2d9b10c27aa23bae62595) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__dev__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__dev__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__dev__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__dev__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public le16_t `[`bcdUSB`](#structusb__dev__desc__t_1a56cc8699d8752ad2ed929093577b524d) {#structusb__dev__desc__t_1a56cc8699d8752ad2ed929093577b524d}

#### `public uint8_t `[`bDeviceClass`](#structusb__dev__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4) {#structusb__dev__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4}

#### `public uint8_t `[`bDeviceSubClass`](#structusb__dev__desc__t_1a260eec0b4e7279e6ecae808ca34c2604) {#structusb__dev__desc__t_1a260eec0b4e7279e6ecae808ca34c2604}

#### `public uint8_t `[`bDeviceProtocol`](#structusb__dev__desc__t_1a44e204b5f7158f4048edcb944351ce27) {#structusb__dev__desc__t_1a44e204b5f7158f4048edcb944351ce27}

#### `public uint8_t `[`bMaxPacketSize0`](#structusb__dev__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2) {#structusb__dev__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2}

#### `public le16_t `[`idVendor`](#structusb__dev__desc__t_1a936f0362af0151f7370e3d18cdaa567c) {#structusb__dev__desc__t_1a936f0362af0151f7370e3d18cdaa567c}

#### `public le16_t `[`idProduct`](#structusb__dev__desc__t_1ae8d97f443c3dc80e3f1d37f3d45c6d57) {#structusb__dev__desc__t_1ae8d97f443c3dc80e3f1d37f3d45c6d57}

#### `public le16_t `[`bcdDevice`](#structusb__dev__desc__t_1a55f0af10047f350be74d3e8c3884c035) {#structusb__dev__desc__t_1a55f0af10047f350be74d3e8c3884c035}

#### `public uint8_t `[`iManufacturer`](#structusb__dev__desc__t_1a7ee6ae41b483f3c49d1ddb39a83a8a43) {#structusb__dev__desc__t_1a7ee6ae41b483f3c49d1ddb39a83a8a43}

#### `public uint8_t `[`iProduct`](#structusb__dev__desc__t_1a77c33850b90ff7617243c40ce61d9168) {#structusb__dev__desc__t_1a77c33850b90ff7617243c40ce61d9168}

#### `public uint8_t `[`iSerialNumber`](#structusb__dev__desc__t_1aeb129fc0d41494f69369da70d73eac11) {#structusb__dev__desc__t_1aeb129fc0d41494f69369da70d73eac11}

#### `public uint8_t `[`bNumConfigurations`](#structusb__dev__desc__t_1abde4f60e84b2d9b10c27aa23bae62595) {#structusb__dev__desc__t_1abde4f60e84b2d9b10c27aa23bae62595}

# struct `usb_dev_qual_desc_t` {#structusb__dev__qual__desc__t}

Standard USB device qualifier descriptor structure.

This descriptor contains information about the device when running at the "other" speed (i.e. if the device is currently operating at high speed, this descriptor can be used to determine what would change if the device was operating at full speed.)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__dev__qual__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__dev__qual__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public le16_t `[`bcdUSB`](#structusb__dev__qual__desc__t_1a56cc8699d8752ad2ed929093577b524d) | 
`public uint8_t `[`bDeviceClass`](#structusb__dev__qual__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4) | 
`public uint8_t `[`bDeviceSubClass`](#structusb__dev__qual__desc__t_1a260eec0b4e7279e6ecae808ca34c2604) | 
`public uint8_t `[`bDeviceProtocol`](#structusb__dev__qual__desc__t_1a44e204b5f7158f4048edcb944351ce27) | 
`public uint8_t `[`bMaxPacketSize0`](#structusb__dev__qual__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2) | 
`public uint8_t `[`bNumConfigurations`](#structusb__dev__qual__desc__t_1abde4f60e84b2d9b10c27aa23bae62595) | 
`public uint8_t `[`bReserved`](#structusb__dev__qual__desc__t_1ab8303f57004812636de0daff446b975a) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__dev__qual__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__dev__qual__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__dev__qual__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__dev__qual__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public le16_t `[`bcdUSB`](#structusb__dev__qual__desc__t_1a56cc8699d8752ad2ed929093577b524d) {#structusb__dev__qual__desc__t_1a56cc8699d8752ad2ed929093577b524d}

#### `public uint8_t `[`bDeviceClass`](#structusb__dev__qual__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4) {#structusb__dev__qual__desc__t_1ab8e1b1fca77a607c39bba2278623d4f4}

#### `public uint8_t `[`bDeviceSubClass`](#structusb__dev__qual__desc__t_1a260eec0b4e7279e6ecae808ca34c2604) {#structusb__dev__qual__desc__t_1a260eec0b4e7279e6ecae808ca34c2604}

#### `public uint8_t `[`bDeviceProtocol`](#structusb__dev__qual__desc__t_1a44e204b5f7158f4048edcb944351ce27) {#structusb__dev__qual__desc__t_1a44e204b5f7158f4048edcb944351ce27}

#### `public uint8_t `[`bMaxPacketSize0`](#structusb__dev__qual__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2) {#structusb__dev__qual__desc__t_1a93b2c926b005917cdf2b5e7e4b3f80a2}

#### `public uint8_t `[`bNumConfigurations`](#structusb__dev__qual__desc__t_1abde4f60e84b2d9b10c27aa23bae62595) {#structusb__dev__qual__desc__t_1abde4f60e84b2d9b10c27aa23bae62595}

#### `public uint8_t `[`bReserved`](#structusb__dev__qual__desc__t_1ab8303f57004812636de0daff446b975a) {#structusb__dev__qual__desc__t_1ab8303f57004812636de0daff446b975a}

# struct `usb_dev_bos_desc_t` {#structusb__dev__bos__desc__t}

USB Device BOS descriptor structure.

The BOS descriptor (Binary device Object Store) defines a root descriptor that is similar to the configuration descriptor, and is the base descriptor for accessing a family of related descriptors. A host can read a BOS descriptor and learn from the wTotalLength field the entire size of the device-level descriptor set, or it can read in the entire BOS descriptor set of device capabilities. The host accesses this descriptor using the GetDescriptor() request. The descriptor type in the GetDescriptor() request is set to BOS.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__dev__bos__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__dev__bos__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public le16_t `[`wTotalLength`](#structusb__dev__bos__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7) | 
`public uint8_t `[`bNumDeviceCaps`](#structusb__dev__bos__desc__t_1aca1d3672075c130816f54ef305a5aa50) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__dev__bos__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__dev__bos__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__dev__bos__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__dev__bos__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public le16_t `[`wTotalLength`](#structusb__dev__bos__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7) {#structusb__dev__bos__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7}

#### `public uint8_t `[`bNumDeviceCaps`](#structusb__dev__bos__desc__t_1aca1d3672075c130816f54ef305a5aa50) {#structusb__dev__bos__desc__t_1aca1d3672075c130816f54ef305a5aa50}

# struct `usb_dev_capa_ext_desc_t` {#structusb__dev__capa__ext__desc__t}

USB Device Capabilities - USB 2.0 Extension Descriptor structure.

Defines the set of USB 1.1-specific device level capabilities.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__dev__capa__ext__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__dev__capa__ext__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public uint8_t `[`bDevCapabilityType`](#structusb__dev__capa__ext__desc__t_1a1be7f18a35c3e636c095752fbb2149c0) | 
`public le32_t `[`bmAttributes`](#structusb__dev__capa__ext__desc__t_1aecf9cc6699e2f1905e31e11484095def) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__dev__capa__ext__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__dev__capa__ext__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__dev__capa__ext__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__dev__capa__ext__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public uint8_t `[`bDevCapabilityType`](#structusb__dev__capa__ext__desc__t_1a1be7f18a35c3e636c095752fbb2149c0) {#structusb__dev__capa__ext__desc__t_1a1be7f18a35c3e636c095752fbb2149c0}

#### `public le32_t `[`bmAttributes`](#structusb__dev__capa__ext__desc__t_1aecf9cc6699e2f1905e31e11484095def) {#structusb__dev__capa__ext__desc__t_1aecf9cc6699e2f1905e31e11484095def}

# struct `usb_dev_lpm_desc_t` {#structusb__dev__lpm__desc__t}

USB Device LPM Descriptor structure.

The BOS descriptor and capabilities descriptors for LPM.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_dev_bos_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__dev__bos__desc__t)` `[`bos`](#structusb__dev__lpm__desc__t_1aa1445afe8acf8bc5d942305edeb6dfd1) | 
`public `[`usb_dev_capa_ext_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__dev__capa__ext__desc__t)` `[`capa_ext`](#structusb__dev__lpm__desc__t_1a260a9ee22980a1306d3dcff998fd48c7) | 

## Members

#### `public `[`usb_dev_bos_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__dev__bos__desc__t)` `[`bos`](#structusb__dev__lpm__desc__t_1aa1445afe8acf8bc5d942305edeb6dfd1) {#structusb__dev__lpm__desc__t_1aa1445afe8acf8bc5d942305edeb6dfd1}

#### `public `[`usb_dev_capa_ext_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__dev__capa__ext__desc__t)` `[`capa_ext`](#structusb__dev__lpm__desc__t_1a260a9ee22980a1306d3dcff998fd48c7) {#structusb__dev__lpm__desc__t_1a260a9ee22980a1306d3dcff998fd48c7}

# struct `usb_association_desc_t` {#structusb__association__desc__t}

Standard USB Interface Association Descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__association__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | size of this descriptor in bytes
`public uint8_t `[`bDescriptorType`](#structusb__association__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | INTERFACE descriptor type.
`public uint8_t `[`bFirstInterface`](#structusb__association__desc__t_1a85323ed61eb948bdea147d67e01ddc2d) | Number of interface.
`public uint8_t `[`bInterfaceCount`](#structusb__association__desc__t_1a9674bda677f9898106ec2b6fe5f5723d) | value to select alternate setting
`public uint8_t `[`bFunctionClass`](#structusb__association__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704) | Class code assigned by the USB.
`public uint8_t `[`bFunctionSubClass`](#structusb__association__desc__t_1ab25f749c091ce99b6868c949c4e45bc3) | Sub-class code assigned by the USB.
`public uint8_t `[`bFunctionProtocol`](#structusb__association__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c) | Protocol code assigned by the USB.
`public uint8_t `[`iFunction`](#structusb__association__desc__t_1ab84d4b3bced6c09c62350d56fd69d226) | Index of string descriptor.

## Members

#### `public uint8_t `[`bLength`](#structusb__association__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__association__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

size of this descriptor in bytes

#### `public uint8_t `[`bDescriptorType`](#structusb__association__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__association__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

INTERFACE descriptor type.

#### `public uint8_t `[`bFirstInterface`](#structusb__association__desc__t_1a85323ed61eb948bdea147d67e01ddc2d) {#structusb__association__desc__t_1a85323ed61eb948bdea147d67e01ddc2d}

Number of interface.

#### `public uint8_t `[`bInterfaceCount`](#structusb__association__desc__t_1a9674bda677f9898106ec2b6fe5f5723d) {#structusb__association__desc__t_1a9674bda677f9898106ec2b6fe5f5723d}

value to select alternate setting

#### `public uint8_t `[`bFunctionClass`](#structusb__association__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704) {#structusb__association__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704}

Class code assigned by the USB.

#### `public uint8_t `[`bFunctionSubClass`](#structusb__association__desc__t_1ab25f749c091ce99b6868c949c4e45bc3) {#structusb__association__desc__t_1ab25f749c091ce99b6868c949c4e45bc3}

Sub-class code assigned by the USB.

#### `public uint8_t `[`bFunctionProtocol`](#structusb__association__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c) {#structusb__association__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c}

Protocol code assigned by the USB.

#### `public uint8_t `[`iFunction`](#structusb__association__desc__t_1ab84d4b3bced6c09c62350d56fd69d226) {#structusb__association__desc__t_1ab84d4b3bced6c09c62350d56fd69d226}

Index of string descriptor.

# struct `usb_conf_desc_t` {#structusb__conf__desc__t}

Standard USB configuration descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__conf__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__conf__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public le16_t `[`wTotalLength`](#structusb__conf__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7) | 
`public uint8_t `[`bNumInterfaces`](#structusb__conf__desc__t_1a1ad144333e75b0d867e72f8a337cd510) | 
`public uint8_t `[`bConfigurationValue`](#structusb__conf__desc__t_1aecb9ae30bca0b044d2941120f21c2b29) | 
`public uint8_t `[`iConfiguration`](#structusb__conf__desc__t_1a5ad4440b4eb1935d66b154d274f8a272) | 
`public uint8_t `[`bmAttributes`](#structusb__conf__desc__t_1ae7c63b4cda39953db5710012a5d91c6f) | 
`public uint8_t `[`bMaxPower`](#structusb__conf__desc__t_1ad3ac74420252d7a6a03e1e9d7b481f9b) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__conf__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__conf__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__conf__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__conf__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public le16_t `[`wTotalLength`](#structusb__conf__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7) {#structusb__conf__desc__t_1aef0f5fd0160660a30f12e0c82a73f3d7}

#### `public uint8_t `[`bNumInterfaces`](#structusb__conf__desc__t_1a1ad144333e75b0d867e72f8a337cd510) {#structusb__conf__desc__t_1a1ad144333e75b0d867e72f8a337cd510}

#### `public uint8_t `[`bConfigurationValue`](#structusb__conf__desc__t_1aecb9ae30bca0b044d2941120f21c2b29) {#structusb__conf__desc__t_1aecb9ae30bca0b044d2941120f21c2b29}

#### `public uint8_t `[`iConfiguration`](#structusb__conf__desc__t_1a5ad4440b4eb1935d66b154d274f8a272) {#structusb__conf__desc__t_1a5ad4440b4eb1935d66b154d274f8a272}

#### `public uint8_t `[`bmAttributes`](#structusb__conf__desc__t_1ae7c63b4cda39953db5710012a5d91c6f) {#structusb__conf__desc__t_1ae7c63b4cda39953db5710012a5d91c6f}

#### `public uint8_t `[`bMaxPower`](#structusb__conf__desc__t_1ad3ac74420252d7a6a03e1e9d7b481f9b) {#structusb__conf__desc__t_1ad3ac74420252d7a6a03e1e9d7b481f9b}

# struct `usb_iad_desc_t` {#structusb__iad__desc__t}

Standard USB association descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__iad__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | Size of this descriptor in bytes.
`public uint8_t `[`bDescriptorType`](#structusb__iad__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | Interface descriptor type.
`public uint8_t `[`bFirstInterface`](#structusb__iad__desc__t_1a85323ed61eb948bdea147d67e01ddc2d) | Number of interface.
`public uint8_t `[`bInterfaceCount`](#structusb__iad__desc__t_1a9674bda677f9898106ec2b6fe5f5723d) | value to select alternate setting
`public uint8_t `[`bFunctionClass`](#structusb__iad__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704) | Class code assigned by the USB.
`public uint8_t `[`bFunctionSubClass`](#structusb__iad__desc__t_1ab25f749c091ce99b6868c949c4e45bc3) | Sub-class code assigned by the USB.
`public uint8_t `[`bFunctionProtocol`](#structusb__iad__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c) | Protocol code assigned by the USB.
`public uint8_t `[`iFunction`](#structusb__iad__desc__t_1ab84d4b3bced6c09c62350d56fd69d226) | Index of string descriptor.

## Members

#### `public uint8_t `[`bLength`](#structusb__iad__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__iad__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

Size of this descriptor in bytes.

#### `public uint8_t `[`bDescriptorType`](#structusb__iad__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__iad__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

Interface descriptor type.

#### `public uint8_t `[`bFirstInterface`](#structusb__iad__desc__t_1a85323ed61eb948bdea147d67e01ddc2d) {#structusb__iad__desc__t_1a85323ed61eb948bdea147d67e01ddc2d}

Number of interface.

#### `public uint8_t `[`bInterfaceCount`](#structusb__iad__desc__t_1a9674bda677f9898106ec2b6fe5f5723d) {#structusb__iad__desc__t_1a9674bda677f9898106ec2b6fe5f5723d}

value to select alternate setting

#### `public uint8_t `[`bFunctionClass`](#structusb__iad__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704) {#structusb__iad__desc__t_1a1ed25bc3320ca90e4d3acb4410aea704}

Class code assigned by the USB.

#### `public uint8_t `[`bFunctionSubClass`](#structusb__iad__desc__t_1ab25f749c091ce99b6868c949c4e45bc3) {#structusb__iad__desc__t_1ab25f749c091ce99b6868c949c4e45bc3}

Sub-class code assigned by the USB.

#### `public uint8_t `[`bFunctionProtocol`](#structusb__iad__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c) {#structusb__iad__desc__t_1a2b3b905ab34e6e28b57c3ddc51b3487c}

Protocol code assigned by the USB.

#### `public uint8_t `[`iFunction`](#structusb__iad__desc__t_1ab84d4b3bced6c09c62350d56fd69d226) {#structusb__iad__desc__t_1ab84d4b3bced6c09c62350d56fd69d226}

Index of string descriptor.

# struct `usb_iface_desc_t` {#structusb__iface__desc__t}

Standard USB interface descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__iface__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__iface__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public uint8_t `[`bInterfaceNumber`](#structusb__iface__desc__t_1a3d66d88c5e928462aef62633449f1eb0) | 
`public uint8_t `[`bAlternateSetting`](#structusb__iface__desc__t_1a4cdd7aab185365e51a1e722f43073b8c) | 
`public uint8_t `[`bNumEndpoints`](#structusb__iface__desc__t_1acec2e7d68271baace354a0539f3d7e3d) | 
`public uint8_t `[`bInterfaceClass`](#structusb__iface__desc__t_1ae899427763e325f03241afc69a6e1ea0) | 
`public uint8_t `[`bInterfaceSubClass`](#structusb__iface__desc__t_1a3b3919d1203cd42550d77287f7585595) | 
`public uint8_t `[`bInterfaceProtocol`](#structusb__iface__desc__t_1a6872c4ec51fd061e2955f84d97bea2a7) | 
`public uint8_t `[`iInterface`](#structusb__iface__desc__t_1a2e4535908d90f195c6347a91e15b544d) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__iface__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__iface__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__iface__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__iface__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public uint8_t `[`bInterfaceNumber`](#structusb__iface__desc__t_1a3d66d88c5e928462aef62633449f1eb0) {#structusb__iface__desc__t_1a3d66d88c5e928462aef62633449f1eb0}

#### `public uint8_t `[`bAlternateSetting`](#structusb__iface__desc__t_1a4cdd7aab185365e51a1e722f43073b8c) {#structusb__iface__desc__t_1a4cdd7aab185365e51a1e722f43073b8c}

#### `public uint8_t `[`bNumEndpoints`](#structusb__iface__desc__t_1acec2e7d68271baace354a0539f3d7e3d) {#structusb__iface__desc__t_1acec2e7d68271baace354a0539f3d7e3d}

#### `public uint8_t `[`bInterfaceClass`](#structusb__iface__desc__t_1ae899427763e325f03241afc69a6e1ea0) {#structusb__iface__desc__t_1ae899427763e325f03241afc69a6e1ea0}

#### `public uint8_t `[`bInterfaceSubClass`](#structusb__iface__desc__t_1a3b3919d1203cd42550d77287f7585595) {#structusb__iface__desc__t_1a3b3919d1203cd42550d77287f7585595}

#### `public uint8_t `[`bInterfaceProtocol`](#structusb__iface__desc__t_1a6872c4ec51fd061e2955f84d97bea2a7) {#structusb__iface__desc__t_1a6872c4ec51fd061e2955f84d97bea2a7}

#### `public uint8_t `[`iInterface`](#structusb__iface__desc__t_1a2e4535908d90f195c6347a91e15b544d) {#structusb__iface__desc__t_1a2e4535908d90f195c6347a91e15b544d}

# struct `usb_ep_desc_t` {#structusb__ep__desc__t}

Standard USB endpoint descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__ep__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__ep__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 
`public uint8_t `[`bEndpointAddress`](#structusb__ep__desc__t_1a527afb0f25cdd442d8d32c7df8e18c45) | 
`public uint8_t `[`bmAttributes`](#structusb__ep__desc__t_1ae7c63b4cda39953db5710012a5d91c6f) | 
`public le16_t `[`wMaxPacketSize`](#structusb__ep__desc__t_1ad083d80a481cb62796a7183f9240c914) | 
`public uint8_t `[`bInterval`](#structusb__ep__desc__t_1aff92277eea8536f7de1a88d818c91b9e) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__ep__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__ep__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__ep__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__ep__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

#### `public uint8_t `[`bEndpointAddress`](#structusb__ep__desc__t_1a527afb0f25cdd442d8d32c7df8e18c45) {#structusb__ep__desc__t_1a527afb0f25cdd442d8d32c7df8e18c45}

#### `public uint8_t `[`bmAttributes`](#structusb__ep__desc__t_1ae7c63b4cda39953db5710012a5d91c6f) {#structusb__ep__desc__t_1ae7c63b4cda39953db5710012a5d91c6f}

#### `public le16_t `[`wMaxPacketSize`](#structusb__ep__desc__t_1ad083d80a481cb62796a7183f9240c914) {#structusb__ep__desc__t_1ad083d80a481cb62796a7183f9240c914}

#### `public uint8_t `[`bInterval`](#structusb__ep__desc__t_1aff92277eea8536f7de1a88d818c91b9e) {#structusb__ep__desc__t_1aff92277eea8536f7de1a88d818c91b9e}

# struct `usb_str_desc_t` {#structusb__str__desc__t}

A standard USB string descriptor structure.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__str__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | 
`public uint8_t `[`bDescriptorType`](#structusb__str__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) | 

## Members

#### `public uint8_t `[`bLength`](#structusb__str__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__str__desc__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

#### `public uint8_t `[`bDescriptorType`](#structusb__str__desc__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__str__desc__t_1a67d7027b9eb9ed268d28e84fbc675707}

# struct `usb_str_lgid_desc_t` {#structusb__str__lgid__desc__t}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_str_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__str__desc__t)` `[`desc`](#structusb__str__lgid__desc__t_1a6b9de937ba1cb40f4b82094a8644c528) | 
`public le16_t `[`string`](#structusb__str__lgid__desc__t_1a79364ecffd40a6c3218c408b4891c460) | 

## Members

#### `public `[`usb_str_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__str__desc__t)` `[`desc`](#structusb__str__lgid__desc__t_1a6b9de937ba1cb40f4b82094a8644c528) {#structusb__str__lgid__desc__t_1a6b9de937ba1cb40f4b82094a8644c528}

#### `public le16_t `[`string`](#structusb__str__lgid__desc__t_1a79364ecffd40a6c3218c408b4891c460) {#structusb__str__lgid__desc__t_1a79364ecffd40a6c3218c408b4891c460}

