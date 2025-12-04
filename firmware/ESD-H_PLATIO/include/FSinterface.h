#pragma once

#include "string.h"
#include "LittleFS.h"
#include "Arduino.h"

class FS_navigator{
    char directory[20]{""};
    char filenName[20]{""};
    File fileObj;
    char buffer[10240]; //1kb file-buffer
    size_t len{0};                      

public:
    FS_navigator() {if(!LittleFS.begin()) Serial.println("An Error has occurred while mounting LittleFS");}
    ~FS_navigator() { }
    void ChangeFolder(const char* folderpath);
    bool FileOpen(const char *filename, const char* accesstype);
    bool FileRead();
    inline char* bufferPtr(){return buffer;}
};