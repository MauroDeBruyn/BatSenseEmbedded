## Section Introduction

This section documents the Home Assistant setup. It covers accessing the Home Assistant web interface after deployment on the Raspberry Pi and explains how functionality can be added and restored by the user in case of system failure.

## Overview
- [Access Freshly Installed Home Assistant](#access-freshly-installed-home-assistant)
- [Installation Options](#installation-options)
  - [New Installation](#new-installation)
  - [SD Card File Transfer Installation](#sd-card-file-transfer-installation)
  - [Backup Installation](#backup-installation)
- [Backing Up Home Assistant](#how-to-back-up-your-home-assistant-instance)
- [Expert (Advanced) Settings](#expertise-settings)
- [Sidebar Customization](#sidebar-items)
- [Add-ons Management](#how-to-add-addons)
  - [Adding Local Add-ons](#adding-local-addons)
  - [Troubleshooting Local Add-ons](#troubleshooting-local-addons)
- [InfluxDB Integration](#influxdb)
  - [Installation and Setup](#installation--setup)
  - [Storing Sensor Data](#how-to-instruct-home-assistant-to-save-sensor-data-to-influxdb)
  - [Data Validation](#validating-with-sensor-data-input)
- [Grafana Integration](#grafana)
  - [Adding InfluxDB as Data Source](#adding-influxdb-plugin)
  - [Dashboards and Visualizations](#creating-a-dashboard--graphs)
  - [Embedding Grafana in Home Assistant](#adding-visualization-to-home-assistant-dashboard)
- [Camera Integration](#integrating-camera-image-into-home-assistant-dashboard)
  - [Prerequisites](#prerequisites)
  - [AppDaemon Setup](#setting-up-appdaemon)
- [Adding ESP Sensor Modules](#how-to-add-esp-sensor-modules-to-home-assistant)
- [Local Image Integration](#home-assistant)
- [References](#references)

## Access Freshly Installed Home Assistant

Within a few minutes after powering on the Raspberry Pi, Home Assistant becomes accessible on the local network.

1. Open a web browser on the desktop system.
2. Navigate to: `http://homeassistant.local:8123`

**Note:**  
The time required for the interface to become available depends on the hardware. On a Raspberry Pi 4 or 5, this typically takes less than one minute.

## Installation Options

### New Installation

Use this option when setting up Home Assistant on a device for the first time.  
After preparing the hardware and storage media, complete the onboarding process at:

```
http://homeassistant.local:8123
```

### SD Card File Transfer Installation

Use this method to clone an existing Home Assistant SD card to another SD card.

**Steps:**
1. Install and open [balenaEtcher](https://etcher.balena.io/).
2. Select **Clone drive**.
3. Insert both SD cards into the computer.
4. Carefully identify the **source** (existing Home Assistant SD card) and the **destination** (target SD card).
5. Select the drives accordingly and start the cloning process.

> The cloning process may take up to an hour depending on SD card size and system performance.

---

### Backup Installation

Use this option to restore Home Assistant from an existing backup.

#### Create a Backup
1. Navigate to:
   ```
   Settings → System → Backups
   ```
2. Click **Create Backup** and generate an automatic backup.
3. Download the backup file once completed.

#### Restore the Backup
1. Prepare the destination device by completing the hardware setup.
2. Boot the new Home Assistant system.
3. Open:
   ```
   http://homeassistant.local:8123
   ```
4. Select **Restore from Backup** when prompted and upload the backup file.

---

## How to Back Up Your Home Assistant Instance

1. Open the Home Assistant web interface.
2. Navigate to:
   ```
   Settings → System → Backups
   ```
3. Click **Create Backup**.
4. Download the backup file and store it securely.

Here you can view, backups and download previous backups.
![how to backup](/resources/documentation_media/Home_Assistant_Setup/How_to_backup.png)

## Expertise settings
To enable expertise settings the following steps: this enables the ability to view local addons
1. select profile.
2. go to general tab
3. select `advanced mode`
![expert settings](/resources/documentation_media/Home_Assistant_Setup/enabling_expert_settings_HA.png)

## Sidebar Items
This section explains how to modify the sidebar of Home assistant.

1.navigate over to the `Gereral` user menu and click on `Change the order and hide items from the sidebar`
![quickview change](/resources/documentation_media/Home_Assistant_Setup/Changing_Quickview_HA.png)
2. In this window the user can select which items are visible from the quickview.
## How to add addons

Add-ons allow the user to extend the functionality around Home Assistant by installing additional applications.
![image](/resources/documentation_media/Home_Assistant_Setup/addon-image.png)

To install add-ons navigate to the settings menu in the left lower corner and click on the addon option from the selection menu.
![image](/resources/documentation_media/Home_Assistant_Setup/where_are_addons.png)
After which you can either configure your existing addons or add new ones via the add-on store by selecting an addon from the list and clicking install.

## Adding local addons
Local addons are a more advanced way of getting functionality onto your home assistant. 
To add local addons you will need the following addon for this process to be simple.:
- Studio code server(this addon allows us to view the files on the system running home assistant. it has all the functionality that normal visual studio code has.)

1. open studio code server navigate to `/addons` this will house the locally installed addons.
2. find the addon you want to install for example [appdaemon](https://github.com/hassio-addons/addon-appdaemon.git)
3. open a terminal from inside studio code server
![where is terminal](/resources/documentation_media/Home_Assistant_Setup/where_is_terminal.png)
4. either curl or git clone the file repository
``` bash
curl -LO https://github.com/hassio-addons/addon-appdaemon/archive/refs/tags/v0.17.13.tar.gz
tar -xzf addon-appdaemon-0.17.13.tar.gz
```
**NOTE**: `-L` follows redirects, `-O` keeps the original filename.

Once the add-on is installed under `/addons/`, enable [advanced (expert)](#expertise-settings) settings in Home Assistant so local add-ons become visible and can be added.

the process to add a local addon is the same as the one described in section [how to add addons](#how-to-add-addons) the only difference is that it appears under a section called 'Local add-ons' instead of 'Official add-ons'

**NOTE**: The addon needs to be started manually. it may take a while because the dockerfile needs to create a docker image and so on.
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

## influxDB
### Installation & setup
Adding a database to your home assistant and saving data from your sensors is pretty straight forward.

1. first we navigate over to the plugins section and install the `InfluxDB` addon
2. Secondly open `InfluxDB` configuration window from within Home assistant and disable ssl.\
**NOTE**: SSL ensures that sensitive data is securely transmitted through the browser. But becuase home assistant runs inside a local network data does not travel the public internet. SSL adds little value there unless you expose home assistant externally.

2. Once installed the next step is to create a database this is done as follows:
    1. from within the InfluxDB user interface open `InfluxDB Admin` which can be found in the ribbon on the left side.
    2. in the top right corner select `Create Database`
    3. give your database a name and confirm the creation using the green check-icon
3. Select the Users-tab from the top. and create a new user which will have access to the database.
4. select the user access permissions(1) and save it (2)
![changing user access permissions](/resources/documentation_media/Home_Assistant_Setup/InfluxDB_UserAccess.png)

### How to instruct Home assistant to save sensor data to influxDB
1. Open the file editor from the Home assistant left ribbon.
2. Open the folder icon
3. Open the file called configuration.yaml\
**NOTE**: Changes made to this folder have effect on restart and can break your system if configured incorrectly. 
4. Add the following code snippet to the end of the file.
```
influxdb:  
  host: localhost  
  port: 8086  
  database: $(database_name)  
  username: $(User_with_database_permissions)  
  password: $(User_with_database_permissions_password)  
  ssl: false  
  verify_ssl: false  
  max_retries: 3  
  default_measurement: state  
  include:  
    domains:  
      - sensor
```
**NOTE**: sensor means only entities of type sensor.* will be written to InfluxDB (e.g. temperature, humidity, power, etc.), and other domains like switch, light, or binary_sensor are excluded.

5. Replace each value shown in $() with your own configuration details before saving the file.
6. After confirming the configuration is correct, save the file and restart Home Assistant.

**NOTE**: If any non-critical error occurs during startup, it will be shown at the top of the Settings tab.

### validating with sensor data input.
To validate everything is working correctly we can open the database and check for data inputs from sensors.
1. open InfluxDB user-interface from the side panel.
2. Open the Explore panel.
3. Select the sensor to view from the menu.
4. select what to view.
![InfluxDB Data Validation](/resources/documentation_media/Home_Assistant_Setup/InfluxDB_validation.png)

## grafana 
To display graphs to the user, Grafana was used due to its extensive visualization capabilities.

### Adding InfluxDB plugin

1. first we navigate over to the plugins section and install the `Grafana` addon
2. Secondly open `Grafana` configuration window from within Home assistant and disable ssl
3. from within the configuration panel add port `4444` to the exposed ports under the **network** section
4. Start grafana from the information panel. \
**NOTE**: It is recommended to review and enable the settings on this page if they suit your needs.
5. Open the grafana user-interface from within home assistant.
6. Navigate to the connection tab from the side-bar.
7. Search for InfluxDB and `add new data source` from the top right corner.
8. the following describes the setup of influxDB grafana plugin:
    1. The URL should point to the InfluxDB container ID which can be found by going to: Settings -> Add-ons -> InfluxDB, there you will find a section `Hostname` with a value resembling something like `a0....-influxdb` insert that value in the URL field.
    2. configure the username, password and database to reflect values from within InfluxDB and save the configuration \
    **note**: If everything is configured correctly you should see the following message in a green window:
    ![confirmation window](/resources/documentation_media/Home_Assistant_Setup/Grafana_InfluxDB_plugin_SetupConfirmation.png)

### Creating a dashboard & graphs

1. Open the Dashboard panel and click on `create a new dashboard`
2. click on `add a new visualization` and select the data you want to display.
3. from within the visualization creator configure the graph. \
**NOTE**: example:
![example graph](/resources/documentation_media/Home_Assistant_Setup/graph_example_grafana.png)
4. Once the visualization is configured save it by clicking `Save dashboard` for a new project, and `save visualization` for an existing dashboard.
5. The visualization is now visible in the grafana dashboard.

### Adding visualization to Home assistant dashboard
Following steps showcase a way of adding grafana visualization to the home assistant dashboard.
1. open the dashboard which contains the visualization.
2. click on 3 dots -> Share -> Share embed
![URL opentab](/resources/documentation_media/Home_Assistant_Setup/grafana_where_URL.png)
3. turn of Lock time range
4. copy the url from the start to the end of the following character: `"` 
![URL opentab](/resources/documentation_media/Home_Assistant_Setup/grafana_url_cpy.png)
5. Navigate to the Home assistant dashboard.
6. open: `Edit dashboard` -> Add card
7. in the searchbar enter `webpage`
8. under `URL` enter the copied link. and change the domain name to the one set on your home assistant. \
**FOR EXAMPLE**: ```http://batsenseembedded:8123/rest/of/the/link``` \
**NOTE**: Dont use batsenseembedded.local:8123, it relies on mDNS, which is not consistently supported or reliable across all networks and devices.
9. The graph will be visible once the webpage configuration is done.

## Integrating camera image into Home assistant dashboard.
This section describes how to add a camera image to the dashboard so the user can view the heatmap generated by the camera. Dummy image data is sent over TCP for demonstration, but the same setup works with any image source because the processing is handled by a background Python script and saved into a image file.

### prerequisites
- local version of appdaemon addon tested on (0.17.13)
  - appdaemon should be compiled with the following changes: \
  **INFO**: This exposes the ports for the python script to bind to so data can be exchanged via tcp/udp sockets.
  ``` yaml
  ports:
  5050/tcp: 5050
  6000/tcp: 6000
  6001/udp: 6001

  ports_description:
  5050/tcp: AppDaemon
  6000/tcp: Camera 1 input
  6001/udp: Camera 2 input
  ``` 
- python script which will listen for image data can be found [here](/firmware/Thermal_Imaging/thermal_receiver.py).
- python script for dummy camera can be found [here](/firmware/Simulations/mlx90640_sim.py).
- Full appdaemon Yaml config can be found [here](/firmware/Thermal_Imaging/config.yaml).
- Full appdaemon apps-folder config can be found [here](/firmware/Thermal_Imaging/apps.yaml).
- Studio code Home assistant plugin.

### setting up appdaemon
the appdaemon setup has been explained in [adding local addon](#adding-local-addons).
although this is not the full setup. you will need to do the following to finish the appdaemon setup:
1. locate `/addon_config/local_appdaemon/apps`.
2. apply the changes mentioned before which can be found in the following [file](/firmware/Thermal_Imaging/apps.yaml)
3. add a file called [thermal_receiver.py](/firmware/Thermal_Imaging/thermal_receiver.py) into the directory.
**NOTE**: This file must match the name you used in the apps.yaml file otherways it wont be recognised by appdaemon.
4. restart the appdaemon addon from the home assistant addon interface.

**NOTE**: The Log tab can be used to view appdaemon for possible failures in the config or misconfigurations. make sure to use it to verify the process is done correctly:
the end result should output the following in the logs:
``` bash
2025-12-13 09:15:05.892850 INFO MLX90640_CAM1: [08:15:05.887413] READY ��� Listening on 0.0.0.0:6000
2025-12-13 09:15:05.893691 INFO MLX90640_CAM1: [08:15:05.887276] INIT OK ��� listening on 0.0.0.0:6000, endpoint '/MLX90640_CAM1'
```
### How to Add ESP Sensor Modules to Home Assistant

1. Install the **ESPHome** add-on in Home Assistant.
2. Set up and flash the ESP device using the provided scripts:  
   - [ESP device setup](https://github.com/BjarniHeselmans/Bat-Detectie/tree/main/Scripts)
3. In Home Assistant, navigate to **Settings → Devices & Services**.
4. Select **ESPHome** from the integrations list.
5. If the device is discovered automatically, click **Configure** and add it.
6. If automatic discovery fails, choose **Add device manually** and enter the ESP device’s IP address.
7. Verify that the sensor entities appear and are reporting data correctly.

### Home assistant
1. navigate to `settings -> `Devives & Services`
2. in the lower right corner select `Add integration`
3. search and select `Local File`, name it accordingly and set path to `/share/thermal.png`
4. navigate to the dashboard and open the dashboard editor
5. add new card, searh for `picture entity` and select it.
6. Under Entity and Camera Entity search for the name you gave to the `Local File` which holds the image data, for example `thermal1`
7. Add it to your dashboard. 

![example image](/resources/documentation_media/Home_Assistant_Setup/camera_image_example.png)
## References
[Data visualization using Grafana and InfluxDB](https://www.youtube.com/watch?v=e4qe_ghroe4)