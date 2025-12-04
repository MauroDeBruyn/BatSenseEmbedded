#pragma once

#include "string.h"
#include "LittleFS.h"
#include "Arduino.h"

class FS_navigator{
    char directory[20]{""};
    char filenName[20]{""};
    File fileObj;
    char buffer[1024]; //1kb file-buffer
    size_t len;                      

public:
    FS_navigator() {if(!LittleFS.begin()) Serial.println("An Error has occurred while mounting LittleFS");}
    ~FS_navigator() { }
    void ChangeFolder(const char* folderpath);
    bool FileOpen(const char *filename, const char* accesstype);
    bool FileRead();
};