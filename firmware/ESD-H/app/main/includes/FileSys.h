#ifndef FILESYS_H
#define FILESYS_H

#include <stdio.h> //for prints
#include <string.h> //for strings
#include <sys/unistd.h> //for file open and close
#include <sys/stat.h> //file system interaction
#include "esp_log.h" //for logs
#include "esp_spiffs.h" //spiffs initialization

static const char *TAG_FS = "spiffs";

void fs_init( void );
void fs_deinit( void );

void file_test( void );

#endif