#
# Bristlemouth files/includes
#
set(BRISTLEMOUTH_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(BRISTLEMOUTH_SOURCES
    # BCMP (migrating into actual bcmp library)
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_cli.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_config.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_time.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_heartbeat.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_info.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_linked_list_generic.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_neighbors.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_ping.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_topology.cpp
    ${BRISTLEMOUTH_DIR}/src/bcmp/bcmp_resource_discovery.cpp

    # DFU
    ${BRISTLEMOUTH_DIR}/src/dfu/bm_dfu_client.cpp
    ${BRISTLEMOUTH_DIR}/src/dfu/bm_dfu_core.cpp
    ${BRISTLEMOUTH_DIR}/src/dfu/bm_dfu_host.cpp

    # Bristlemouth Core
    ${BRISTLEMOUTH_DIR}/src/bm/bm_l2.cpp
    ${BRISTLEMOUTH_DIR}/src/bm/bm_util.c
    ${BRISTLEMOUTH_DIR}/src/bm/bm_printf.cpp
    ${BRISTLEMOUTH_DIR}/src/bm/bristlemouth.cpp
PARENT_SCOPE)

set(BRISTLEMOUTH_INCLUDE_DIRS
    ${BRISTLEMOUTH_DIR}/include
PARENT_SCOPE)