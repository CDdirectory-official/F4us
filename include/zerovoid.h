/*
 *  ZeroVoid Engine - Core Global Interface
 *  Licensed under GNU GPL v3 (2026)
 */

#ifndef ZEROVOID_H
#define ZEROVOID_H

#include <stddef.h>

#define ZV_SUCCESS 0
#define ZV_SUSPICIOUS 1
#define ZV_CRITICAL 99
#define ZV_ERROR -1

typedef struct {
    char file_path[512];
    size_t file_size;
    int threat_score;
    unsigned char magic_header[8];
} ZV_CONTEXT;

/* Function Prototypes */
int zv_analyze_binary(ZV_CONTEXT *ctx);
int zv_deploy_sandbox(const ZV_CONTEXT *ctx);

#endif