/*
 *  ZeroVoid Engine - Active Response Daemon (The Soldier Module)
 *  Licensed under GNU GPL v3 (2026)
 */

#include "../../include/zerovoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

/* Active Hunter Function to Counter Malicious Processes */
int zv_soldier_counter_attack(pid_t rogue_pid, const char *infected_path) {
    printf("[!] ZV-SOLDIER: Active combat agent deployed against PID [%d].\n", rogue_pid);

    // 1. Terminate the malicious process immediately at kernel level (SIGKILL)
    if (kill(rogue_pid, SIGKILL) == 0) {
        printf("[+] ZV-SOLDIER: Successfully neutralized hostile process [%d].\n", rogue_pid);
    } else {
        fprintf(stderr, "[!] ZV-SOLDIER Error: Failed to terminate process [%d]. Escalating privileges required.\n", rogue_pid);
        return ZV_ERROR;
    }

    // 2. Quarantine and shred the source file so it cannot restart
    printf("[*] ZV-SOLDIER: Purging malicious binary from system storage...\n");
    
    // Revoke all read/write/execute permissions from the file (Shredding access)
    if (chmod(infected_path, 0000) == 0) {
        printf("[+] ZV-SOLDIER: File permissions revoked (0000). Threat isolated.\n");
    } else {
        printf("[*] ZV-SOLDIER Warning: Could not alter file permissions. Proceeding to deletion.\n");
    }

    // Delete the file from disk
    if (remove(infected_path) == 0) {
        printf("[+] ZV-SOLDIER: Rogue binary '%s' has been deleted successfully.\n", infected_path);
    } else {
        fprintf(stderr, "[!] ZV-SOLDIER Error: Deficit permissions to delete file. Manual quarantine required.\n");
        return ZV_ERROR;
    }

    printf("[+] ZV-SOLDIER: System integrity restored. Returning to active standby mode.\n");
    return ZV_SUCCESS;
}