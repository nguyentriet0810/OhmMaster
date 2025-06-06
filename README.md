# 🚀 OhmMaster - Handheld Resistance Meter using STM32 with RTOS

## 📋 1. Overview

- **OhmMaster** is a handheld resistance measurement device with a selectable range from **0.4Ω to 10MΩ**.
- It allows users to adjust both the measurement range and sampling frequency, offering flexibility for various applications.
- The device can transmit measurement data to a computer via **UART** communication.
- **OhmMaster** is well-suited for measuring static resistors or soft sensors that return values in the form of resistance.

---

## ⚙️ 2. Technologies Used

- **Microcontroller**: STM32F103C8 (ARM Cortex-M3, 72MHz)
- **Custom RTOS**: A lightweight, self-developed real-time operating system for deterministic task handling.
- **Measurement Method**: Resistance is measured by sourcing a known current and sampling the resulting voltage using the **ADS1115** high-resolution ADC.
- **User Interface**: **TFT display** with button-based control for range and sampling adjustments.
- **Data Communication**: Measurement data can be transmitted to a PC via **UART**.

---

## ✨ 3. Key Features

- **Resistance measurement** from **0.4Ω to 10MΩ**.
- Selectable measurement ranges and sampling rates.
- High-accuracy **ADC (ADS1115)** for voltage sampling.
- Real-time display on **TFT screen** with button navigation.
- **UART communication** with PC for data logging or visualization.
- Built-in **custom RTOS** for efficient task scheduling.
- Portable and compact design, powered via **adapter 8-12V** (using **9V** for best performance).

---

## 🛠️ 4. How to Use

### Step 1: Clone the Repository
Clone the repository to your local machine:
git clone https://github.com/nguyentriet0810/OhmMaster
This repository contains both the firmware and PCB design files.

### Step 2: Fabricate the PCB
Navigate to the hardware/ folder and use the provided Gerber files or Altium project to manufacture the 2-layer PCB.

### Step 3: Flash the Firmware
Open the firmware project in Keil uVision (MDK-ARM)
Connect the STM32F103C8 board via ST-Link
Build and flash the firmware to the device

### Step 4: Connect to PC via UART
Use a USB-to-UART adapter (e.g., CP2102, FTDI)
Connect to the device's UART TX/RX pins
Open a serial terminal at 115200 baud
Observe live resistance readings for logging or analysis

## 🎥 5. Demo
Watch a demonstration of **OhmMaster** in action: https://youtu.be/fcCfoET1POA?si=9PWGg6f9-cb-5Tt6

## 🧑‍💻 6. Author

**Nguyen Hoang Minh Triet** – Final Year Student at **HCM University of Technology**  
Email: [23trietminh23@gmail.com](mailto:23trietminh23@gmail.com)  
GitHub: [@nguyentriet0810](https://github.com/nguyentriet0810)  
YouTube: [Hoang Triet](https://www.youtube.com/@hoangtriet9999)

Feel free to open an issue or contact me for any questions or suggestions!
