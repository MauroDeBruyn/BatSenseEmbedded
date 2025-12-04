#pragma once
#include <Arduino.h>

#define LOG_OUT_OF_MEMORY 20
class logger{
    logger(){}
    ~logger(){}
    char logs[10240];
    size_t size{0};
    const char* log_template= "[ %s ] : %s\n";
public: 
    static logger* create();
    inline char* getLogs(){return logs;}
    void addLog(const char* meta, const char* message);
};