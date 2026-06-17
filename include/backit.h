/*
 * F4us Backit: Unified System Architecture Headers
 * Licensed under GNU GPL v3 (2026)
 */

#ifndef F4US_BACKIT_H
#define F4US_BACKIT_H

/* --- PURE LINUX CORE SYSTEM HEADERS --- */
#include <stdio.h>      // For standard Input/Output streams (printf, fopen, fread)
#include <stdlib.h>     // For standard memory allocations and system utilities (malloc, system)
#include <string.h>     // For raw memory & string manipulation operations (strstr, strcmp)
#include <unistd.h>     // For POSIX kernel API wrappers (unlink, sleep, getuid)
#include <dirent.h>     // For directory stream processing structures (DIR, readdir)
#include <sys/stat.h>   // For filesystem mode and file attributes modification

/* --- GLOBAL CORE ARCHITECTURE CONFIGURATION --- */
#define MAX_MALWARE_SIGNATURES 3
#define TARGET_DIR "/tmp" // The dynamic battlefield zone for hunting viruses

/* --- CORE FUNCTIONS PROTOTYPES --- */
void f4us_backit_stealth_init(void);
void f4us_hunt_and_destroy(void);

#endif
