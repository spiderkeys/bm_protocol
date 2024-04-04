#include "bcmp/protocol/heartbeat.h"

#include "bcmp/protocol/core.h"
#include "bcmp/protocol/messages/bcmp_messages.h"

int8_t bcmp_send_heartbeat( uint32_t lease_duration_s )
{
    bcmp_heartbeat_t heartbeat = {
        .time_since_boot_us = uptimeGetMicroSeconds(),
        .liveliness_lease_dur_s = lease_duration_s
    };

    return bcmp_tx(&multicast_ll_addr, BCMP_HEARTBEAT, (uint8_t *)&heartbeat, sizeof(heartbeat));

    return 0;
}