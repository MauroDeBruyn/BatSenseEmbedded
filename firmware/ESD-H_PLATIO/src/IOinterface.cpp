#include "IOinterface.h"

volatile unsigned long SDinterface::_spiBlockoutTime = 0;
bool SDinterface::_weTookBus = false;
SDinterface* instance= nullptr;

void IRAM_ATTR SDGiveControl() {
    if(instance){
        instance->logs->addLog("sd-card", "failed to take bus");
    }
    if (!SDinterface::_weTookBus)
        SDinterface::_spiBlockoutTime = millis() + SPI_BLOCKOUT_PERIOD;
}

SDinterface::SDinterface()
{
    instance = this;
    logs = logger::create();
    // Detect when other master uses SPI bus
    pinMode(CS_SENSE, INPUT);
    attachInterrupt(CS_SENSE, SDGiveControl, FALLING);
}

void SDinterface::takeBusControl()
{
    _weTookBus = true;
    pinMode(MISO_PIN, SPECIAL);
    pinMode(MOSI_PIN, SPECIAL);
    pinMode(SCLK_PIN, SPECIAL);
    pinMode(SD_CS, OUTPUT);
}

void SDinterface::relinquishBusControl()
{
    pinMode(MISO_PIN, INPUT);
    pinMode(MOSI_PIN, INPUT);
    pinMode(SCLK_PIN, INPUT);
    pinMode(SD_CS, INPUT);
    _weTookBus = false;
}

bool SDinterface::canWeTakeBus()
{
    if (millis() < _spiBlockoutTime)
    {
        return false;
    }
    return true;
}

bool SDinterface::read_file(const char *filename)
{
    if (!canWeTakeBus())
    {
        logs->addLog("sd-card", "failed to take bus");
        return 1;
    }
    takeBusControl();

    if (!sdfat.begin(SD_CS, SPI_FULL_SPEED))
    {
        logs->addLog("sd-card", "initialization of SD failed");
        relinquishBusControl();
        return 1;
    }

    File32 file = sdfat.open(filename, FILE_READ);
    if (!file)
    {
        logs->addLog("sd-card", "failed to open file");
        relinquishBusControl();
        return 1;
    }

    logs->addLog("SD-card string read from file:", file.readString().c_str());

    relinquishBusControl();
    return 0;
}