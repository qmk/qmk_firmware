/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "cyw43.h"
#include "hci_transport.h"
#include "hci.h"
#include "pico/btstack_hci_transport_cyw43.h"

// assert outgoing pre-buffer for cyw43 header is available
#if !defined(HCI_OUTGOING_PRE_BUFFER_SIZE) || (HCI_OUTGOING_PRE_BUFFER_SIZE < 4)
#error HCI_OUTGOING_PRE_BUFFER_SIZE not defined or smaller than 4. Please update btstack_config.h
#endif

// assert outgoing packet fragments are word aligned
#if !defined(HCI_ACL_CHUNK_SIZE_ALIGNMENT) || ((HCI_ACL_CHUNK_SIZE_ALIGNMENT & 3) != 0)
#error HCI_ACL_CHUNK_SIZE_ALIGNMENT not defined or not a multiply of 4. Please update btstack_config.h
#endif

#define BT_DEBUG_ENABLED 0
#if BT_DEBUG_ENABLED
#define BT_DEBUG(...) CYW43_PRINTF(__VA_ARGS__)
#else
#define BT_DEBUG(...) (void)0
#endif

// Callback when we have data
static void (*hci_transport_cyw43_packet_handler)(uint8_t packet_type, uint8_t *packet, uint16_t size) = NULL;

// Incoming packet buffer - cyw43 packet header (incl packet type) + incoming pre buffer + max(acl header + acl payload, event header + event data)
__attribute__((aligned(4)))
static uint8_t hci_packet_with_pre_buffer[4 + HCI_INCOMING_PRE_BUFFER_SIZE + HCI_INCOMING_PACKET_BUFFER_SIZE ];

static btstack_data_source_t transport_data_source;
static bool hci_transport_ready;

// Forward declaration
static void hci_transport_cyw43_process(void);

static void hci_transport_data_source_process(btstack_data_source_t *ds, btstack_data_source_callback_type_t callback_type) {
    assert(callback_type == DATA_SOURCE_CALLBACK_POLL);
    assert(ds == &transport_data_source);
    (void)callback_type;
    (void)ds;
    hci_transport_cyw43_process();
}

static void hci_transport_cyw43_init(const void *transport_config) {
    UNUSED(transport_config);
}

static int hci_transport_cyw43_open(void) {
    int err = cyw43_bluetooth_hci_init();
    if (err != 0) {
        CYW43_PRINTF("Failed to open cyw43 hci controller: %d\n", err);
        return err;
    }

    btstack_run_loop_set_data_source_handler(&transport_data_source, &hci_transport_data_source_process);
    btstack_run_loop_enable_data_source_callbacks(&transport_data_source, DATA_SOURCE_CALLBACK_POLL);
    btstack_run_loop_add_data_source(&transport_data_source);
    hci_transport_ready = true;

    return 0;
}

static int hci_transport_cyw43_close(void) {
    btstack_run_loop_disable_data_source_callbacks(&transport_data_source, DATA_SOURCE_CALLBACK_POLL);
    btstack_run_loop_remove_data_source(&transport_data_source);
    hci_transport_ready = false;

    return 0;
}

static void hci_transport_cyw43_register_packet_handler(void (*handler)(uint8_t packet_type, uint8_t *packet, uint16_t size)) {
    hci_transport_cyw43_packet_handler = handler;
}

static int hci_transport_cyw43_can_send_now(uint8_t packet_type) {
    UNUSED(packet_type);
    return true;
}

static int hci_transport_cyw43_send_packet(uint8_t packet_type, uint8_t *packet, int size) {
    // store packet type before actual data and increase size
    // This relies on HCI_OUTGOING_PRE_BUFFER_SIZE being set
    uint8_t *buffer = &packet[-4];
    uint32_t buffer_size = size + 4;
    buffer[3] = packet_type;

    CYW43_THREAD_ENTER
    int err = cyw43_bluetooth_hci_write(buffer, buffer_size);

    if (err != 0) {
        CYW43_PRINTF("Failed to send cyw43 hci packet: %d\n", err);
        assert(false);
    } else {
        BT_DEBUG("bt sent %lu\n", buffer_size);
        static uint8_t packet_sent_event[] = { HCI_EVENT_TRANSPORT_PACKET_SENT, 0};
        hci_transport_cyw43_packet_handler(HCI_EVENT_PACKET, &packet_sent_event[0], sizeof(packet_sent_event));
    }
    CYW43_THREAD_EXIT
    return err;
}

// configure and return hci transport singleton
static const hci_transport_t hci_transport_cyw43 = {
        /* const char * name; */                                        "CYW43",
        /* void   (*init) (const void *transport_config); */            &hci_transport_cyw43_init,
        /* int    (*open)(void); */                                     &hci_transport_cyw43_open,
        /* int    (*close)(void); */                                    &hci_transport_cyw43_close,
        /* void   (*register_packet_handler)(void (*handler)(...); */   &hci_transport_cyw43_register_packet_handler,
        /* int    (*can_send_packet_now)(uint8_t packet_type); */       &hci_transport_cyw43_can_send_now,
        /* int    (*send_packet)(...); */                               &hci_transport_cyw43_send_packet,
        /* int    (*set_baudrate)(uint32_t baudrate); */                NULL,
        /* void   (*reset_link)(void); */                               NULL,
        /* void   (*set_sco_config)(uint16_t voice_setting, int num_connections); */ NULL,
};

const hci_transport_t *hci_transport_cyw43_instance(void) {
    return &hci_transport_cyw43;
}

// Called to perform bt work from a data source
static void hci_transport_cyw43_process(void) {
    CYW43_THREAD_LOCK_CHECK
    uint32_t len = 0;
    bool has_work;
    do {
        int err = cyw43_bluetooth_hci_read(hci_packet_with_pre_buffer, sizeof(hci_packet_with_pre_buffer), &len);
        BT_DEBUG("bt in len=%lu err=%d\n", len, err);
        if (err == 0 && len > 0) {
            hci_transport_cyw43_packet_handler(hci_packet_with_pre_buffer[3], hci_packet_with_pre_buffer + 4, len - 4);
            has_work = true;
        } else {
            has_work = false;
        }
    } while (has_work);
}

// This is called from cyw43_poll_func.
void cyw43_bluetooth_hci_process(void) {
    if (hci_transport_ready) {
        btstack_run_loop_poll_data_sources_from_irq();
    }
}
