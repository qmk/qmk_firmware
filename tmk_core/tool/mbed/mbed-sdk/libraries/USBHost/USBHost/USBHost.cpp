/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "USBHost.h"
#include "USBHostHub.h"

USBHost * USBHost::instHost = NULL;

#define DEVICE_CONNECTED_EVENT      (1 << 0)
#define DEVICE_DISCONNECTED_EVENT   (1 << 1)
#define TD_PROCESSED_EVENT          (1 << 2)

#define MAX_TRY_ENUMERATE_HUB       3

#define MIN(a, b) ((a > b) ? b : a)

/**
* How interrupts are processed:
*    - new device connected:
*       - a message is queued in queue_usb_event with the id DEVICE_CONNECTED_EVENT
*       - when the usb_thread receives the event, it:
*           - resets the device
*           - reads the device descriptor
*           - sets the address of the device
*           - if it is a hub, enumerates it
*   - device disconnected:
*       - a message is queued in queue_usb_event with the id DEVICE_DISCONNECTED_EVENT
*       - when the usb_thread receives the event, it:
*           - free the device and all its children (hub)
*   - td processed
*       - a message is queued in queue_usb_event with the id TD_PROCESSED_EVENT
*       - when the usb_thread receives the event, it:
*           - call the callback attached to the endpoint where the td is attached
*/
void USBHost::usb_process() {

    bool controlListState;
    bool bulkListState;
    bool interruptListState;
    USBEndpoint * ep;
    uint8_t i, j, res, timeout_set_addr = 10;
    uint8_t buf[8];
    bool too_many_hub;
    int idx;

#if DEBUG_TRANSFER
    uint8_t * buf_transfer;
#endif

#if MAX_HUB_NB
    uint8_t k;
#endif

    while(1) {
        osEvent evt = mail_usb_event.get();

        if (evt.status == osEventMail) {

            message_t * usb_msg = (message_t*)evt.value.p;

            switch (usb_msg->event_id) {

                // a new device has been connected
                case DEVICE_CONNECTED_EVENT:
                    too_many_hub = false;
                    buf[4] = 0;

                    do
                    {
                      Lock lock(this);

                      for (i = 0; i < MAX_DEVICE_CONNECTED; i++) {
                          if (!deviceInUse[i]) {
                              USB_DBG_EVENT("new device connected: %p\r\n", &devices[i]);
                              devices[i].init(usb_msg->hub, usb_msg->port, usb_msg->lowSpeed);
                              deviceReset[i] = false;
                              deviceInited[i] = true;
                              break;
                          }
                      }

                      if (i == MAX_DEVICE_CONNECTED) {
                          USB_ERR("Too many device connected!!\r\n");
                          continue;
                      }

                      if (!controlEndpointAllocated) {
                          control = newEndpoint(CONTROL_ENDPOINT, OUT, 0x08, 0x00);
                          addEndpoint(NULL, 0, (USBEndpoint*)control);
                          controlEndpointAllocated = true;
                      }

  #if MAX_HUB_NB
                      if (usb_msg->hub_parent)
                          devices[i].setHubParent((USBHostHub *)(usb_msg->hub_parent));
  #endif

                      for (j = 0; j < timeout_set_addr; j++) {

                          resetDevice(&devices[i]);

                          // set size of control endpoint
                          devices[i].setSizeControlEndpoint(8);

                          devices[i].activeAddress(false);

                          // get first 8 bit of device descriptor
                          // and check if we deal with a hub
                          USB_DBG("usb_thread read device descriptor on dev: %p\r\n", &devices[i]);
                          res = getDeviceDescriptor(&devices[i], buf, 8);

                          if (res != USB_TYPE_OK) {
                              USB_ERR("usb_thread could not read dev descr");
                              continue;
                          }

                          // set size of control endpoint
                          devices[i].setSizeControlEndpoint(buf[7]);

                          // second step: set an address to the device
                          res = setAddress(&devices[i], devices[i].getAddress());

                          if (res != USB_TYPE_OK) {
                              USB_ERR("SET ADDR FAILED");
                              continue;
                          }
                          devices[i].activeAddress(true);
                          USB_DBG("Address of %p: %d", &devices[i], devices[i].getAddress());

                          // try to read again the device descriptor to check if the device
                          // answers to its new address
                          res = getDeviceDescriptor(&devices[i], buf, 8);

                          if (res == USB_TYPE_OK) {
                              break;
                          }

                          Thread::wait(100);
                      }

                      USB_INFO("New device connected: %p [hub: %d - port: %d]", &devices[i], usb_msg->hub, usb_msg->port);

  #if MAX_HUB_NB
                      if (buf[4] == HUB_CLASS) {
                          for (k = 0; k < MAX_HUB_NB; k++) {
                              if (hub_in_use[k] == false) {
                                  for (uint8_t j = 0; j < MAX_TRY_ENUMERATE_HUB; j++) {
                                      if (hubs[k].connect(&devices[i])) {
                                          devices[i].hub = &hubs[k];
                                          hub_in_use[k] = true;
                                          break;
                                      }
                                  }
                                  if (hub_in_use[k] == true)
                                      break;
                              }
                          }

                          if (k == MAX_HUB_NB) {
                              USB_ERR("Too many hubs connected!!\r\n");
                              too_many_hub = true;
                          }
                      }

                      if (usb_msg->hub_parent)
                          ((USBHostHub *)(usb_msg->hub_parent))->deviceConnected(&devices[i]);
  #endif

                      if ((i < MAX_DEVICE_CONNECTED) && !too_many_hub) {
                          deviceInUse[i] = true;
                      }

                    } while(0);

                    break;

                // a device has been disconnected
                case DEVICE_DISCONNECTED_EVENT:

                    do
                    {
                      Lock lock(this);

                      controlListState = disableList(CONTROL_ENDPOINT);
                      bulkListState = disableList(BULK_ENDPOINT);
                      interruptListState = disableList(INTERRUPT_ENDPOINT);

                      idx = findDevice(usb_msg->hub, usb_msg->port, (USBHostHub *)(usb_msg->hub_parent));
                      if (idx != -1) {
                          freeDevice((USBDeviceConnected*)&devices[idx]);
                      }

                      if (controlListState) enableList(CONTROL_ENDPOINT);
                      if (bulkListState) enableList(BULK_ENDPOINT);
                      if (interruptListState) enableList(INTERRUPT_ENDPOINT);

                    } while(0);

                    break;

                // a td has been processed
                // call callback on the ed associated to the td
                // we are not in ISR -> users can use printf in their callback method
                case TD_PROCESSED_EVENT:
                    ep = (USBEndpoint *) ((HCTD *)usb_msg->td_addr)->ep;
                    if (usb_msg->td_state == USB_TYPE_IDLE) {
                        USB_DBG_EVENT("call callback on td %p [ep: %p state: %s - dev: %p - %s]", usb_msg->td_addr, ep, ep->getStateString(), ep->dev, ep->dev->getName(ep->getIntfNb()));

#if DEBUG_TRANSFER
                        if (ep->getDir() == IN) {
                            buf_transfer = ep->getBufStart();
                            printf("READ SUCCESS [%d bytes transferred - td: 0x%08X] on ep: [%p - addr: %02X]: ",  ep->getLengthTransferred(), usb_msg->td_addr, ep, ep->getAddress());
                            for (int i = 0; i < ep->getLengthTransferred(); i++)
                                printf("%02X ", buf_transfer[i]);
                            printf("\r\n\r\n");
                        }
#endif
                        ep->call();
                    } else {
                        idx = findDevice(ep->dev);
                        if (idx != -1) {
                            if (deviceInUse[idx]) {
                                USB_WARN("td %p processed but not in idle state: %s [ep: %p - dev: %p - %s]", usb_msg->td_addr, ep->getStateString(), ep, ep->dev, ep->dev->getName(ep->getIntfNb()));
                                ep->setState(USB_TYPE_IDLE);
                            }
                        }
                    }
                    break;
            }

            mail_usb_event.free(usb_msg);
        }
    }
}

/* static */void USBHost::usb_process_static(void const * arg) {
    ((USBHost *)arg)->usb_process();
}

USBHost::USBHost() : usbThread(USBHost::usb_process_static, (void *)this, osPriorityNormal, USB_THREAD_STACK)
{
    headControlEndpoint = NULL;
    headBulkEndpoint = NULL;
    headInterruptEndpoint = NULL;
    tailControlEndpoint = NULL;
    tailBulkEndpoint = NULL;
    tailInterruptEndpoint = NULL;

    lenReportDescr = 0;

    controlEndpointAllocated = false;

    for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        deviceInUse[i] = false;
        devices[i].setAddress(i + 1);
        deviceReset[i] = false;
        deviceInited[i] = false;
        for (uint8_t j = 0; j < MAX_INTF; j++)
            deviceAttachedDriver[i][j] = false;
    }

#if MAX_HUB_NB
    for (uint8_t i = 0; i < MAX_HUB_NB; i++) {
        hubs[i].setHost(this);
        hub_in_use[i] = false;
    }
#endif
}

USBHost::Lock::Lock(USBHost* pHost) : m_pHost(pHost)
{
  m_pHost->usb_mutex.lock();
}

USBHost::Lock::~Lock()
{
  m_pHost->usb_mutex.unlock();
}

void USBHost::transferCompleted(volatile uint32_t addr)
{
    uint8_t state;

    if(addr == 0)
        return;

    volatile HCTD* tdList = NULL;

    //First we must reverse the list order and dequeue each TD
    do {
        volatile HCTD* td = (volatile HCTD*)addr;
        addr = (uint32_t)td->nextTD; //Dequeue from physical list
        td->nextTD = tdList; //Enqueue into reversed list
        tdList = td;
    } while(addr);

    while(tdList != NULL) {
        volatile HCTD* td = tdList;
        tdList = (volatile HCTD*)td->nextTD; //Dequeue element now as it could be modified below
        if (td->ep != NULL) {
            USBEndpoint * ep = (USBEndpoint *)(td->ep);

            if (((HCTD *)td)->control >> 28) {
                state = ((HCTD *)td)->control >> 28;
            } else {
                if (td->currBufPtr)
                    ep->setLengthTransferred((uint32_t)td->currBufPtr - (uint32_t)ep->getBufStart());
                state = 16 /*USB_TYPE_IDLE*/;
            }

            ep->unqueueTransfer(td);

            if (ep->getType() != CONTROL_ENDPOINT) {
                // callback on the processed td will be called from the usb_thread (not in ISR)
                message_t * usb_msg = mail_usb_event.alloc();
                usb_msg->event_id = TD_PROCESSED_EVENT;
                usb_msg->td_addr = (void *)td;
                usb_msg->td_state = state;
                mail_usb_event.put(usb_msg);
            }
            ep->setState(state);
            ep->ep_queue.put((uint8_t*)1);
        }
    }
}

USBHost * USBHost::getHostInst()
{
    if (instHost == NULL) {
        instHost = new USBHost();
        instHost->init();
    }
    return instHost;
}


/*
 * Called when a device has been connected
 * Called in ISR!!!! (no printf)
 */
/* virtual */ void USBHost::deviceConnected(int hub, int port, bool lowSpeed, USBHostHub * hub_parent)
{
    // be sure that the new device connected is not already connected...
    int idx = findDevice(hub, port, hub_parent);
    if (idx != -1) {
        if (deviceInited[idx])
            return;
    }

    message_t * usb_msg = mail_usb_event.alloc();
    usb_msg->event_id = DEVICE_CONNECTED_EVENT;
    usb_msg->hub = hub;
    usb_msg->port = port;
    usb_msg->lowSpeed = lowSpeed;
    usb_msg->hub_parent = hub_parent;
    mail_usb_event.put(usb_msg);
}

/*
 * Called when a device has been disconnected
 * Called in ISR!!!! (no printf)
 */
/* virtual */ void USBHost::deviceDisconnected(int hub, int port, USBHostHub * hub_parent, volatile uint32_t addr)
{
    // be sure that the device disconnected is connected...
    int idx = findDevice(hub, port, hub_parent);
    if (idx != -1) {
        if (!deviceInUse[idx])
            return;
    } else {
        return;
    }

    message_t * usb_msg = mail_usb_event.alloc();
    usb_msg->event_id = DEVICE_DISCONNECTED_EVENT;
    usb_msg->hub = hub;
    usb_msg->port = port;
    usb_msg->hub_parent = hub_parent;
    mail_usb_event.put(usb_msg);
}

void USBHost::freeDevice(USBDeviceConnected * dev)
{
    USBEndpoint * ep = NULL;
    HCED * ed = NULL;

#if MAX_HUB_NB
    if (dev->getClass() == HUB_CLASS) {
        if (dev->hub == NULL) {
            USB_ERR("HUB NULL!!!!!\r\n");
        } else {
            dev->hub->hubDisconnected();
            for (uint8_t i = 0; i < MAX_HUB_NB; i++) {
                if (dev->hub == &hubs[i]) {
                    hub_in_use[i] = false;
                    break;
                }
            }
        }
    }

    // notify hub parent that this device has been disconnected
    if (dev->getHubParent())
        dev->getHubParent()->deviceDisconnected(dev);

#endif

    int idx = findDevice(dev);
    if (idx != -1) {
        deviceInUse[idx] = false;
        deviceReset[idx] = false;

        for (uint8_t j = 0; j < MAX_INTF; j++) {
            deviceAttachedDriver[idx][j] = false;
            if (dev->getInterface(j) != NULL) {
                USB_DBG("FREE INTF %d on dev: %p, %p, nb_endpot: %d, %s", j, (void *)dev->getInterface(j), dev, dev->getInterface(j)->nb_endpoint, dev->getName(j));
                for (int i = 0; i < dev->getInterface(j)->nb_endpoint; i++) {
                    if ((ep = dev->getEndpoint(j, i)) != NULL) {
                        ed = (HCED *)ep->getHCED();
                        ed->control |= (1 << 14); //sKip bit
                        unqueueEndpoint(ep);

                        freeTD((volatile uint8_t*)ep->getTDList()[0]);
                        freeTD((volatile uint8_t*)ep->getTDList()[1]);

                        freeED((uint8_t *)ep->getHCED());
                    }
                    printList(BULK_ENDPOINT);
                    printList(INTERRUPT_ENDPOINT);
                }
                USB_INFO("Device disconnected [%p - %s - hub: %d - port: %d]", dev, dev->getName(j), dev->getHub(), dev->getPort());
            }
        }
        dev->disconnect();
    }
}


void USBHost::unqueueEndpoint(USBEndpoint * ep)
{
    USBEndpoint * prec = NULL;
    USBEndpoint * current = NULL;

    for (int i = 0; i < 2; i++) {
        current = (i == 0) ? (USBEndpoint*)headBulkEndpoint : (USBEndpoint*)headInterruptEndpoint;
        prec = current;
        while (current != NULL) {
            if (current == ep) {
                if (current->nextEndpoint() != NULL) {
                    prec->queueEndpoint(current->nextEndpoint());
                    if (current == headBulkEndpoint) {
                        updateBulkHeadED((uint32_t)current->nextEndpoint()->getHCED());
                        headBulkEndpoint = current->nextEndpoint();
                    } else if (current == headInterruptEndpoint) {
                        updateInterruptHeadED((uint32_t)current->nextEndpoint()->getHCED());
                        headInterruptEndpoint = current->nextEndpoint();
                    }
                }
                // here we are dequeuing the queue of ed
                // we need to update the tail pointer
                else {
                    prec->queueEndpoint(NULL);
                    if (current == headBulkEndpoint) {
                        updateBulkHeadED(0);
                        headBulkEndpoint = current->nextEndpoint();
                    } else if (current == headInterruptEndpoint) {
                        updateInterruptHeadED(0);
                        headInterruptEndpoint = current->nextEndpoint();
                    }

                    // modify tail
                    switch (current->getType()) {
                        case BULK_ENDPOINT:
                            tailBulkEndpoint = prec;
                            break;
                        case INTERRUPT_ENDPOINT:
                            tailInterruptEndpoint = prec;
                            break;
                        default:
                            break;
                    }
                }
                current->setState(USB_TYPE_FREE);
                return;
            }
            prec = current;
            current = current->nextEndpoint();
        }
    }
}


USBDeviceConnected * USBHost::getDevice(uint8_t index)
{
    if ((index >= MAX_DEVICE_CONNECTED) || (!deviceInUse[index])) {
        return NULL;
    }
    return (USBDeviceConnected*)&devices[index];
}

// create an USBEndpoint descriptor. the USBEndpoint is not linked
USBEndpoint * USBHost::newEndpoint(ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir, uint32_t size, uint8_t addr)
{
    int i = 0;
    HCED * ed = (HCED *)getED();
    HCTD* td_list[2] = { (HCTD*)getTD(), (HCTD*)getTD() };

    memset((void *)td_list[0], 0x00, sizeof(HCTD));
    memset((void *)td_list[1], 0x00, sizeof(HCTD));

    // search a free USBEndpoint
    for (i = 0; i < MAX_ENDPOINT; i++) {
        if (endpoints[i].getState() == USB_TYPE_FREE) {
            endpoints[i].init(ed, type, dir, size, addr, td_list);
            USB_DBG("USBEndpoint created (%p): type: %d, dir: %d, size: %d, addr: %d, state: %s", &endpoints[i], type, dir, size, addr, endpoints[i].getStateString());
            return &endpoints[i];
        }
    }
    USB_ERR("could not allocate more endpoints!!!!");
    return NULL;
}


USB_TYPE USBHost::resetDevice(USBDeviceConnected * dev)
{
    int index = findDevice(dev);
    if (index != -1) {
        USB_DBG("Resetting hub %d, port %d\n", dev->getHub(), dev->getPort());
        Thread::wait(100);
        if (dev->getHub() == 0) {
            resetRootHub();
        }
#if MAX_HUB_NB
        else {
            dev->getHubParent()->portReset(dev->getPort());
        }
#endif
        Thread::wait(100);
        deviceReset[index] = true;
        return USB_TYPE_OK;
    }

    return USB_TYPE_ERROR;
}

// link the USBEndpoint to the linked list and attach an USBEndpoint to a device
bool USBHost::addEndpoint(USBDeviceConnected * dev, uint8_t intf_nb, USBEndpoint * ep)
{

    if (ep == NULL) {
        return false;
    }

    HCED * prevEd;

    // set device address in the USBEndpoint descriptor
    if (dev == NULL) {
        ep->setDeviceAddress(0);
    } else {
        ep->setDeviceAddress(dev->getAddress());
    }

    if ((dev != NULL) && dev->getSpeed()) {
        ep->setSpeed(dev->getSpeed());
    }

    ep->setIntfNb(intf_nb);

    // queue the new USBEndpoint on the ED list
    switch (ep->getType()) {

        case CONTROL_ENDPOINT:
            prevEd = ( HCED*) controlHeadED();
            if (!prevEd) {
                updateControlHeadED((uint32_t) ep->getHCED());
                USB_DBG_TRANSFER("First control USBEndpoint: %08X", (uint32_t) ep->getHCED());
                headControlEndpoint = ep;
                tailControlEndpoint = ep;
                return true;
            }
            tailControlEndpoint->queueEndpoint(ep);
            tailControlEndpoint = ep;
            return true;

        case BULK_ENDPOINT:
            prevEd = ( HCED*) bulkHeadED();
            if (!prevEd) {
                updateBulkHeadED((uint32_t) ep->getHCED());
                USB_DBG_TRANSFER("First bulk USBEndpoint: %08X\r\n", (uint32_t) ep->getHCED());
                headBulkEndpoint = ep;
                tailBulkEndpoint = ep;
                break;
            }
            USB_DBG_TRANSFER("Queue BULK Ed %p after %p\r\n",ep->getHCED(), prevEd);
            tailBulkEndpoint->queueEndpoint(ep);
            tailBulkEndpoint = ep;
            break;

        case INTERRUPT_ENDPOINT:
            prevEd = ( HCED*) interruptHeadED();
            if (!prevEd) {
                updateInterruptHeadED((uint32_t) ep->getHCED());
                USB_DBG_TRANSFER("First interrupt USBEndpoint: %08X\r\n", (uint32_t) ep->getHCED());
                headInterruptEndpoint = ep;
                tailInterruptEndpoint = ep;
                break;
            }
            USB_DBG_TRANSFER("Queue INTERRUPT Ed %p after %p\r\n",ep->getHCED(), prevEd);
            tailInterruptEndpoint->queueEndpoint(ep);
            tailInterruptEndpoint = ep;
            break;
        default:
            return false;
    }

    ep->dev = dev;
    dev->addEndpoint(intf_nb, ep);

    return true;
}


int USBHost::findDevice(USBDeviceConnected * dev)
{
    for (int i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        if (dev == &devices[i]) {
            return i;
        }
    }
    return -1;
}

int USBHost::findDevice(uint8_t hub, uint8_t port, USBHostHub * hub_parent)
{
    for (int i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        if (devices[i].getHub() == hub && devices[i].getPort() == port) {
            if (hub_parent != NULL) {
                if (hub_parent == devices[i].getHubParent())
                    return i;
            } else {
                return i;
            }
        }
    }
    return -1;
}

void USBHost::printList(ENDPOINT_TYPE type)
{
#if DEBUG_EP_STATE
    volatile HCED * hced;
    switch(type) {
        case CONTROL_ENDPOINT:
            hced = (HCED *)controlHeadED();
            break;
        case BULK_ENDPOINT:
            hced = (HCED *)bulkHeadED();
            break;
        case INTERRUPT_ENDPOINT:
            hced = (HCED *)interruptHeadED();
            break;
    }
    volatile HCTD * hctd = NULL;
    const char * type_str = (type == BULK_ENDPOINT) ? "BULK" :
                            ((type == INTERRUPT_ENDPOINT) ? "INTERRUPT" :
                            ((type == CONTROL_ENDPOINT) ? "CONTROL" : "ISOCHRONOUS"));
    printf("State of %s:\r\n", type_str);
    while (hced != NULL) {
        uint8_t dir = ((hced->control & (3 << 11)) >> 11);
        printf("hced: %p [ADDR: %d, DIR: %s, EP_NB: 0x%X]\r\n", hced,
                                                   hced->control & 0x7f,
                                                   (dir == 1) ? "OUT" : ((dir == 0) ? "FROM_TD":"IN"),
                                                    (hced->control & (0xf << 7)) >> 7);
        hctd = (HCTD *)((uint32_t)(hced->headTD) & ~(0xf));
        while (hctd != hced->tailTD) {
            printf("\thctd: %p [DIR: %s]\r\n", hctd, ((hctd->control & (3 << 19)) >> 19) == 1 ? "OUT" : "IN");
            hctd = hctd->nextTD;
        }
        printf("\thctd: %p\r\n", hctd);
        hced = hced->nextED;
    }
    printf("\r\n\r\n");
#endif
}


// add a transfer on the TD linked list
USB_TYPE USBHost::addTransfer(USBEndpoint * ed, uint8_t * buf, uint32_t len)
{
    td_mutex.lock();

    // allocate a TD which will be freed in TDcompletion
    volatile HCTD * td = ed->getNextTD();
    if (td == NULL) {
        return USB_TYPE_ERROR;
    }

    uint32_t token = (ed->isSetup() ? TD_SETUP : ( (ed->getDir() == IN) ? TD_IN : TD_OUT ));

    uint32_t td_toggle;

    if (ed->getType() == CONTROL_ENDPOINT) {
        if (ed->isSetup()) {
            td_toggle = TD_TOGGLE_0;
        } else {
            td_toggle = TD_TOGGLE_1;
        }
    } else {
        td_toggle = 0;
    }

    td->control      = (TD_ROUNDING | token | TD_DELAY_INT(0) | td_toggle | TD_CC);
    td->currBufPtr   = buf;
    td->bufEnd       = (buf + (len - 1));

    ENDPOINT_TYPE type = ed->getType();

    disableList(type);
    ed->queueTransfer();
    printList(type);
    enableList(type);

    td_mutex.unlock();

    return USB_TYPE_PROCESSING;
}



USB_TYPE USBHost::getDeviceDescriptor(USBDeviceConnected * dev, uint8_t * buf, uint16_t max_len_buf, uint16_t * len_dev_descr)
{
    USB_TYPE t = controlRead(  dev,
                         USB_DEVICE_TO_HOST | USB_RECIPIENT_DEVICE,
                         GET_DESCRIPTOR,
                         (DEVICE_DESCRIPTOR << 8) | (0),
                         0, buf, MIN(DEVICE_DESCRIPTOR_LENGTH, max_len_buf));
    if (len_dev_descr)
        *len_dev_descr = MIN(DEVICE_DESCRIPTOR_LENGTH, max_len_buf);

    return t;
}

USB_TYPE USBHost::getConfigurationDescriptor(USBDeviceConnected * dev, uint8_t * buf, uint16_t max_len_buf, uint16_t * len_conf_descr)
{
    USB_TYPE res;
    uint16_t total_conf_descr_length = 0;

    // fourth step: get the beginning of the configuration descriptor to have the total length of the conf descr
    res = controlRead(  dev,
                        USB_DEVICE_TO_HOST | USB_RECIPIENT_DEVICE,
                        GET_DESCRIPTOR,
                        (CONFIGURATION_DESCRIPTOR << 8) | (0),
                        0, buf, CONFIGURATION_DESCRIPTOR_LENGTH);

    if (res != USB_TYPE_OK) {
        USB_ERR("GET CONF 1 DESCR FAILED");
        return res;
    }
    total_conf_descr_length = buf[2] | (buf[3] << 8);
    total_conf_descr_length = MIN(max_len_buf, total_conf_descr_length);

    if (len_conf_descr)
        *len_conf_descr = total_conf_descr_length;

    USB_DBG("TOTAL_LENGTH: %d \t NUM_INTERF: %d", total_conf_descr_length, buf[4]);

    return controlRead(  dev,
                         USB_DEVICE_TO_HOST | USB_RECIPIENT_DEVICE,
                         GET_DESCRIPTOR,
                         (CONFIGURATION_DESCRIPTOR << 8) | (0),
                         0, buf, total_conf_descr_length);
}


USB_TYPE USBHost::setAddress(USBDeviceConnected * dev, uint8_t address) {
    return controlWrite(    dev,
                            USB_HOST_TO_DEVICE | USB_RECIPIENT_DEVICE,
                            SET_ADDRESS,
                            address,
                            0, NULL, 0);

}

USB_TYPE USBHost::setConfiguration(USBDeviceConnected * dev, uint8_t conf)
{
    return controlWrite( dev,
                         USB_HOST_TO_DEVICE | USB_RECIPIENT_DEVICE,
                         SET_CONFIGURATION,
                         conf,
                         0, NULL, 0);
}

uint8_t USBHost::numberDriverAttached(USBDeviceConnected * dev) {
    int index = findDevice(dev);
    uint8_t cnt = 0;
    if (index == -1)
        return 0;
    for (uint8_t i = 0; i < MAX_INTF; i++) {
        if (deviceAttachedDriver[index][i])
            cnt++;
    }
    return cnt;
}

// enumerate a device with the control USBEndpoint
USB_TYPE USBHost::enumerate(USBDeviceConnected * dev, IUSBEnumerator* pEnumerator)
{
    uint16_t total_conf_descr_length = 0;
    USB_TYPE res;

    do
    {
      Lock lock(this);

      // don't enumerate a device which all interfaces are registered to a specific driver
      int index = findDevice(dev);

      if (index == -1) {
          return USB_TYPE_ERROR;
      }

      uint8_t nb_intf_attached = numberDriverAttached(dev);
      USB_DBG("dev: %p nb_intf: %d", dev, dev->getNbIntf());
      USB_DBG("dev: %p nb_intf_attached: %d", dev, nb_intf_attached);
      if ((nb_intf_attached != 0) && (dev->getNbIntf() == nb_intf_attached)) {
          USB_DBG("Don't enumerate dev: %p because all intf are registered with a driver", dev);
          return USB_TYPE_OK;
      }

      USB_DBG("Enumerate dev: %p", dev);

      // third step: get the whole device descriptor to see vid, pid
      res = getDeviceDescriptor(dev, data, DEVICE_DESCRIPTOR_LENGTH);

      if (res != USB_TYPE_OK) {
          USB_DBG("GET DEV DESCR FAILED");
          return res;
      }

      dev->setClass(data[4]);
      dev->setSubClass(data[5]);
      dev->setProtocol(data[6]);
      dev->setVid(data[8] | (data[9] << 8));
      dev->setPid(data[10] | (data[11] << 8));
      USB_DBG("CLASS: %02X \t VID: %04X \t PID: %04X", data[4], data[8] | (data[9] << 8), data[10] | (data[11] << 8));

      pEnumerator->setVidPid( data[8] | (data[9] << 8), data[10] | (data[11] << 8) );

      res = getConfigurationDescriptor(dev, data, sizeof(data), &total_conf_descr_length);
      if (res != USB_TYPE_OK) {
          return res;
      }

  #if (DEBUG > 3)
      USB_DBG("CONFIGURATION DESCRIPTOR:\r\n");
      for (int i = 0; i < total_conf_descr_length; i++)
          printf("%02X ", data[i]);
      printf("\r\n\r\n");
  #endif

      // Parse the configuration descriptor
      parseConfDescr(dev, data, total_conf_descr_length, pEnumerator);

      // only set configuration if not enumerated before
      if (!dev->isEnumerated()) {

          USB_DBG("Set configuration 1 on dev: %p", dev);
          // sixth step: set configuration (only 1 supported)
          res = setConfiguration(dev, 1);

          if (res != USB_TYPE_OK) {
              USB_DBG("SET CONF FAILED");
              return res;
          }
      }

      dev->setEnumerated();

      // Now the device is enumerated!
      USB_DBG("dev %p is enumerated\r\n", dev);

    } while(0);

    // Some devices may require this delay
    Thread::wait(100);

    return USB_TYPE_OK;
}
// this method fills the USBDeviceConnected object: class,.... . It also add endpoints found in the descriptor.
void USBHost::parseConfDescr(USBDeviceConnected * dev, uint8_t * conf_descr, uint32_t len, IUSBEnumerator* pEnumerator)
{
    uint32_t index = 0;
    uint32_t len_desc = 0;
    uint8_t id = 0;
    int nb_endpoints_used = 0;
    USBEndpoint * ep = NULL;
    uint8_t intf_nb = 0;
    bool parsing_intf = false;
    uint8_t current_intf = 0;

    while (index < len) {
        len_desc = conf_descr[index];
        id = conf_descr[index+1];
        switch (id) {
            case CONFIGURATION_DESCRIPTOR:
                USB_DBG("dev: %p has %d intf", dev, conf_descr[4]);
                dev->setNbIntf(conf_descr[4]);
                break;
            case INTERFACE_DESCRIPTOR:
                if(pEnumerator->parseInterface(conf_descr[index + 2], conf_descr[index + 5], conf_descr[index + 6], conf_descr[index + 7])) {
                    if (intf_nb++ <= MAX_INTF) {
                        current_intf = conf_descr[index + 2];
                        dev->addInterface(current_intf, conf_descr[index + 5], conf_descr[index + 6], conf_descr[index + 7]);
                        nb_endpoints_used = 0;
                        USB_DBG("ADD INTF %d on device %p: class: %d, subclass: %d, proto: %d", current_intf, dev, conf_descr[index + 5],conf_descr[index + 6],conf_descr[index + 7]);
                    } else {
                        USB_DBG("Drop intf...");
                    }
                    parsing_intf = true;
                } else {
                    parsing_intf = false;
                }
                break;
            case ENDPOINT_DESCRIPTOR:
                if (parsing_intf && (intf_nb <= MAX_INTF) ) {
                    if (nb_endpoints_used < MAX_ENDPOINT_PER_INTERFACE) {
                        if( pEnumerator->useEndpoint(current_intf, (ENDPOINT_TYPE)(conf_descr[index + 3] & 0x03), (ENDPOINT_DIRECTION)((conf_descr[index + 2] >> 7) + 1)) ) {
                            // if the USBEndpoint is isochronous -> skip it (TODO: fix this)
                            if ((conf_descr[index + 3] & 0x03) != ISOCHRONOUS_ENDPOINT) {
                                ep = newEndpoint((ENDPOINT_TYPE)(conf_descr[index+3] & 0x03),
                                                 (ENDPOINT_DIRECTION)((conf_descr[index + 2] >> 7) + 1),
                                                 conf_descr[index + 4] | (conf_descr[index + 5] << 8),
                                                 conf_descr[index + 2] & 0x0f);
                                USB_DBG("ADD USBEndpoint %p, on interf %d on device %p", ep, current_intf, dev);
                                if (ep != NULL && dev != NULL) {
                                    addEndpoint(dev, current_intf, ep);
                                } else {
                                    USB_DBG("EP NULL");
                                }
                                nb_endpoints_used++;
                            } else {
                                USB_DBG("ISO USBEndpoint NOT SUPPORTED");
                            }
                        }
                    }
                }
                break;
            case HID_DESCRIPTOR:
                lenReportDescr = conf_descr[index + 7] | (conf_descr[index + 8] << 8);
                break;
            default:
                break;
        }
        index += len_desc;
    }
}


USB_TYPE USBHost::bulkWrite(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking)
{
    return generalTransfer(dev, ep, buf, len, blocking, BULK_ENDPOINT, true);
}

USB_TYPE USBHost::bulkRead(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking)
{
    return generalTransfer(dev, ep, buf, len, blocking, BULK_ENDPOINT, false);
}

USB_TYPE USBHost::interruptWrite(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking)
{
    return generalTransfer(dev, ep, buf, len, blocking, INTERRUPT_ENDPOINT, true);
}

USB_TYPE USBHost::interruptRead(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking)
{
    return generalTransfer(dev, ep, buf, len, blocking, INTERRUPT_ENDPOINT, false);
}

USB_TYPE USBHost::generalTransfer(USBDeviceConnected * dev, USBEndpoint * ep, uint8_t * buf, uint32_t len, bool blocking, ENDPOINT_TYPE type, bool write) {

#if DEBUG_TRANSFER
    const char * type_str = (type == BULK_ENDPOINT) ? "BULK" : ((type == INTERRUPT_ENDPOINT) ? "INTERRUPT" : "ISOCHRONOUS");
    USB_DBG_TRANSFER("----- %s %s [dev: %p - %s - hub: %d - port: %d - addr: %d - ep: %02X]------", type_str, (write) ? "WRITE" : "READ", dev, dev->getName(ep->getIntfNb()), dev->getHub(), dev->getPort(), dev->getAddress(), ep->getAddress());
#endif

    Lock lock(this);

    USB_TYPE res;
    ENDPOINT_DIRECTION dir = (write) ? OUT : IN;

    if (dev == NULL) {
        USB_ERR("dev NULL");
        return USB_TYPE_ERROR;
    }

    if (ep == NULL) {
        USB_ERR("ep NULL");
        return USB_TYPE_ERROR;
    }

    if (ep->getState() != USB_TYPE_IDLE) {
        USB_WARN("[ep: %p - dev: %p - %s] NOT IDLE: %s", ep, ep->dev, ep->dev->getName(ep->getIntfNb()), ep->getStateString());
        return ep->getState();
    }

    if ((ep->getDir() != dir) || (ep->getType() != type)) {
        USB_ERR("[ep: %p - dev: %p] wrong dir or bad USBEndpoint type", ep, ep->dev);
        return USB_TYPE_ERROR;
    }

    if (dev->getAddress() != ep->getDeviceAddress()) {
        USB_ERR("[ep: %p - dev: %p] USBEndpoint addr and device addr don't match", ep, ep->dev);
        return USB_TYPE_ERROR;
    }

#if DEBUG_TRANSFER
    if (write) {
        USB_DBG_TRANSFER("%s WRITE buffer", type_str);
        for (int i = 0; i < ep->getLengthTransferred(); i++)
            printf("%02X ", buf[i]);
        printf("\r\n\r\n");
    }
#endif
    addTransfer(ep, buf, len);

    if (blocking) {

        ep->ep_queue.get();
        res = ep->getState();

        USB_DBG_TRANSFER("%s TRANSFER res: %s on ep: %p\r\n", type_str, ep->getStateString(), ep);

        if (res != USB_TYPE_IDLE) {
            return res;
        }

        return USB_TYPE_OK;
    }

    return USB_TYPE_PROCESSING;

}


USB_TYPE USBHost::controlRead(USBDeviceConnected * dev, uint8_t requestType, uint8_t request, uint32_t value, uint32_t index, uint8_t * buf, uint32_t len) {
    return controlTransfer(dev, requestType, request, value, index, buf, len, false);
}

USB_TYPE USBHost::controlWrite(USBDeviceConnected * dev, uint8_t requestType, uint8_t request, uint32_t value, uint32_t index, uint8_t * buf, uint32_t len) {
    return controlTransfer(dev, requestType, request, value, index, buf, len, true);
}

USB_TYPE USBHost::controlTransfer(USBDeviceConnected * dev, uint8_t requestType, uint8_t request, uint32_t value, uint32_t index, uint8_t * buf, uint32_t len, bool write)
{
    Lock lock(this);
    USB_DBG_TRANSFER("----- CONTROL %s [dev: %p - hub: %d - port: %d] ------", (write) ? "WRITE" : "READ", dev, dev->getHub(), dev->getPort());

    int length_transfer = len;
    USB_TYPE res;
    uint32_t token;

    control->setSpeed(dev->getSpeed());
    control->setSize(dev->getSizeControlEndpoint());
    if (dev->isActiveAddress()) {
        control->setDeviceAddress(dev->getAddress());
    } else {
        control->setDeviceAddress(0);
    }

    USB_DBG_TRANSFER("Control transfer on device: %d\r\n", control->getDeviceAddress());
    fillControlBuf(requestType, request, value, index, len);

#if DEBUG_TRANSFER
    USB_DBG_TRANSFER("SETUP PACKET: ");
    for (int i = 0; i < 8; i++)
        printf("%01X ", setupPacket[i]);
    printf("\r\n");
#endif

    control->setNextToken(TD_SETUP);
    addTransfer(control, (uint8_t*)setupPacket, 8);

    control->ep_queue.get();
    res = control->getState();

    USB_DBG_TRANSFER("CONTROL setup stage %s", control->getStateString());

    if (res != USB_TYPE_IDLE) {
        return res;
    }

    if (length_transfer) {
        token = (write) ? TD_OUT : TD_IN;
        control->setNextToken(token);
        addTransfer(control, (uint8_t *)buf, length_transfer);

        control->ep_queue.get();
        res = control->getState();

#if DEBUG_TRANSFER
        USB_DBG_TRANSFER("CONTROL %s stage %s", (write) ? "WRITE" : "READ", control->getStateString());
        if (write) {
            USB_DBG_TRANSFER("CONTROL WRITE buffer");
            for (int i = 0; i < control->getLengthTransferred(); i++)
                printf("%02X ", buf[i]);
            printf("\r\n\r\n");
        } else {
            USB_DBG_TRANSFER("CONTROL READ SUCCESS [%d bytes transferred]", control->getLengthTransferred());
            for (int i = 0; i < control->getLengthTransferred(); i++)
                printf("%02X ", buf[i]);
            printf("\r\n\r\n");
        }
#endif

        if (res != USB_TYPE_IDLE) {
            return res;
        }
    }

    token = (write) ? TD_IN : TD_OUT;
    control->setNextToken(token);
    addTransfer(control, NULL, 0);

    control->ep_queue.get();
    res = control->getState();

    USB_DBG_TRANSFER("CONTROL ack stage %s", control->getStateString());

    if (res != USB_TYPE_IDLE)
        return res;

    return USB_TYPE_OK;
}


void USBHost::fillControlBuf(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, int len)
{
    setupPacket[0] = requestType;
    setupPacket[1] = request;
    setupPacket[2] = (uint8_t) value;
    setupPacket[3] = (uint8_t) (value >> 8);
    setupPacket[4] = (uint8_t) index;
    setupPacket[5] = (uint8_t) (index >> 8);
    setupPacket[6] = (uint8_t) len;
    setupPacket[7] = (uint8_t) (len >> 8);
}
