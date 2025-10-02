# Engineering Portfolio

📌 A showcase of my engineering projects and technical work. This repository highlights my academic and practical experience in electronics and networking, demonstrating problem-solving skills and creativity in engineering challenges.

---

## Skills & Tools

**Electronics:** LTSpice, MOSFET/BJT modeling, Analog/Digital circuits  
**Programming:** Python, Node.js, MATLAB  
**Networking:** Wireshark, TCP/IP, OSI, HTTP/SMTP/DNS  
**Other Tools:** Git, PDF Documentation, Project Planning & Management  

---

## Table of Contents

1. [Application and Transport Layers with Wireshark](#application-and-transport-layers-with-wireshark)  
2. [Communication Network Fundamentals - Vol 1](#communication-network-fundamentals---vol-1)  
3. [Communication Network Fundamentals - Vol 2](#communication-network-fundamentals---vol-2)  
4. [Low-Pass Twin-T Notch Filter](#low-pass-twin-t-notch-filter)  
5. [MOSFET Memory Cell Programming](#mosfet-memory-cell-programming)  
6. [Project Planning](#project-planning)  
7. [Semiconductor Device Modeling](#semiconductor-device-modeling)  
8. [Voice Signal Characterization](#voice-signal-characterization)  

---

## Application and Transport Layers with Wireshark

**Summary:** Observed and analyzed real network traffic to understand Application and Transport layer protocols in practice.

- **Application Layer:** Interfaces with the user; handles HTTP requests  
- **Transport Layer (TCP):** Ensures reliable end-to-end communication  
- **Tools:** Wireshark captures demonstrate request-response cycles and TCP reliability  

[📄 Full PDF Report](Application_and_Transport_Layers_with_Wireshark.pdf)  

---

## Communication Network Fundamentals - Vol 1

**Summary:** Technical summary of networking principles covering architectures, protocols, and performance metrics.

- **Topics:** OSI/TCP-IP, HTTP/SMTP/DNS, UDP/TCP, IP addressing, NAT, Subnetting, Network performance  
- **Illustrations:** Based on Kurose & Ross textbooks  
- **Purpose:** Provides a solid foundation for understanding networking concepts  

[📄 Full PDF Report](Communication_Network_Fundamentals_Vol_1.pdf)  

---

## Communication Network Fundamentals - Vol 2

**Summary:** Advanced topics in networking, including LANs, routing protocols, SDN, and physical layer theory.

- **Topics:** ARP, RIP, OSPF, Distance Vector, Link State, SDN concepts (OpenFlow, P4), Transmission media, Nyquist/Shannon theorems  

[📄 Full PDF Report](Communication_Network_Fundamentals_Vol_2.pdf)  

---

## Low-Pass Twin-T Notch Filter

**Summary:** Design and simulation of a filter to remove 79.5 Hz interference while allowing other signals to pass, useful for ECG devices.

<p align="center">
  <img src="assets/notch-low-pass-filter.gif" alt="Twin-T Notch Filter Demo" width="400" style="border: 2px solid #ddd; border-radius: 8px;"/>
</p>

- **Function:** Band-reject at 79.5 Hz, low-pass cutoff ~955 Hz  
- **Applications:** Cardiac monitoring, signal cleaning for accurate diagnostics  

[📄 Full PDF / Simulation File](Low-Pass_Twin-T_Notch_Filter.pdf)  

---

## MOSFET Memory Cell Programming

**Summary:** Simulation and analysis of floating-gate MOSFET memory cell programming using Fowler-Nordheim tunneling.

<p align="center">
  <img src="assets/nmos.gif" alt="N-MOS Demo" width="400" style="border: 2px solid #ddd; border-radius: 8px;"/>
</p>

- **Tasks:**  
  - Current evolution and threshold voltage for VG = 11V  
  - Analysis for VG = 12V & 13V  
  - Constant current injection strategy and simulation  
- **Outcome:** Demonstrates advanced semiconductor knowledge and simulation skills  

[📄 Full PDF / Simulation File](MOSFET_Memory_Cell_Programming.pdf)  

---

## Project Planning

**Summary:** Comprehensive guide to planning and managing engineering projects.

- **Contents:** Project design, planning process, risk management, feasibility, lifecycle, Quality Function Deployment (QFD)  

[📄 Full PDF Report](Proyect_Planning.pdf)  

---

## Semiconductor Device Modeling

**Summary:** Complete analysis of diodes, BJTs, and N-Channel MOSFETs with simulations, analytical modeling, and real-world comparison.

- **Diode:** I-V curves, forward/reverse bias, small-signal modeling  
- **BJT:** Parameter extraction, biasing analysis, temperature effects  
- **MOSFET:** Custom model, amplifier design, distortion analysis, validation with BSP89  

[📄 Full PDF Report](Semiconductor_Device_Modeling.pdf)  

---

## Voice Signal Characterization

**Summary:** Analysis and transformation of speech signals using spectral and temporal techniques.

- **Methods:** FFT, STFT, TD-PSOLA, Phase Vocoder  
- **Applications:** Pitch shifting, speed modification, intelligibility preservation  

[📄 Full PDF Report](Voice_Signal_Characterization.pdf)  
