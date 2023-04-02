set(LUFA_PATH ${CMAKE_SOURCE_DIR}/lib/lufa)
set(ARCH AVR8)
set(USE_STATIC_OPTIONS "(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)")

add_compile_definitions(
    PROTOCOL_LUFA
    ARCH=ARCH_${ARCH}
    BOARD=BOARD_NONE

    USB_DEVICE_ONLY
    USE_FLASH_DESCRIPTORS
    USE_STATIC_OPTIONS=${USE_STATIC_OPTIONS}
    FIXED_CONTROL_ENDPOINT_SIZE=8
    FIXED_NUM_CONFIGURATIONS=1
)

add_library(tmk_core_protocol_lufa 
    lufa.c
    ../usb_descriptor.c
    usb_util.c 
)

target_include_directories(tmk_core_protocol_lufa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tmk_core_protocol_lufa PUBLIC ${LUFA_PATH})

target_link_libraries(tmk_core_protocol_lufa PUBLIC quantum)

set(LUFA_ROOT_PATH ${CMAKE_SOURCE_DIR}/lib/lufa/LUFA)

target_sources(tmk_core_protocol_lufa
PUBLIC
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBController_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBInterrupt_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/ConfigDescriptors.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/Events.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/USBTask.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Class/Common/HIDParser.c 

    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Host_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Pipe_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/PipeStream_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/HostStandardReq.c

    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Device_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Endpoint_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/EndpointStream_${ARCH}.c
    # ${LUFA_ROOT_PATH}/Drivers/USB/Core/DeviceStandardReq.c

   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBController_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/USBInterrupt_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/ConfigDescriptors.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/Events.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/USBTask.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Class/Common/HIDParser.c

   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Host_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Pipe_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/PipeStream_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/HostStandardReq.c

   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Device_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/Endpoint_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/${ARCH}/EndpointStream_${ARCH}.c
   ${LUFA_ROOT_PATH}/Drivers/USB/Core/DeviceStandardReq.c

#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/AudioClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/CCIDClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/CDCClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/HIDClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/MassStorageClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/MIDIClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/PrinterClassDevice.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Device/RNDISClassDevice.c

#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/AndroidAccessoryClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/AudioClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/CDCClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/HIDClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/MassStorageClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/MIDIClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/PrinterClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/RNDISClassHost.c
#    ${LUFA_ROOT_PATH}/Drivers/USB/Class/Host/StillImageClassHost.c
)