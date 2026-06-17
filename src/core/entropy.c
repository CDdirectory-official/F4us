/*
 *  ZeroVoid Engine - Shannon Entropy Mathematical Analysis Engine
 *  Licensed under GNU GPL v3 (2026)
 */

#include "../../include/zerovoid.h"
#include <stdio.h>
#include <math.h>

/* Calculates Shannon Entropy of a file to detect obfuscation/encryption */
double zv_calculate_entropy(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) return -1.0;

    unsigned long long byte_counts[256] = {0};
    unsigned long long total_bytes = 0;
    int current_byte;

    /* Collect frequency analysis of each individual byte */
    while ((current_byte = fgetc(file)) != EOF) {
        byte_counts[current_byte]++;
        total_bytes++;
    }
    fclose(file);

    if (total_bytes == 0) return 0.0;

    double entropy = 0.0;
    
    /* Apply Shannon Entropy Formula: H(X) = -sum(P(xi) * log2(P(xi))) */
    for (int i = 0; i < 256; i++) {
        if (byte_counts[i] > 0) {
            double probability = (double)byte_counts[i] / total_bytes;
            entropy -= probability * (log(probability) / log(2.0));
        }
    }

    return entropy;
}

/* Enhancing core analyzer integration layer */
int zv_check_structural_anomaly(ZV_CONTEXT *ctx) {
    double entropy_score = zv_calculate_entropy(ctx->file_path);
    
    printf("[*] Heuristics: Analyzing binary entropy density... Score: %.4f/8.0000\n", entropy_score);

    /* Cryptors, packers, and hidden shellcodes usually peak above 7.2000 */
    if (entropy_score > 7.2000) {
        printf("[!] Heuristics Warning: High entropy threshold breached! Potential encrypted payload detected.\n");
        ctx->threat_score += 45;
        return ZV_SUSPICIOUS;
    }

    return ZV_SUCCESS;
}