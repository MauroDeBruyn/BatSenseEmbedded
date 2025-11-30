ESP-SD-HOTSPOT
is a subsection dedicated for the implementation of means to interact with data stored onto an sd card without physically having transfer data.
This approach relies on wifi as the medium.

## setup
- [get started guide for esp32 SDK](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)
- fix python not being found mingw32(from guide downloaded version)
``` bash
echo 'export PATH="/c/path_to_python/Python314:$PATH"' >> ~/.bashrc
echo 'export PATH="/c/path_to_python/Python314/Scripts:$PATH"' >> ~/.bashrc
source ~/.bashrc
```
**note** : don't forget to append **:$PATH** to the end of export otherways you overwrite existing PATH and lose access to all other commands

- [fix for magic number 0x3333 partition fail](https://github.com/espressif/ESP8266_RTOS_SDK/issues/929)
QIO of SPI Mode to DIO, the problem was solved.
- [xtensa-lx106-elf-gcc not found error](https://github.com/nodemcu/espressif-sdk-archive/blob/master/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-win32.zip)
----
xtensa-lx106-elf-gcc folder -> /opt (where you can already see the folder xtensa-esp32-elf. Then, I've added these two lines at the end of .bash_profile:
Note that C:/msys32/home/domin/esp/ESP8266_RTOS_SDK is the path I've cloned the RTOS_SDK into.

``` bash
export PATH=$PATH:/opt/xtensa-lx106-elf/bin
export IDF_PATH="C:/msys32/home/domin/esp/ESP8266_RTOS_SDK"
```

``` bash
    make flash monitor
```
**note** : hold flash button -> press reset button and let go -> release the flash button
- this is necessary otherways the board won't flash

monitor output: 

**note** : if using putty to monitor se the baud rate to **74880** for proper output.
``` c
ets Jan  8 2013,rst cause:2, boot mode:(3,6)

load 0x40100000, len 7536, room 16
tail 0
chksum 0x53
load 0x3ffe8408, len 24, room 8
tail 0
chksum 0xda
load 0x3ffe8420, len 3468, room 8
tail 4
chksum 0xc6
csum 0xc6
I (83) boot: ESP-IDF v3.4-110-gd412ac60 2nd stage bootloader
I (83) boot: compile time 14:01:37
I (84) boot: SPI Speed      : 40MHz
I (96) boot: SPI Mode       : DIO
I (109) boot: SPI Flash Size : 2MB
I (121) boot: Partition Table:
I (133) boot: ## Label            Usage          Type ST Offset   Length
I (155) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (179) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (202) boot:  2 factory          factory app      00 00 00010000 000f0000
I (225) boot: End of partition table
I (238) esp_image: segment 0: paddr=0x00010010 vaddr=0x40210010 size=0x1cc5c (117852) map
0x40210010: _stext at ??:?

I (340) esp_image: segment 1: paddr=0x0002cc74 vaddr=0x4022cc6c size=0x071f8 ( 29176) map
I (359) esp_image: segment 2: paddr=0x00033e74 vaddr=0x3ffe8000 size=0x00544 (  1348) load
I (362) esp_image: segment 3: paddr=0x000343c0 vaddr=0x40100000 size=0x00080 (   128) load
I (390) esp_image: segment 4: paddr=0x00034448 vaddr=0x40100080 size=0x0512c ( 20780) load
I (429) boot: Loaded app from partition at offset 0x10000
Hello world!
This is ESP8266 chip with 1 CPU cores, WiFi, silicon revision 1, 2MB external flash
Restarting in 10 seconds...
Restarting in 9 seconds...
Restarting in 8 seconds...
Restarting in 7 seconds...
Restarting in 6 seconds...
Restarting in 5 seconds...
Restarting in 4 seconds...
Restarting in 3 seconds...
Restarting in 2 seconds...
Restarting in 1 seconds...
Restarting in 0 seconds...
Restarting now.
```

### Examples
- [official espressif examples](https://github.com/espressif/ESP8266_RTOS_SDK/tree/d412ac601befc4dd024d2d2adcfaa319c7463e36/examples)