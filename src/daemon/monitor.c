/*
 *  ZeroVoid Engine - Asynchronous File System Monitor Daemon
 *  Licensed under GNU GPL v3 (2026)
 *
 *  Description: 
 *  Monitors filesystem directories using Linux native inotify APIs.
 *  Automatically triggers the static analyzer and active response 
 *  subsystems upon detecting newly generated or modified binaries.
 */

#define _GNU_SOURCE
#include "../../include/zerovoid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <limits.h>

#define EVENT_SIZE    (sizeof(struct inotify_event))
#define BUF_LEN       (1024 * (EVENT_SIZE + 16))
#define TARGET_DIR    "/var/zerovoid/uploads"

/* Internal declaration for the soldier counter-attack routine */
int zv_soldier_counter_attack(int fake_pid, const char *infected_path);

int main(int argc, char *argv[]) {
    int length, i = 0;
    int fd;
    int wd;
    char buffer[BUF_LEN];

    printf("==================================================\n");
    printf("   ZEROVOID DAEMON - ACTIVE KERNEL MONITOR        \n");
    printf("   Status: Operational | Engine: Inotify Native   \n");
    printf("==================================================\n");
    printf("[*] Daemon: Initializing core filesystem watcher...\n");

    /* 1. Initialize Inotify Subsystem */
    fd = inotify_init();
    if (fd < 0) {
        perror("[!] Daemon Error: Failed to initialize inotify");
        return ZV_ERROR;
    }

    /* 2. Register Target Watch Directory */
    printf("[*] Daemon: Subscribing to events in target directory: %s\n", TARGET_DIR);
    wd = inotify_add_watch(fd, TARGET_DIR, IN_CLOSE_WRITE | IN_MOVED_TO);
    if (wd == -1) {
        perror("[!] Daemon Error: Cannot watch target directory. Path may not exist");
        close(fd);
        return ZV_ERROR;
    }

    printf("[+] Daemon: Successfully hooked to directory events. Monitoring active processes...\n");

    /* 3. Main Asynchronous Event Loop */
    while (1) {
        i = 0;
        length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            perror("[!] Daemon Error: Failed to read incoming inotify telemetry stream");
            break;
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            
            if (event->len) {
                /* Filter out directory structural modifications, process files only */
                if (!(event->mask & IN_ISDIR)) {
                    printf("\n[*] Daemon: Intercepted system event for file: %s\n", event->name);

                    /* Construct the full canonical path for validation contexts */
                    ZV_CONTEXT ctx;
                    memset(&ctx, 0, sizeof(ZV_CONTEXT));
                    snprintf(ctx.file_path, sizeof(ctx.file_path), "%s/%s", TARGET_DIR, event->name);
                    ctx.threat_score = 0;

                    /* 4. Trigger the Core Analysis Pipeline */
                    int analysis_result = zv_analyze_binary(&ctx);

                    if (analysis_result == ZV_CRITICAL || ctx.threat_score >= 50) {
                        printf("[!!!] THREAT DETECTION: Malicious or obfuscated anomaly identified!\n");
                        printf("[!] Target Vector: %s | Threat Score Factor: %d\n", ctx.file_path, ctx.threat_score);
                        
                        /* 5. Deploy Active Defense: The Soldier Protocol 
                         * Passes a generic zeroed PID or tracked subsystem context for termination */
                        zv_soldier_counter_attack(0, ctx.file_path);
                    } 
                    else if (analysis_result == ZV_SUSPICIOUS) {
                        printf("[*] Telemetry: Medium risk structure detected. Deploying namespace isolation...\n");
                        zv_deploy_sandbox(&ctx);
                    } 
                    else {
                        printf("[+] Telemetry: File passed automated heuristic checks. Signature clear.\n");
                    }
                }
            }
            /* Shift buffer pointer to the next consecutive filesystem event structure */
            i += EVENT_SIZE + event->len;
        }
    }

    /* 6. Graceful Degradation Cleanups */
    inotify_rm_watch(fd, wd);
    close(fd);
    printf("[*] Daemon: Subsystem unhooked. Monitor shutting down gracefully.\n");
    return ZV_SUCCESS;
}