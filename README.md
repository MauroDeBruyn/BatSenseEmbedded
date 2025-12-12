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

### Methods

- **Hardware setup** explains how the physical components are interconnected and configured to operate as a single system.
    - **[Documentation](./docs/hardware_setup/README.md)** ( describes the complete hardware setup, including Raspberry Pi preparation, network configuration. )

- **Home Assistant OS** is used as the central platform for data ingestion, processing, storage, and visualization.
    - **[Documentation](./docs/Home_Assistant_setup/README.md)** ( details the complete Home Assistant implementation, including platform installation, sensor integration, dashboard configuration, and all additions and configurations carried out as part of the project. )

- **Sensor modules** operate as independent data sources and transmit measurements wirelessly to a central system.
    - **[Temperature & humidity sensor documentation (Bat-Detectie group)](https://github.com/BjarniHeselmans/Bat-Detectie.git)** ( describes the design, configuration, and operation of the temperature and humidity sensor modules. )
    - **[Thermal sensor documentation (Niels & Yinnis)]()** ( describes the design, configuration, and operation of the thermal sensor modules. )

---


## 🗺️ Roadmap <a name="roadmap"></a>

``` 
== Resultaten ==
Hier laat je bewijs zien van wat jullie systeem echt doet.
Geen verhalen, geen beloftes, alleen aantoonbare realiteit.
Hier hoort o.a. in:
• Aantal werkende modules
• Screenshots van Home Assistant
• Temperatuurgrafieken
• Humiditygrafieken
• Camerabeelden met timestamp
• Testresultaten
• Stabiliteitstests
Beantwoord hier:
• Wat is effectief getest?
• Wat werkte stabiel?
• Wat werkte soms?
• Wat werkte niet?
Alles onderbouwen met beeld, grafiek of meetdata
• Geen toekomstplannen
• Geen meningen

```

- ✅ **Completed**
   - ESP modules tested for reliability and data accuracy
   - Cable lengths reduced to comply with I²C protocol specs
   - Sensors inspected, rewired, and verified for field deployment

- 🔄 **Ongoing**
   - Wi-Fi data transfer pipeline (for pippyg modules)
   - SD-based data logging
   - Integration with Home Assistant for real-time data display

- 🚀 **Future**
   - Full connectivity of all modules to Home Assistant
   - Easy data export from Home Assistant or SD storage
   - Automated reporting and visualization tools for ecological research

---

``` 
== BESLUIT ==
Hier kijken jullie kritisch terug op het project.
Beantwoord hier eerlijk:
• Wat is écht geslaagd?
• Wat liep fout?
• Wat was het moeilijkste technische probleem?
• Wat zouden jullie anders doen met meer tijd?
• Wat is de relevantie voor de praktijk?
• Wat is de meerwaarde van dit project?
Kritische reflectie
Technisch eerlijk
Professionele toon
Geen excuses
Geen “we hebben veel geleerd” zonder uitleg

```

## 🛠️ Installation <a name="installation"></a>
See [docs/INSTALL.md](./docs/INSTALL.md) for detailed instructions to set up and deploy sensor modules.

1. Download latest release or clone repository.
2. Flash ESP32 modules using provided firmware and YAML configuration.
3. Power up central device (Home Assistant hub).
4. Confirm data transmission between modules and central hub.

---

## 📚 Documentation <a name="documentation"></a>
- See [Application Note](./docs/application_note.md) for technical details.
- System architecture, hardware specs, and YAML setup guides are available in the `/docs` directory.

---

## 👥 Contributors <a name="contributors"></a>
- **Mauro De Bruyn** – Student / Developer – [GitHub](https://github.com/MauroDeBruyn)
- **Oliwier Jaworski** – Student / Developer – [GitHub](https://github.com/OliwierJaworski)
