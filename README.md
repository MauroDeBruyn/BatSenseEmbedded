<h1 align="center">
  <a href="#">BatSenseEmbedded</a>
</h1>

<p align="center">
  <img alt="Stars" src="https://img.shields.io/github/stars/MauroDeBruyn/BatSenseEmbedded?style=social">
  <a href="https://github.com/MauroDeBruyn/BatSenseEmbedded">
    <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/MauroDeBruyn/BatSenseEmbedded">
  </a>
  <a href="https://github.com/MauroDeBruyn/">
    <img alt="Template made by Mauro De Bruyn" src="https://img.shields.io/badge/made%20by-Mauro%20De%20Bruyn-ff69b4">
  </a>
</p>

![Project Banner](./resources/media/banner.png)

<h4 align="center"> 
   Status: 🚧 Work In Progress
</h4>

<p align="center">
 <a href="#about">About</a> •
 <a href="#technical-approach">Technical Approach</a> • 
 <a href="#project-requirements">Project Requirements</a> • 
 <a href="#roadmap">Roadmap</a> • 
 <a href="#installation">Installation</a> •
 <a href="#documentation">Documentation</a> •
 <a href="#contributors">Contributors</a>
</p>

---

## 🧭 About <a name="about"></a>
BatSenseEmbedded is a technical research project developed for the PXL research group to study bat presence and movement within cavity walls of residential buildings. The project focuses on collecting environmental data from enclosed wall spaces that are believed to be used by bats during specific periods of the year.

The system integrates multiple sensor types, including temperature, humidity, sound, and thermal sensors. All sensor data is collected and processed centrally using Home Assistant, which serves as the single integration and visualization platform. This project focuses on implementing and configuring this central system to reliably ingest, store, process, and present data from all deployed sensor modules.

The collected data is intended to support further analysis by researchers and to provide a factual basis for understanding bat usage of cavity walls in the context of building renovation and conservation.

---

## ⚙️ Project Requirements <a name="project-requirements"></a>
- **Easy setup:** Modules are suitable for quick deployment by researchers, with minimal configuration needed.
- **Minimal home impact:** Installation uses adhesive mounts, avoids drilling and major changes to private residences.
- **Long operational life:** Battery-powered units are built for resilience.
- **Field robustness:** Hardware is selected to resist condensation and variations in outdoor climate.
- **Scalable deployment:** Supports installation in multiple homes for broad-scale studies.
- **Real-time monitoring:** A real-time overview dashboard shows the current status of all devices, with clear indication of online and offline nodes.
- **Continuous data logging:** Automatic and continuous logging of temperature and humidity data per module.
- **Data visualization:** Graphical visualization with at least 30 minutes of history per module and one combined temperature/humidity graph for all modules.
- **System capacity:** Management and visualization of at least 20 autonomous sensor modules.
- **Persistent storage:** All measurement data is stored persistently and retained after Home Assistant restarts.
- **Restart resilience:** Correct reinitialization after restart, ensuring all nodes and historical data are visible again.
- **Thermal imaging:** Visualization of MLX90640 thermal data as a 32×24 heatmap, with logging of minimum, maximum, and average temperature.
- **Data export:** Export of node lists and measurement data to CSV/Excel formats.
- **Documentation support:** Support for capturing dashboard screenshots.
- **Backup and recovery:** Ability to create and store configuration backups.

---

## 🚀 Technical Approach <a name="technical-approach"></a>

### Materials

- **Raspberry Pi 4 (3 units)** used as central host systems  
  - Power supply: 5.1 V DC / 3 A  
  - Ethernet connection: Cat5/6

- **Raspberry Pi 5 (1 unit)** used as central host system  
  - Power supply: 5.1 V DC / 3 A  
  - Ethernet connection: Cat5/6

- **microSD cards (4 units, Class 1)**  
  - Used for operating system installation and persistent data storage

- **TP-Link TL-MR6400 Wireless N 4G-LTE routers (4 units)**  
  - power supply: 9 V DC / 0.85 A  
  - Ethernet connection: Cat5/6

- **Preconfigured autonomous battery-powered sensor modules (40 units)**  
  - Providing temperature, humidity, and thermal data

### SD Card Adapter Materials

- **MicroSD to SD Card Adapter**  
  - Enables SD card extension and easier physical integration  
  - [Product link](https://www.amazon.com.be/-/en/CENPEK-Adapter-Extension-Upgrade-Navigators/dp/B0C7KV13RQ)

- **FYSETC SD WiFi Pro**    
  - Custom-designed board by FYSETC built around an ESP8266 microcontroller  
  - Provides SD card functionality with Wi-Fi connectivity and SPI access from two endpoints  
  - Used as an experimental platform for wireless SD card data accesse  
  - [Project repository](https://github.com/FYSETC/SD-WIFI-PRO)  
  - [Product page 1](https://nl.aliexpress.com/item/1005006122460409.html)  
  - [Product page 2](https://nl.aliexpress.com/item/1005008461184152.html)

### Methods

- **Hardware setup** explains how the physical components are interconnected and configured to operate as a single system.
    - **[Documentation](./docs/hardware_setup/README.md)** ( describes the complete hardware setup, including Raspberry Pi preparation, Home Assistant installation, network configuration. )

- **Home Assistant OS** is used as the central platform for data ingestion, processing, storage, and visualization.
    - **[Documentation](./docs/Home_Assistant_setup/README.md)** ( details the complete Home Assistant implementation, including sensor integration, dashboard configuration, and all additions and configurations carried out as part of the project. )
    - **which website to reach home assistant on: http://batsenseembedded:8123/

- **SD Card Data Server** is used to enable remote access to data stored on an SD card without requiring physical removal of the card from the device.
  - **[Documentation](./firmware/pippyg_pipistrelle_mini/README.md)** (describes the implementation that explores wireless SD card access, including SPI communication, an embedded HTTP server for file listing and download, observed limitations, and experimental results. This is not a full production-ready implementation, but a research-driven subsystem.)
  - **Purpose:** Allow users to remotely retrieve sensor data from deployed devices where physical access to the SD card is impractical.

- **Sensor modules** operate as independent data sources and transmit measurements wirelessly to a central system.
    - **[Temperature & humidity sensor documentation (Bat-Detectie group)](https://github.com/BjarniHeselmans/Bat-Detectie.git)** ( describes the design, configuration, and operation of the temperature and humidity sensor modules. )
    - **[Thermal sensor documentation (Niels & Yinnis)]** ( describes the design, configuration, and operation of the thermal sensor modules. )

---


## 🗺️ Results <a name="roadmap"></a>

This section documents **observable and verifiable system behavior only**.

### Proven Functionality

- **20 fully operational sensor modules** connected and actively reporting data.
- **Home Assistant preview available** via recorded output  
  - [Video](./resources/media/exportData.mp4)
- Devices successfully connect to the Home Assistant instance once the system is connected to the **batsenseWiFi** network.
- Network router operates reliably in both **4G** and **WLAN** modes, depending on configuration.
- Home Assistant instances are **interchangeable** without requiring manual reconfiguration or setup changes.

### Tested With Limited Functionality

- Camera data preview via Home Assistant dashboard (dummy data only).
- **SD-based and Wi-Fi FTP server data access**
  - **Single SPI master:** Stable data transfer, correct UI loading, reliable file serving.
  - **Shared SPI bus:** Deadlock occurs, system becomes unrecoverable.
- **Camera images available (dummy data)**  
  - Dummy camera data is displayed in the dashboard for validation purposes  
  - [Example image](./resources/documentation_media/Home_Assistant_Setup/camera_image_example.png)

### Not Fully Functional

- Concurrent SPI access on a shared bus using the **FYSETC SD WiFi Pro**.
- Home Assistant was not tested with real camera data; no guarantee can be made that it will function correctly without additional configuration or validation.
Wireless access to SD card–stored data was partially achieved, confirming that remote data retrieval is feasible in deployments where physical access is impractical.

### conclusion

This project demonstrated that a sensor network with **20 operational modules** can be reliably integrated into **Home Assistant** for centralized data ingestion and visualization, using tools such as **Grafana** and **InfluxDB**. Home Assistant instances proved to be seamlessly interchangeable without requiring manual reconfiguration of the modules.

Several limitations were also identified. Sharing a single SPI bus between multiple masters requires a highly robust design to ensure reliable communication. This was the most significant technical challenge of the project and revealed the lack of strict SPI ownership and arbitration in the chosen architecture. Camera integration was only validated using dummy data, meaning real-world camera functionality remains unverified.

With additional time, the system would benefit from a redesigned SPI access model, a more strictly encapsulated SD access layer, full validation using real camera hardware and data streams, and the integration of additional modules into the system.

## 👥 Contributors <a name="contributors"></a>
- **Mauro De Bruyn** – Student / Developer – [GitHub](https://github.com/MauroDeBruyn)
- **Oliwier Jaworski** – Student / Developer – [GitHub](https://github.com/OliwierJaworski)
