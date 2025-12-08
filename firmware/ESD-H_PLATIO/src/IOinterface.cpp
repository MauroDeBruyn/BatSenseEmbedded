#include "IOinterface.h"

volatile unsigned long SDinterface::_spiBlockoutTime = 0;
bool SDinterface::_weTookBus = false;
SDinterface* instance = nullptr;

void IRAM_ATTR SDGiveControl() {
    if(instance){
        if (!instance->_weTookBus){
            instance->_spiBlockoutTime = millis() + SPI_BLOCKOUT_PERIOD;
            instance->logs->addLog("sd-card", "failed to take bus");
            Serial.println("failed to take the bus");
            instance->logs->addLog("SD-card", "failed to take the bus");
        }else{
            Serial.println("We have the bus");
            instance->logs->addLog("SD-card", "We have the bus");
        }
    }
}
void IRAM_ATTR SDIdleControl() {
    if(instance){
        Serial.println("control of bus has been freed");
        instance->logs->addLog("SD-card", "control freed");
    }
}

SDinterface::SDinterface()
{
    instance = this;
    logs = logger::create();
    pinMode(CS_SENSE, INPUT); // detect when other master is using spi
    attachInterrupt(CS_SENSE, SDGiveControl, FALLING);
    attachInterrupt(CS_SENSE, SDIdleControl, RISING);
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

String SDinterface::sdFiles_HTML_Format()
{
    
    /*File root = SD.open("/");
    if (!root || !root.isDirectory())
    {
        return "";
    }

    String html =
        "<!doctype html><html><head>"
        "<meta charset='utf-8'>"
        "<title>SD Browser</title>"
        "<style>"
        "body{font-family:monospace;background:#111;color:#0f0;padding:20px}"
        "a{color:#0ff;text-decoration:none}"
        "</style></head><body><h2>SD Files</h2><ul>";

    for (;;)
    {
       File file = root.openNextFile();
        if (!file)
            break;

        String name = file.name();
        html += "<li><a href='/sd?f=" + name + "'>" + name + "</a> (";
        html += file.size();
        html += " bytes)</li>";

        file.close(); // REQUIRED
        yield();      // keep TCP alive
    }

    root.close();

    html += "</ul></body></html>";
    return html;*/
    return "work in progress";
}
