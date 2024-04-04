#ifndef __BM_L2_H__
#define __BM_L2_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "lwip/netif.h"
#include "bm_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* We store the egress port for the RX device and the ingress port of the TX device
   in bytes 5 (index 4) and 6 (index 5) of the SRC IPv6 address. */
#define EGRESS_PORT_IDX     4
#define INGRESS_PORT_IDX    5

/* Ingress and Egress ports are mapped to the 5th and 6th byte of the IPv6 src address as per
    the bristlemouth protocol spec */
#define CLEAR_PORTS(x) (x[1] &= (~(0xFFFFU)))

/* IPv6 is stored in uint32_t array of size 4 */
enum {
    IPV6_ADDR_DWORD_0,
    IPV6_ADDR_DWORD_1,
    IPV6_ADDR_DWORD_2,
    IPV6_ADDR_DWORD_3
};
typedef void (*bm_l2_link_change_cb_t)(uint8_t port, bool state);

err_t bm_l2_tx(struct pbuf *p, uint8_t port_mask);
err_t bm_l2_rx(void* device_handle, uint8_t* payload, uint16_t payload_len, uint8_t port_mask);
err_t bm_l2_link_output(struct netif *netif, struct pbuf *p);
err_t bm_l2_netif_init(struct netif *netif);
err_t bm_l2_init(bm_l2_link_change_cb_t link_change_cb);
void bm_l2_netif_set_power(void * dev, bool on);

bool bm_l2_get_device_handle(uint8_t dev_idx, void **device_handle, bm_netdev_type_t *type, uint32_t *start_port_idx);
uint8_t bm_l2_get_num_ports();
bool bm_l2_get_port_state(uint8_t port);

#ifdef __cplusplus
}
#endif

#endif /* __BM_L2_H__ */
