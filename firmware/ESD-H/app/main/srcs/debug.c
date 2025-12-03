#include "debug.h"

int append_err(char* buffer, const char* data){
    strcat(buffer, data);
    strcat(buffer, "\n");
    return 0;
}
