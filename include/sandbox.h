/*
 *  ZeroVoid Engine - Sandbox Environment Blueprint Interface
 *  Licensed under GNU GPL v3 (2026)
 */

#ifndef ZEROVOID_SANDBOX_H
#define ZEROVOID_SANDBOX_H

#include "zerovoid.h"

/* Allocation of 64KB stack memory execution space for the jailed process */
#define ZV_SANDBOX_STACK_SIZE (1024 * 64)

/* Function Prototypes for Isolation Management */
int jail_child_process(void *arg);
int zv_deploy_sandbox(const ZV_CONTEXT *ctx);

#endif