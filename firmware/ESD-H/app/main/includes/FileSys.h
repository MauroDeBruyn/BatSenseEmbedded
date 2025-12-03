#ifndef FILESYS_H
#define FILESYS_H

#include <stdio.h> //for prints
#include <string.h> //for strings
#include <sys/unistd.h> //for file open and close
#include <sys/stat.h> //file system interaction
#include "esp_log.h" //for logs
#include "esp_spiffs.h" //spiffs initialization

#include <dirent.h>
#include <sys/stat.h>

void fs_init( void );
void fs_deinit( void );

void ls_spiffs(const char *path);
void file_test( void );

extern char errbuffer[20480]; //20kb
#endif