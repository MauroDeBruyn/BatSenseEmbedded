#include "logging.h"

logger* logger::create() {
    static logger instance;
    return &instance;
}

void logger::addLog(const char* meta, const char* message)
{
    char LogPrototype[150];

    int written = snprintf(
        LogPrototype,
        sizeof(LogPrototype),
        log_template,
        meta,
        message
    );

    if (written <= 0) return;

    size_t LogSize = (size_t)written;

    if (LogSize > (sizeof(logs) - size)){
        if(!memset(logs,0, sizeof(logs))) //check if memory was set -> return ptr to area if 0 -> err
        {
            Serial.println("Failed to clear logs memory");            
            return;
        }
        LogSize = 0;
    }

    memcpy(&logs[size], LogPrototype, LogSize);
    size += LogSize;

    logs[size] = '\0';   
}
