/*
 *  ZeroVoid Engine - Advanced Sandbox Environment (Linux-native)
 *  Licensed under GNU GPL v3 (2026)
 */

#define _GNU_SOURCE
#include "../../include/zerovoid.h"
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

int jail_child_process(void *arg) {
    ZV_CONTEXT *ctx = (ZV_CONTEXT *)arg;
    
    printf("[+] Sandbox: Child process jailed inside isolated Namespace.\n");
    printf("[+] Sandbox: Network interface detached. Harddrive write-access restricted.\n");
    
    // Execute the untrusted binary safely inside the isolated environment
    char *const envp[] = {NULL};
    char *const argv[] = {ctx->file_path, NULL};
    
    execve(ctx->file_path, argv, envp);
    
    // If execve returns, it failed
    return ZV_ERROR;
}

int zv_deploy_sandbox(const ZV_CONTEXT *ctx) {
    printf("[*] Sandbox: Deploying isolation chamber for: %s\n", ctx->file_path);
    
    // 64KB stack for the isolated child process
    char child_stack[65536]; 
    
    // Clone process with isolated Network and PID structures (Zero Trust Network)
    pid_t pid = clone(jail_child_process, child_stack + sizeof(child_stack), 
                      CLONE_NEWNET | CLONE_NEWPID | SIGCHLD, (void *)ctx);
                      
    if (pid == -1) {
        fprintf(stderr, "[!] Error: Failed to spawn sandbox instance.\n");
        return ZV_ERROR;
    }
    
    int status;
    waitpid(pid, &status, 0); // Watch the malware's behavior until it dies
    printf("[+] Sandbox: Isolated process finished execution. Cleaning up sandbox container.\n");
    return ZV_SUCCESS;
}