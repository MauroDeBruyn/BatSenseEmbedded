## Section Introduction

This section documents the Home Assistant setup. It covers accessing the Home Assistant web interface after deployment on the Raspberry Pi and explains how functionality can be added and restored by the user in case of system failure.

## Overview
- [Access Freshly Installed Home Assistant](#access-freshly-installed-home-assistant)
- [Installation Options](#installation-options)
  - [New Installation](#new-installation)
  - [Backup Installation](#backup-installation)
- [Post-Installation](#post-installation)
- [References](#references)

## Access Freshly Installed Home Assistant

Within a few minutes after powering on the Raspberry Pi, Home Assistant becomes accessible on the local network.

1. Open a web browser on the desktop system.
2. Navigate to: `http://homeassistant.local:8123`

**Note:**  
The time required for the interface to become available depends on the hardware. On a Raspberry Pi 4 or 5, this typically takes less than one minute.

## Installation Options

### New Installation

This option is used when setting up Home Assistant for the first time on the device.

```
todo:
```

### Backup Installation

This option is used to restore a previously created Home Assistant backup.

```
todo:
```

## How to add addons

Add-ons allow the user to extend the functionality around Home Assistant by installing additional applications.
![image](/resources/documentation_media/Home_Assistant_Setup/addon-image.png)

To install add-ons navigate to the settings menu in the left lower corner and click on the addon option from the selection menu.
![image](/resources/documentation_media/Home_Assistant_Setup/where_are_addons.png)
After which you can either configure your existing addons or add new ones via the add-on store by selecting an addon from the list and clicking install.

## How to add local addons
Local addons are a more advanced way of getting functionality onto your home assistant. 
To add local addons you will need the following addon for this process to be simple.:
-Studio code server(this addon allows us to view the files on the system running home assistant. it has all the functionality that normal visual studio code has.)

1. open studio code server navigate to '/addons' this will house the locally installed addons.
2. find the addon you want to install for example [appdaemon](https://github.com/hassio-addons/addon-appdaemon.git)
3. open a terminal from inside studio code server
![where is terminal](/resources/documentation_media/Home_Assistant_Setup/where_is_terminal.png)
4. either curl or git clone the 
``` bash
curl -LO https://github.com/hassio-addons/addon-appdaemon/archive/refs/tags/v0.17.13.tar.gz
tar -xzf addon-appdaemon-0.17.13.tar.gz
```
**NOTE**: -L follows redirects, -O keeps the original filename.

once the addon is installed under '/addons/' the final thing to do is to add it from inside home assistant.

the process to add a local addon is the same as the one described in section [how to add addons](#how-to-add-addons) the only difference is that it appears under a section called 'Local add-ons' instead of 'Official add-ons'

### troubleshooting local addons
sometimes errors can occur these are to the users to solve for example an error with version 0.17.13 of appdaemon was:
```
22.45 ERROR: unable to select packages:
22.47   yq-go-4.47.2-r2:
22.47     breaks: world[yq-go=4.47.2-r1]
------
```
To get this response use the following command in the terminal:
``` bash
ha supervisor logs
```
solving the issue will depend on the error at hand for this one switching to the 'yq-go-4.47.2-r2' python package by editing the included dockerfile solved the issue.

![appdaemon troubleshoot](/resources/documentation_media/Home_Assistant_Setup/appdaemon_troubleshoot.png)

**NOTE**: Rebuilding the addon is necessary for the changes to take effect.

## How to add graphs to your home assistant dashboard
```
todo:
```
## How to add camera images to your home assistant dashboard
```
todo:
```
## How to backup your Home assistant instance.
```
todo:
```

## References