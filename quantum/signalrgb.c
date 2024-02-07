#ifndef RAW_ENABLE
#    error "RAW HID Communication is not enabled" //This should be impossible to run into afaik. Common_features ensures RAWHID is enabled.
#endif

#include "qmk_version.h"
#include "protocol/host.h"
#include "version.h"
#include "quantum.h"
#include "signalrgb.h"
#include "color.h"
#include "raw_hid.h"


 uint8_t packet[32];

void get_qmk_version(void) //Grab the QMK Version the board's firmware is built off of
{
        packet[0] = GET_QMK_VERSION;
        packet[1] = QMK_VERSION_BYTE_1;
        packet[2] = QMK_VERSION_BYTE_2;
        packet[3] = QMK_VERSION_BYTE_3;

        raw_hid_send(packet, 32);
}

void get_signalrgb_protocol_version(void) 
{
        packet[0] = GET_PROTOCOL_VERSION;
        packet[1] = PROTOCOL_VERSION_BYTE_1;
        packet[2] = PROTOCOL_VERSION_BYTE_2;
        packet[3] = PROTOCOL_VERSION_BYTE_3;

        raw_hid_send(packet, 32);
}

void get_unique_identifier(void) //Grab the unique identifier for each specific model of keyboard.
{
        packet[0] = GET_UNIQUE_IDENTIFIER;
        packet[1] = DEVICE_UNIQUE_IDENTIFIER_BYTE_1;
        packet[2] = DEVICE_UNIQUE_IDENTIFIER_BYTE_2;
        packet[3] = DEVICE_UNIQUE_IDENTIFIER_BYTE_3;

        raw_hid_send(packet, 32);
}

void led_streaming(uint8_t *data) //Stream data from HID Packets to Keyboard.
{
    uint8_t index = data[1];
    uint8_t numberofleds = data[2]; 

    if(numberofleds >= 10)
    {
        packet[1] = DEVICE_ERROR_LEDS;
        raw_hid_send(packet,32);
        return; 
    } 
    
    for (uint8_t i = 0; i < numberofleds; i++)
    {
      uint8_t offset = (i * 3) + 3;
      uint8_t  r = data[offset];
      uint8_t  g = data[offset + 1];
      uint8_t  b = data[offset + 2];

      //if ( ((index + i) == CAPS_LOCK_LED_INDEX && host_keyboard_led_state().caps_lock) || ((index + i) == NUM_LOCK_LED_INDEX && host_keyboard_led_state().num_lock) || ((index + i) == SCROLL_LOCK_LED_INDEX && host_keyboard_led_state().scroll_lock))   {
      //if ( ((index + i) == CAPS_LOCK_LED_INDEX && host_keyboard_led_state().caps_lock) || ((index + i) == NUM_LOCK_LED_INDEX && host_keyboard_led_state().num_lock))   {
      //if ( (index + i) == CAPS_MAC_WIN_LED_INDEX && host_keyboard_led_state().caps_lock)   {
      //if ( (index + i) == CAPS_LOCK_LED_INDEX && host_keyboard_led_state().caps_lock)   {
      //if ( (index + i) == NUM_LOCK_LED_INDEX && host_keyboard_led_state().num_lock)  {
      //#if defined(RGBLIGHT_ENABLE)
      //rgblight_setrgb_at(255, 255, 255, index + i);
      //#elif defined(RGB_MATRIX_ENABLE)
      //rgb_matrix_set_color(index + i, 255, 255, 255);
      //#endif

      //} else {

      #if defined(RGBLIGHT_ENABLE)
      rgblight_setrgb_at(r, g, b, index + i);
      #elif defined(RGB_MATRIX_ENABLE)
      rgb_matrix_set_color(index + i, r, g, b);
      #endif
        }
     }
//}

void signalrgb_mode_enable(void)
{
    #if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SIGNALRGB); //Set RGB Matrix to SignalRGB Compatible Mode
    #endif
}

void signalrgb_mode_disable(void)
{
    #if defined(RGBLIGHT_ENABLE)
    rgblight_reload_from_eeprom();
    #elif defined(RGB_MATRIX_ENABLE)
    rgb_matrix_reload_from_eeprom(); //Reloading last effect from eeprom
    #endif
}

void get_total_leds(void)//Grab total number of leds that a board has.
{
    packet[0] = GET_TOTAL_LEDS;
    #if defined(RGBLIGHT_ENABLE)
    packet[1] = RGBLED_NUM;
    #elif defined(RGB_MATRIX_ENABLE)
    packet[1] = RGB_MATRIX_LED_COUNT;
    #endif

    raw_hid_send(packet, 32);
}

void get_firmware_type(void) //Grab which fork of qmk a board is running.
{
    packet[0] = GET_FIRMWARE_TYPE;
    packet[1] = FIRMWARE_TYPE_BYTE;

    raw_hid_send(packet, 32);
}

void raw_hid_receive(uint8_t *data, uint8_t length) 
{
        switch (data[0]) {
        case GET_QMK_VERSION:
           
        get_qmk_version();

        break;
        case GET_PROTOCOL_VERSION:

        get_signalrgb_protocol_version();

        break;
        case GET_UNIQUE_IDENTIFIER:

        get_unique_identifier();

        break;
        case STREAM_RGB_DATA: 

        led_streaming(data);

        break;

        case SET_SIGNALRGB_MODE_ENABLE: 

        signalrgb_mode_enable();

        break;

        case SET_SIGNALRGB_MODE_DISABLE: 

        signalrgb_mode_disable();

        break;

        case GET_TOTAL_LEDS:

        get_total_leds();

        break;

        case GET_FIRMWARE_TYPE:

        get_firmware_type();

        break;

        default:
        break;
    }
}