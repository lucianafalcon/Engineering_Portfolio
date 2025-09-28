📌 A showcase of my engineering projects and technical work. This repository includes examples of my experience in electronics, highlighting both my academic and practical expertise. It offers insight into my problem-solving abilities and creative approach to engineering challenges.

## Table of Contents

1. [Application and Transport Layers with Wireshark](Application_and_Transport_Layers_with_Wireshark.pdf)
2. [Communication Network Fundamentals - Vol 1](Communication_Network_Fundamentals_Vol_1.pdf)
3. [Communication Network Fundamentals - Vol 2](Communication_Network_Fundamentals_Vol_2.pdf)
4. [Low-Pass Twin-T Notch Filter](Low-Pass_Twin-T_Notch_Filter.pdf)
5. [MOSFET Memory Cell Programming](#mosfet-memory-cell-programming)
6. [Project Planning](Proyect_Planning.pdf)
7. [Semiconductor Device Modeling](Semiconductor_Device_Modeling.pdf)
8. [Voice Signal Characterization](Voice_Signal_Characterization.pdf)


---

## Application and Transport Layers with Wireshark

In computer networks, protocols are organized into layers, each with specific functions that ensure proper information exchange. Among these, the Application and Transport layers are essential to understanding how users access network services and how communication between devices is maintained.

Application Layer: Acts as the interface between the user and the network, handling direct interactions such as HTTP requests.

Transport Layer (TCP): Ensures a reliable end-to-end connection, guaranteeing correct and ordered data delivery.

Analyzing traffic captures with Wireshark allows observing these layers in action: the client requests resources via HTTP, the server responds with the requested data, and TCP ensures the communication is reliable.

The project aims to provide a clear, practical view of these interactions, showing how theoretical network concepts translate into real traffic.

---

## Communication Network Fundamentals - Vol 1 

This document is a comprehensive technical summary covering key concepts in computer networks. It introduces the structure and function of communication systems, including physical components, protocols, performance metrics, and communication models like OSI and TCP/IP. Topics include:

- Network architectures and physical/logical components
- Communication models such as OSI and TCP/IP
- Application Protocol: HTTP, SMTP, DNS
- Transport Layer: UDP, TCP, Performance
- IP Architecture: IPv4, NAT, Subnetting, IPv6, CIDR
- Network performance: delay, throughput, and congestion control
- Encapsulation and data flow across layers
- Applications and Examples

Illustrations and examples from the textbooks by Kurose & Ross support the explanations throughout this document. I created this material to serve as a solid foundation for anyone seeking to understand the principles of computer networking.

---

## Communication Network Fundamentals - Vol 2

This second volume continues the study of computer networking, expanding on the foundations introduced in Volume 1. It addresses more specialized topics across different network layers:

- Data Link Layer & LAN Networks: ARP protocol, internal routing (RIP, OSPF), and routing algorithms (Distance Vector, Link State)
- Network Architecture: Evolution of the Internet, reference links, interconnection, and classification of network types
- Software-Defined Networking (SDN): Router architecture, SDN concepts, OpenFlow protocol, P4 programming language, and Open Compute Project (OCP)
- Physical Layer: Transmission media, modulation, multiplexing, and theoretical limits (Nyquist and Shannon theorems)

---

## Low-Pass Twin-T Notch Filter

The designed Notch Twin-T filter is a band-reject filter cascaded with a low-pass stage. Its main function is to eliminate a specific frequency at 79.5 Hz, allowing the rest of the signal to pass while attenuating frequencies above 954.92 Hz due to the low-pass response.  
This type of filter is particularly useful in cardiac monitoring devices, such as electrocardiographs (ECG), where power line interference or low-frequency muscle noise is common and can affect signal quality. By adjusting the values of the notch components, the signal can be cleaned, enhancing monitoring accuracy and improving diagnostic reliability.

<p align="center">
  <img src="assets/notch-low-pass-filter.gif" alt="Twin-T Notch Filter Demo" width="400"/>
</p>

---

## MOSFET Memory Cell Programming

<small>
The programming of a memory cell based on a MOSFET transistor consists of charging the floating gate with electrons, which occurs exclusively through Fowler-Nordheim tunneling from the conduction band of the substrate.

In the file, you will find how to carry out this process, which includes:

- Simulating the temporal evolution of the current injected into the floating gate and the threshold voltage for a control gate voltage of VG = 11V, determining the maximum achievable value of Vt
- Analyzing the changes in the results when VG = 12V and VG = 13V
- Exploring strategies to achieve a constant current injection process and simulating the response for VG = 11V
</small>

---

## Project Planning

This section covers essential aspects of engineering project planning and management, including methodologies, the steps involved in managing projects, understanding market needs, product requirements, and the key phases of project execution.

The file includes:

- Project Design
- Planning Process
- Project Management
- Risk Management and Feasibility
- Project Life Cycle
- Quality Function Deployment (QFD)

---

## Semiconductor Device Modeling

This file contains the complete development of the technical report titled "Modeling of Semiconductor Devices: Diode, Bipolar Junction Transistor (BJT), and N-Channel MOSFET" by me. The project thoroughly analyzes the theoretical and practical behavior of fundamental electronic devices through simulations, analytical modeling, and comparison with real manufacturer data.

**Objective:**  
To build a solid understanding of modeling, simulation, and design of semiconductor devices, bridging theory and real-world application through practical tools and hands-on experimentation.

### Diode

- I-V characteristic simulated in LTSpice and parameter extraction (Is, n) using Python
- Analysis under forward and reverse bias using large- and small-signal models
- Circuit modeling using small-signal equivalent (MPS) and comparison with transient simulation results

### Bipolar Junction Transistor (BJT)

- Extraction of key parameters (Is, β, VA, VCEsat) from simulated curves and datasheets
- Biasing analysis with and without emitter resistance (RE)
- Study of collector current (IC) variation with temperature

### N-Channel MOSFET

- Development of a custom transistor model based on simulated transfer and output curves
- Design and analysis of a common-source single-stage amplifier
- Examination of distortion, small-signal parameters (gm, Rin, Rout, Av), and validation using the BSP89 model
  
---

## Voice Signal Characterization

This project explores various techniques for analyzing and transforming speech signals. It includes: Spectral analysis using the Fourier Transform (FFT), short-Time Fourier Transform (STFT) for spectrograms, time-domain and frequency-domain pitch and speed modifications, TD-PSOLA and Phase Vocoder techniques, and the results demonstrate the value of spectral-temporal processing for speech transformation, pitch shifting, and intelligibility preservation in different use cases.




