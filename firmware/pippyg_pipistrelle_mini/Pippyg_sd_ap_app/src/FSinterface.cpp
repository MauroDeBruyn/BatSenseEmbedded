#include "FSinterface.h"

void FS_navigator::ChangeFolder(const char* folderpath) {
    memcpy(directory, folderpath, strlen(folderpath) + 1);
}

bool FS_navigator::FileOpen(const char *filename, const char* accesstype){
    if (fileObj) fileObj.close(); 

    if(memcpy(filenName, filename, strlen(filename) + 1) == NULL){
       Serial.println("failed to execute memcpy"); 
    }

    if (directory[0] != '\0') {
        char path[42];

        if(memcpy(path, directory, strlen(directory)) == NULL){
            Serial.println("failed to execute memcpy"); 
        }
        
        path[strlen(directory)] = '/';

        if(memcpy(path + strlen(directory) + 1, filenName, strlen(filenName) + 1) == NULL){
            Serial.println("failed to execute memcpy"); 
        };

        fileObj = LittleFS.open(path, accesstype);
        if(!fileObj)
            Serial.println("failed to open the file"); 
    } else {
        fileObj = LittleFS.open(filenName, accesstype);
        if (!fileObj)
            Serial.println("failed to open the file");
    }

    return 1;
}

bool FS_navigator::FileRead()
{
    if (!fileObj)
        return false;

    len = fileObj.size();
    if (len >= sizeof(buffer)){

        len = sizeof(buffer); //if buffered data is too large just cut the last part
        Serial.println("Warning: file read exceeds buffer, data truncated");
    } 

    fileObj.readBytes(buffer, len);
    buffer[len] = '\0';

    return true;
}
