/*
 * Copyright (c) 2018      Los Alamos National Security, LLC
 *                         All rights reserved.
 *
 * This file is part of the sdsdkv project. See the LICENSE file at the
 * top-level directory of this distribution.
 */

/**
 * @file sdsdkv-config.h
 */

#pragma once

#include "sdsdkv.h"
#include "sdskv-common.h"

#include <cstdlib>

static inline bool
config_valid(
    const sdsdkv_config &config
) {
    switch (config.personality) {
        case SDSDKV_PERSONALITY_CLIENT:
        case SDSDKV_PERSONALITY_SERVER:
            break;
        default:
            return false;
    }
    //
    switch (config.hash_be) {
        case SDSDKV_HASHING_CH_PLACEMENT:
            break;
        default:
            return false;
    }
    //
    switch (config.db_type) {
        case SDSDKV_DB_MAP:
        case SDSDKV_DB_LEVELDB:
            break;
        default:
            return false;
    }
    //
    return true;
}

static inline sdskv_db_type_t
config_get_real_db_type(
    const sdsdkv_config &config
) {
    switch (config.db_type) {
        case SDSDKV_DB_MAP:
            return KVDB_MAP;
        case SDSDKV_DB_LEVELDB:
            return KVDB_LEVELDB;
        default:
            return sdskv_db_type_t(-187);
    }
}

static inline int
config_dup_destroy(
    sdsdkv_config **config_dup
) {
    if (config_dup) {
        if (*config_dup) {
            sdsdkv_config *tc = *config_dup;
            if (tc->db_name) free(tc->db_name);
            if (tc->comm_protocol) free(tc->comm_protocol);
            free(tc);
        }
        *config_dup = NULL;
    }
    return SDSDKV_SUCCESS;
}

static inline int
config_dup(
    const sdsdkv_config &config,
    sdsdkv_config **config_dup
) {
    int rc = SDSDKV_SUCCESS;

    sdsdkv_config *tc = (sdsdkv_config *)calloc(1, sizeof(*tc));
    if (!tc) return SDSDKV_ERR_OOR;

    tc->init_comm = config.init_comm;
    tc->personality = config.personality;
    tc->hash_be = config.hash_be;
    // TODO(skg) may need to check for NULL here. The idea being that perhaps a
    // user can pass NULL here to mean something...
    if (-1 == asprintf(&(tc->db_name), "%s", config.db_name)) {
        tc->db_name = NULL;
        rc = SDSDKV_ERR_OOR;
        goto out;
    }
    if (-1 == asprintf(&(tc->comm_protocol), "%s", config.comm_protocol)) {
        tc->comm_protocol = NULL;
        rc = SDSDKV_ERR_OOR;
        goto out;
    }
out:
    if (rc != SDSDKV_SUCCESS) {
        config_dup_destroy(&tc);
    }

    *config_dup = tc;

    return SDSDKV_SUCCESS;
}

/*
 * vim: ft=cpp ts=4 sts=4 sw=4 expandtab
 */
