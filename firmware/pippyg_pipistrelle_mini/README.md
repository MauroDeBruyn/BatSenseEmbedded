## **pippyg_pipistrelle_mini**
is a subsection dedicated for the implementation of means to interact with data stored onto an sd card without physically having to transfer data. This allows the user to remotely transfer data without changing having physical contact with the device.

## introduction
Within the research, various sensors are used, including the Pippyg Pipistrelle Mini, which stores bat audio samples on an SD card. Retrieving this data can be difficult due to the sensor’s positioning, as it requires disconnecting the SD card from the system, transferring the audio files, and then reinstalling the card. To simplify this process, a solution was sought. This led to the idea of wirelessly transferring the data from the device to an other device which are connected.

## Goals
- [ ] The client device establishes a reliable connection to the endpoint.
- [x] An embedded HTTP server provides a user interface for file listing and selection.
- [x] Selected files are downloaded by the client via HTTP.
- [ ] SD card data integrity is preserved at all times.
- [x] Sustained data throughput is at least 0.5 MB/s.
- [x] The system operates with low power consumption.
- [ ] Hosts sharing the SPI bus use proper arbitration so only one host accesses the bus while the other is blocked.


## Results

### SPI Usage and System Reliability

- **Only the data server using the SPI bus**
  - Data transfers operate at a stable and acceptable speed.
  - User interfaces load correctly.
  - Files are served and downloaded without issues.

- **Data server and information source sharing the SPI bus**
  - A deadlock occurs.
  - The system enters an unrecoverable, unusable state.

### Functional Behavior

- An LED on GPIO pin 2 acts as a heartbeat indicator and toggles approximately every 61 seconds to show that the main loop is still running.
- An HTTP server runs in Access Point mode and serves a main page generated from the current SD card contents.
- A global SD interface provides HTML-formatted file listings to the HTTP server.
- Access to the SPI bus is controlled via a chip-select state and an SPI blockout timer to prevent concurrent access.


## Conclusion

Using a shared SPI bus with two masters is technically possible, but in practice it introduces significant challenges. Timing constraints, unpredictable behavior, and the absence of strict ownership and arbitration logic make the system unreliable in its current form.

Without a single, centralized control mechanism for SPI access, contention can easily lead to deadlocks and unrecoverable states. However, with architectural changes—such as clearly defined bus ownership, proper arbitration, and encapsulated SPI access control—a shared SPI bus can be used reliably.

## references

### hardware present
[GL823K :USB 2.0 SD/MSPRO Card Reader](https://w.electrodragon.com/w/images/c/cb/GL823K.pdf)
[CH340 :USB to serial chip](https://www.mpja.com/download/35227cpdata.pdf)

### Examples && information
- [documentation and examples of the SD-WIFI from fysetc](https://github.com/FYSETC/ESPWebDAV)
- [how SD-cards work indepth](https://elm-chan.org/docs/mmc/mmc_e.html)
