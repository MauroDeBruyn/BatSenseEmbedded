#ifndef SD_READER_H
#define SD_READER_H

#include "debug.h"

#define SD_CS		4
#define MISO_PIN		12
#define MOSI_PIN		13
#define SCLK_PIN		14
#define CS_SENSE	5

void SDcontrol_init();
void SDcontrol_monitorBus();
void SDcontrol_takeBus();
void SDcontrol_giveBus();

extern char errbuffer[20480]; //20kb

#endif