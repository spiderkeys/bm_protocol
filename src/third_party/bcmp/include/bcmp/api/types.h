#ifndef BCMP_API_TYPES_H
#define BCMP_API_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Address Types
enum bcmp_ip_addr_type {
  BCMP_IPADDR_TYPE_V4 =   0U,
  BCMP_IPADDR_TYPE_V6 =   6U
};

// IPv4 Address
struct _bcmp_ip4_addr {
  uint32_t addr;
};
typedef struct _bcmp_ip4_addr bcmp_ip4_addr_t;

// IPv6 Address
struct _bcmp_ip6_addr {
  uint32_t addr[4];
};
typedef struct _bcmp_ip6_addr bcmp_ip6_addr_t;

// IP Address
typedef struct _bcmp_ip_addr {
  union {
    bcmp_ip6_addr_t ip6;
    bcmp_ip4_addr_t ip4;
  } u_addr;
  uint8_t type;
} bcmp_ip_addr_t;

#ifdef __cplusplus
}
#endif


#endif /* BCMP_API_TYPES_H */