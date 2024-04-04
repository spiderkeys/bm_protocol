#ifndef BCMP_PROTOCOL_CORE_H
#define BCMP_PROTOCOL_CORE_H

#include "bcmp/system/platform.h"
#include "bcmp/api/types.h"
#include "bcmp/protocol/messages/bcmp_messages.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*bcmp_reply_message_cb)(uint8_t *payload);

static constexpr uint32_t BCMP_DEFAULT_REQUEST_TIMEOUT_MS = 24;

int8_t bcmp_sendto( 
    const bcmp_ip_addr_t *dst, 
    bcmp_message_type_t type, 
    uint8_t *buff, 
    uint16_t len,
    uint16_t seq_num=0, 
    bcmp_reply_message_cb reply_cb=NULL,
    uint32_t request_timeout_ms=BCMP_DEFAULT_REQUEST_TIMEOUT_MS );

#ifdef __cplusplus
}
#endif

#endif