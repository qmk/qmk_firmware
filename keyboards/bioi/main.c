/*
Copyright 2019 Basic I/O Instruments(Scott Wei) <scot.wei@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/pgmspace.h>
#include <util/delay.h>

#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#include "print.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#endif
#include "suspend.h"

#include "usb_descriptor.h"
#include "lufa.h"
#include "quantum.h"
#include <util/atomic.h>

#ifdef NKRO_ENABLE
#include "keycode_config.h"

extern keymap_config_t keymap_config;
#endif

#ifdef AUDIO_ENABLE
#include <audio.h>
#endif

#ifdef BLUETOOTH_ENABLE
#ifdef BLUETOOTH_BLUEFRUIT_LE
#include "bluefruit_le.h"
#else
#include "bluetooth.h"
#endif
#endif

#ifdef VIRTSER_ENABLE
#include "virtser.h"
#endif

#if (defined(RGB_MIDI) | defined(RGBLIGHT_ANIMATIONS)) & defined(RGBLIGHT_ENABLE)
#include "rgblight.h"
#endif

#ifdef MIDI_ENABLE
#include "qmk_midi.h"
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
#endif

#include "ble.h"
#include "usart.h"

#include <avr/power.h>
#include <avr/sleep.h>

bool force_usb = false; //Reserved for FORCE USB Mode function.
bool force_ble = false; //Reserved for FORCE USB Mode function.

bool usb_connected = false;
bool ble_enabled = false;

uint32_t kb_idle_timer = 0;

bool usb_state_sent = false;

uint8_t USB_DeviceLastState = 0;

#ifdef RAW_ENABLE
/** \brief Raw HID Task
 *
 * FIXME: Needs doc
 */
static void raw_hid_task(void)
{
    // Create a temporary buffer to hold the read in data from the host
    uint8_t data[RAW_EPSIZE];
    bool data_read = false;

    // Device must be connected and configured for the task to run
    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    Endpoint_SelectEndpoint(RAW_OUT_EPNUM);

    // Check to see if a packet has been sent from the host
    if (Endpoint_IsOUTReceived())
    {
        // Check to see if the packet contains data
        if (Endpoint_IsReadWriteAllowed())
        {
            /* Read data */
            Endpoint_Read_Stream_LE(data, sizeof(data), NULL);
            data_read = true;
        }

        // Finalize the stream transfer to receive the last packet
        Endpoint_ClearOUT();

        if (data_read)
        {
            raw_hid_receive(data, sizeof(data));
        }
    }
}
#endif

static void setup_mcu(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}

static void setup_usb(void)
{
    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}

void power_saving(void)
{
    power_adc_disable();
    power_usart0_disable();
    power_spi_disable();
    power_twi_disable();

    USBCON |= (1 << FRZCLK); // Freeze the USB Clock
    PLLCSR &= ~(1 << PLLE);  // Disable the USB Clock (PPL)
    USBCON &= ~(1 << USBE);
}

void power_recover(void)
{

    USBCON |= (1 << USBE);
    PLLCSR |= (1 << PLLE);    // Resume the USB Clock (PPL)
    USBCON &= ~(1 << FRZCLK); // Resume the USB Clock

    power_adc_enable();
    power_usart0_enable();
    power_spi_enable();
    power_twi_enable();
}

void ble_task_init(void)
{
    kb_idle_timer = timer_read32();  //Mark current time, reserved for further usage;
}

void ble_task(void)
{

    if (USB_DeviceLastState != USB_DeviceState)
    {
        usb_state_sent = false;
#ifdef BLE_DEBUG
        send_str(PSTR("USB State Changed\r\n"));
        if (USB_DeviceState == DEVICE_STATE_Unattached)
        {
            send_str(PSTR("USB State Unattached\r\n"));
        }
#endif
        if (USB_DeviceState == DEVICE_STATE_Powered)
        {
#ifdef BLE_DEBUG
            send_str(PSTR("USB State Powered\r\n"));
#endif
            power_recover();
            host_set_driver(&null_driver);
        }
#ifdef BLE_DEBUG
        if ((USB_DeviceState == DEVICE_STATE_Default))
        {
            send_str(PSTR("USB State Default\r\n"));
        }
        if ((USB_DeviceState == DEVICE_STATE_Addressed))
        {
            send_str(PSTR("USB State Addressed\r\n"));
        }
        if (USB_DeviceState == DEVICE_STATE_Configured)
        {
            send_str(PSTR("USB State Configured\r\n"));
        }
        if (USB_DeviceState > DEVICE_STATE_Unattached)
        {
        }
        else
        {
            //
        }
#endif
    }
    else
    {
#ifdef BLE_DEBUG
        if (!usb_state_sent)
        {
            if (USB_DeviceState == DEVICE_STATE_Unattached)
            {
                send_str(PSTR("USB State Stopped at Unattached\r\n"));
            }
            if (USB_DeviceState == DEVICE_STATE_Powered)
            {
                send_str(PSTR("USB State Stopped at Powered\r\n"));
            }
            if ((USB_DeviceState == DEVICE_STATE_Default))
            {
                send_str(PSTR("USB State Stopped at Default\r\n"));
            }
            if ((USB_DeviceState == DEVICE_STATE_Addressed))
            {
                send_str(PSTR("USB State Stopped at Addressed\r\n"));
            }
            if (USB_DeviceState == DEVICE_STATE_Configured)
            {
                send_str(PSTR("USB State Stopped at Configured\r\n"));
            }
        }
#endif
        if (USB_DeviceState == DEVICE_STATE_Unattached)
        {
            if (host_get_driver() && host_get_driver() != &bluefruit_driver)
            {
#ifdef BLE_DEBUG
                send_str(PSTR("USB State stopped at Unattached\r\n"));
#endif
                ble_task_init();

                force_usb = 0;
                usb_connected = 0;

                //Reinit USB to prepare for next connection.
                USB_Init();
                USB_Detach();
                USB_Attach();

#ifdef BLE_DEBUG
                send_str(PSTR("Loading &bluefruit_driver\r\n"));
#endif
                host_set_driver(&bluefruit_driver);
                clear_keyboard();
                power_saving();
            }
            else
            {
                //Do nothing if USB is unattached and the driver is &bluefruit_driver
            }
        }
        if (USB_DeviceState == DEVICE_STATE_Configured)
        {
            if (host_get_driver() && host_get_driver() != &lufa_driver)
            {
#ifdef BLE_DEBUG
                send_str(PSTR("USB State stopped at Configured\r\n"));
#endif
                power_recover();

                usb_connected = 1;
                ble_enabled = 0;
#ifdef BLE_DEBUG
                send_str(PSTR("Loading &lufa_driver\r\n"));
#endif
                host_set_driver(&lufa_driver);
                clear_keyboard();
            }
            else
            {
                //Do nothing if the driver is &lufa_driver
            }
        }

        usb_state_sent = true;
    }

    USB_DeviceLastState = USB_DeviceState;
}

// Use a custom main() function because the task logic is different from the common one.
int main(void)
{
#ifdef MIDI_ENABLE
    setup_midi();
#endif

    setup_mcu();

    keyboard_setup();

    setup_usb();
    sei();

#if defined(BLUETOOTH_RN42)
    serial_init();
#endif

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 255; // timeout when USB is not available(Bluetooth)
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured)
    {
        wait_ms(4);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif
    }

    print("\nUSB init\n");

    keyboard_init();
    host_set_driver(&lufa_driver);

    backlight_disable();
    //host_set_driver(&lufa_driver);
    print("Keyboard initialized.\n");

    //Init Hardware UART
    usart_init();

#ifdef BLE_DEBUG
    send_str(PSTR("Keyboard has been setup up\r\n"));

    if (usb_connected)
    {
        send_str(PSTR("usb_connected=1\r\n"));
    }
    else
    {
        send_str(PSTR("usb_connected=0\r\n"));
    }
#endif

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

#ifdef VIRTSER_ENABLE
    virtser_init();
#endif

    while (1)
    {
        ble_task();
        keyboard_task();

#ifdef RAW_ENABLE
        raw_hid_task();
#endif

#if defined(RGBLIGHT_ANIMATIONS) && defined(RGBLIGHT_ENABLE)
        rgblight_task();
#endif

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif
    }
}
