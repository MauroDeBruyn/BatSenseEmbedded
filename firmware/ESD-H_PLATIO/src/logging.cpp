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

    if (LogSize > (sizeof(logs) - size))
        return;   // out of memory, drop log

    memcpy(&logs[size], LogPrototype, LogSize);
    size += LogSize;

    logs[size] = '\0';   
}
