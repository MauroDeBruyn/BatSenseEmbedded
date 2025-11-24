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
BatSenseEmbedded is a project designed for the PXL research group to investigate bat behavior within the cavity walls of homes. Researchers believe that differences in climatic conditions, such as temperature and humidity, affect how bats use these spaces. This system helps monitor environmental parameters, supports ecological studies, and guides renovation practices to protect bat habitats.

---

## 🚀 Technical Approach <a name="technical-approach"></a>
- 🌡️ **Environment sensing:** Embedded modules measure temperature and humidity, based on the ESP32 platform.
- 📡 **Wireless connectivity:** Sensor modules transmit data wirelessly to a central hub.
- 🔋 **Battery operation:** Modules are engineered for long battery life, ensuring extended observation periods.
- 🖥️ **Centralized data management:** The central module runs Home Assistant, collecting and organizing data from multiple modules.
- 🛠️ **Non-destructive installation:** Mounting is designed for rapid, non-invasive deployment inside homes.

---

## ⚙️ Project Requirements <a name="project-requirements"></a>
- **Easy setup:** Modules are suitable for quick deployment by researchers, with minimal configuration needed.
- **Minimal home impact:** Installation uses adhesive mounts, avoids drilling and major changes to private residences.
- **Long operational life:** Battery-powered units are built for resilience.
- **Field robustness:** Hardware is selected to resist condensation and variations in outdoor climate.
- **Scalable deployment:** Supports installation in multiple homes for broad-scale studies.

---

## 🗺️ Roadmap <a name="roadmap"></a>
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
