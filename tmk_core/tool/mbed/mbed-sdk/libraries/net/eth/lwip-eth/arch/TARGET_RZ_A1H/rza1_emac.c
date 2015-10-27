#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "mbed_interface.h"
#include "ethernet_api.h"
#include "ethernetext_api.h"

#define RECV_TASK_PRI           (osPriorityNormal)
#define PHY_TASK_PRI            (osPriorityNormal)
#define PHY_TASK_WAIT           (200)

/* memory */
static sys_sem_t recv_ready_sem;    /* receive ready semaphore */

/* function */
static void rza1_recv_task(void *arg);
static void rza1_phy_task(void *arg);
static err_t rza1_etharp_output(struct netif *netif, struct pbuf *q, ip_addr_t *ipaddr);
static err_t rza1_low_level_output(struct netif *netif, struct pbuf *p);
static void rza1_recv_callback(void);

static void rza1_recv_task(void *arg) {
    struct netif   *netif = (struct netif*)arg;
    struct eth_hdr *ethhdr;
    u16_t          recv_size;
    struct pbuf    *p;
    struct pbuf    *q;

    while (1) {
        sys_arch_sem_wait(&recv_ready_sem, 0);
        recv_size = ethernet_receive();
        if (recv_size != 0) {
            p = pbuf_alloc(PBUF_RAW, recv_size, PBUF_POOL);
            if (p != NULL) {
                for (q = p; q != NULL; q = q->next) {
                    (void)ethernet_read((char *)q->payload, q->len);
                }
                ethhdr = p->payload;
                switch (htons(ethhdr->type)) {
                    case ETHTYPE_IP:
                    case ETHTYPE_ARP:
#if PPPOE_SUPPORT
                    case ETHTYPE_PPPOEDISC:
                    case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
                        /* full packet send to tcpip_thread to process */
                        if (netif->input(p, netif) != ERR_OK) {
                            /* Free buffer */
                            pbuf_free(p);
                        }
                        break;
                    default:
                        /* Return buffer */
                        pbuf_free(p);
                        break;
                }
            }
        }
    }
}

static void rza1_phy_task(void *arg) {
    struct netif *netif = (struct netif*)arg;
    s32_t        connect_sts = 0;   /* 0: disconnect, 1:connect */
    s32_t        link_sts;
    s32_t        link_mode_new = NEGO_FAIL;
    s32_t        link_mode_old = NEGO_FAIL;

    while (1) {
        link_sts = ethernet_link();
        if (link_sts == 1) {
            link_mode_new = ethernetext_chk_link_mode();
            if (link_mode_new != link_mode_old) {
                if (connect_sts == 1) {
                    tcpip_callback_with_block((tcpip_callback_fn)netif_set_link_down, (void*) netif, 1);
                }
                if (link_mode_new != NEGO_FAIL) {
                    ethernetext_set_link_mode(link_mode_new);
                    tcpip_callback_with_block((tcpip_callback_fn)netif_set_link_up, (void*) netif, 1);
                    connect_sts = 1;
                }
            }
        } else {
            if (connect_sts != 0) {
                tcpip_callback_with_block((tcpip_callback_fn)netif_set_link_down, (void*) netif, 1);
                link_mode_new = NEGO_FAIL;
                connect_sts   = 0;
            }
        }
        link_mode_old = link_mode_new;
        osDelay(PHY_TASK_WAIT);
    }
}

static err_t rza1_etharp_output(struct netif *netif, struct pbuf *q, ip_addr_t *ipaddr) {
    /* Only send packet is link is up */
    if (netif->flags & NETIF_FLAG_LINK_UP) {
        return etharp_output(netif, q, ipaddr);
    }

    return ERR_CONN;
}

static err_t rza1_low_level_output(struct netif *netif, struct pbuf *p) {
    struct pbuf *q;
    s32_t       cnt;
    err_t       err        = ERR_MEM;
    s32_t       write_size = 0;

    if ((p->payload != NULL) && (p->len != 0)) {
        /* If the first data can't be written, transmit descriptor is full. */
        for (cnt = 0; cnt < 100; cnt++) {
            write_size = ethernet_write((char *)p->payload, p->len);
            if (write_size != 0) {
                break;
            }
            osDelay(1);
        }
        if (write_size != 0) {
            for (q = p->next; q != NULL; q = q->next) {
                (void)ethernet_write((char *)q->payload, q->len);
            }
            if (ethernet_send() == 1) {
                err = ERR_OK;
            }
        }
    }

    return err;
}

static void rza1_recv_callback(void) {
    sys_sem_signal(&recv_ready_sem);
}

err_t eth_arch_enetif_init(struct netif *netif)
{
    ethernet_cfg_t ethcfg;

    /* set MAC hardware address */
#if (MBED_MAC_ADDRESS_SUM != MBED_MAC_ADDR_INTERFACE)
    netif->hwaddr[0] = MBED_MAC_ADDR_0;
    netif->hwaddr[1] = MBED_MAC_ADDR_1;
    netif->hwaddr[2] = MBED_MAC_ADDR_2;
    netif->hwaddr[3] = MBED_MAC_ADDR_3;
    netif->hwaddr[4] = MBED_MAC_ADDR_4;
    netif->hwaddr[5] = MBED_MAC_ADDR_5;
#else
    mbed_mac_address((char *)netif->hwaddr);
#endif
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP;

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "lwiprza1";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = 'e';
    netif->name[1] = 'n';

    netif->output     = rza1_etharp_output;
    netif->linkoutput = rza1_low_level_output;

    /* Initialize the hardware */
    ethcfg.int_priority = 6;
    ethcfg.recv_cb      = &rza1_recv_callback;
    ethcfg.ether_mac    = (char *)netif->hwaddr;
    ethernetext_init(&ethcfg);

    /* semaphore */
    sys_sem_new(&recv_ready_sem, 0);

    /* task */
    sys_thread_new("rza1_recv_task", rza1_recv_task, netif, DEFAULT_THREAD_STACKSIZE, RECV_TASK_PRI);
    sys_thread_new("rza1_phy_task", rza1_phy_task, netif, DEFAULT_THREAD_STACKSIZE, PHY_TASK_PRI);

    return ERR_OK;
}

void eth_arch_enable_interrupts(void) {
    ethernetext_start_stop(1);
}

void eth_arch_disable_interrupts(void) {
    ethernetext_start_stop(0);
}
