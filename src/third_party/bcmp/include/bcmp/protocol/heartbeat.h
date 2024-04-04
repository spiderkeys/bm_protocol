#ifndef BCMP_PROTOCOL_HEARTBEAT_H
#define BCMP_PROTOCOL_HEARTBEAT_H

#include <stdint.h>

int8_t bcmp_send_heartbeat( uint32_t lease_duration_s );

#endif /* BCMP_PROTOCOL_HEARTBEAT_H */