#pragma once

#include <stdint.h>
#include "bristlemouth/bcmp/bcmp.h"
#include <bcmp/protocol/messages/bcmp_messages.h>
#include "configuration.h"
#include "bm_common_structs.h"

using namespace cfg;

void bcmp_config_init(Configuration* user_cfg, Configuration* sys_cfg);
bool bcmp_config_get(uint64_t target_node_id, bm_common_config_partition_e partition, size_t key_len, const char* key, err_t &err, bcmp_reply_message_cb reply_cb = NULL);
bool bcmp_config_set(uint64_t target_node_id, bm_common_config_partition_e partition,
    size_t key_len, const char* key, size_t value_size, void * val, err_t &err, bcmp_reply_message_cb reply_cb = NULL);
bool bcmp_config_commit(uint64_t target_node_id, bm_common_config_partition_e partition, err_t &err);
bool bcmp_config_status_request(uint64_t target_node_id, bm_common_config_partition_e partition, err_t &err, bcmp_reply_message_cb reply_cb = NULL);
bool bcmp_config_status_response(uint64_t target_node_id,bm_common_config_partition_e partition, bool commited, err_t &err);
bool bcmp_config_del_key(uint64_t target_node_id,bm_common_config_partition_e partition, size_t key_len, const char * key, bcmp_reply_message_cb reply_cb = NULL);

bool bcmp_process_config_message(bcmp_message_type_t bcmp_msg_type, uint8_t *payload, uint16_t seq_num);
