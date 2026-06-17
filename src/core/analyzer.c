/*
 *  ZeroVoid Engine - Static Binary Analyzer & Entropy Detector
 *  Licensed under GNU GPL v3 (2026)
 */

#include "../../include/zerovoid.h"
#include <stdio.h>
#include <math.h>

int zv_analyze_binary(ZV_CONTEXT *ctx) {
    FILE *file = fopen(ctx->file_path, "rb");
    if (!file) return ZV_ERROR;

    // Read Magic Bytes
    size_t bytes_read = fread(ctx->magic_header, 1, 8, file);
    if (bytes_read < 4) {
        fclose(file);
        return ZV_ERROR;
    }

    // 1. Deep Magic Bytes Validation
    if (ctx->magic_header[0] == 0x4D && ctx->magic_header[1] == 0x5A) {
        ctx->threat_score += 10; // Executable found, elevate monitoring
    } else if (ctx->magic_header[0] == '<' && ctx->magic_header[1] == '?') {
        fclose(file);
        return ZV_CRITICAL; // Direct Web Shell bypass attempt
    }

    // 2. High Entropy / Packer Detection Logic (Mathematical Approximation)
    unsigned int byte_counts[256] = {0};
    int total_bytes = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        byte_counts[ch]++;
        total_bytes++;
    }
    fclose(file);

    // Calculate basic data density
    int unique_bytes = 0;
    for (int i = 0; i < 256; i++) {
        if (byte_counts[i] > 0) unique_bytes++;
    }

    // If data is extremely dense/randomized, it's encrypted/packed malware
    if (unique_bytes > 240 && total_bytes > 1024) {
        ctx->threat_score += 50; // High probability of an obfuscated payload
    }

    return (ctx->threat_score >= 50) ? ZV_SUSPICIOUS : ZV_SUCCESS;
}