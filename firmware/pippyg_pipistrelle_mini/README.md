## TODO ---- BESCHRIJF wat elk folder doet bv psoc6 folder = test data source, andere platform.io project is het resultaat... ----

## **pippyg_pipistrelle_mini**
is a subsection dedicated for the implementation of means to interact with data stored onto an sd card without physically having to transfer data. This allows the user to remotely transfer data without changing having physical contact with the device.

## INLEIDING — Waarom bestaat dit project?
Within the research, various sensors are used, including the Pippyg Pipistrelle Mini, which stores bat audio samples on an SD card. Retrieving this data can be difficult due to the sensor’s positioning, as it requires disconnecting the SD card from the system, transferring the audio files, and then reinstalling the card. To simplify this process, a solution was sought. This led to the idea of wirelessly transferring the data from the device to an other device which are connected.

## DOELSTELLING — Wat moest er op het einde werken?
- The client device establishes a reliable connection to the endpoint.
- An embedded HTTP server provides a user interface for file listing and selection.
- Selected files are downloaded by the client via HTTP.
- SD card data integrity is preserved at all times.
- Sustained data throughput is at least 0.5 MB/s.
- The system operates with low power consumption.
- Hosts sharing the SPI bus use proper arbitration so only one host accesses the bus while the other is blocked.


## RESULTATEN — Wat werkte effectief?
```
---- when only the dataserver is using the spi lane ----
- data transfers at a reasonable speed.
- user interfaces load as expected and work serving users the files he wants to download.

---- when both the info source and dataserver share the spi lane ----
- a deadlock happens which leaves the system in an unuseable state


##TODO ---- BESCHRIJF WAT DE CODE DOET! ----
```

## BESLUIT — Wat hebben jullie hieruit geleerd?
Using a shared spi bus for 2 masters is possible but due to timings, unpredicatble behavior, no control logic, it difficult to create a reliable system.

## references

### hardware present
[ESP8266]()
[GL823K :USB 2.0 SD/MSPRO Card Reader](https://w.electrodragon.com/w/images/c/cb/GL823K.pdf)
[CH340 :USB to serial chip](https://www.mpja.com/download/35227cpdata.pdf)

### Examples && information
- [documentation and examples of the SD-WIFI from fysetc](https://github.com/FYSETC/ESPWebDAV)
- [how SD-cards work indepth](https://elm-chan.org/docs/mmc/mmc_e.html)
