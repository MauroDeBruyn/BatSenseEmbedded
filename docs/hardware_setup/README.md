## Section Introduction

This section describes the steps required to prepare the hardware and install Home Assistant OS on a Raspberry Pi. It assumes the hardware components are already available and focuses on bringing the central system into an operational state.

## Overview
- [Setting up the Router](#setting-up-the-router)
  - [Router Prerequisites](#router-prerequisites)
- [Installing Home Assistant](#installing-home-assistant)
  - [Home Assistant Prerequisites](#home-assistant-prerequisites)
  - [OS Flashing](#os-flashing)
  - [Raspberry Pi Hardware Setup](#raspberry-pi-hardware-setup)
- [References](#references)

## Setting up the Router

### Router Prerequisites
- **TP-Link TL-MR6400 Wireless N 4G-LTE router**
  - Power supply: 9 V DC / 0.85 A  
  - Ethernet connection: Cat5/6

```
todo:
mauro schrijf hier ovr de router setup etc...
```

## Installing Home Assistant

### Home Assistant Prerequisites
- **SD card**
  - Minimum capacity: 32 GB

- **Raspberry Pi**
  - Raspberry Pi 4 or Raspberry Pi 5  
  - Ethernet connection: Cat5/6  
  - Raspberry Pi power supply

- **Computer**
  - Windows operating system  
  - SD card reader or SD card slot  
  - At least 10 GB of free storage space

### OS Flashing

1. Download and install [**Raspberry Pi Imager**](https://www.raspberrypi.com/software/) on the computer.
2. Open Raspberry Pi Imager and select the appropriate Raspberry Pi model.
3. Configure the following settings:
   - **Device**: Raspberry Pi 4 or Raspberry Pi 5  
     ![Raspberry Pi version selection](/resources/documentation_media/Home_Assistant_Setup/RPI_Version.png)
   - **Operating System**:  
     Select *Other specific-purpose OS* → *Home assistants and home automation* → *Home Assistant OS*  
     ![Home Assistant OS selection](/resources/documentation_media/Home_Assistant_Setup/CHOOSE_OS_RPI_imager.png)
4. Insert the SD card into the computer.  
   *Note: all existing data on the SD card will be erased.*
5. Select the correct SD card and proceed with flashing.
6. Wait until the Home Assistant OS image has been successfully written to the SD card.

### Raspberry Pi Hardware Setup

1. Insert the flashed SD card into the Raspberry Pi.
2. Connect the Raspberry Pi to the network using an Ethernet cable.  
   Ensure it is connected to the same network as the computer and has internet access.
3. Connect the power supply to the Raspberry Pi to start the device.  
   *Note: no further setup actions are required for the Raspberry Pi.*

## References
- [Angry IP Scanner](https://angryip.org/)  
- [Home Assistant installation guide](https://www.home-assistant.io/installation/raspberrypi)  
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
