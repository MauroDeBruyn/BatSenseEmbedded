#include "FSinterface.h"

void FS_navigator::ChangeFolder(const char* folderpath) {
    memcpy(directory, folderpath, strlen(folderpath) + 1);
}

bool FS_navigator::FileOpen(const char *filename, const char* accesstype){
    if (fileObj) fileObj.close();

    memcpy(filenName, filename, strlen(filename) + 1);

    if (directory[0] != '\0') {
        char path[42];

        memcpy(path, directory, strlen(directory));
        path[strlen(directory)] = '/';

        memcpy(path + strlen(directory) + 1,
               filenName,
               strlen(filenName) + 1);

        fileObj = LittleFS.open(path, accesstype);
        Serial.printf("--- FileOpen --- path: %s\n", path);
    } else {
        fileObj = LittleFS.open(filenName, accesstype);
        Serial.printf("--- FileOpen --- path: %s\n", filenName);
    }

    return fileObj;
}

bool FS_navigator::FileRead() {
    if (!fileObj) return false;

    len = fileObj.size();
    if (len >= sizeof(buffer)) len = sizeof(buffer);

    fileObj.readBytes(buffer, len);
    buffer[len] = '\0';

    Serial.println("--- FileRead --- content:");
    Serial.write((uint8_t*)buffer, len);

    return true;
}

