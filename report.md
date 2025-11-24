# ESP32 QEMU Emulation Project: Environment Setup and Code Demonstration

## Project Overview

This project demonstrates the successful setup and utilization of the QEMU **(Quick Emulator)** environment for executing firmware targeting the **Espressif ESP32** microcontroller. By utilizing a custom QEMU fork and integrating it with the **ESP-IDF (IoT Development Framework)**, this setup allows for complete software development and testing without requiring physical hardware.

---
## Objectives

The primary goals of this project were:
1. **Environment Setup:** Successfully configured a Linux environment (Ubuntu 22.04+) to install the necessary prerequisites and the ESP-IDF toolchain.
2. **Demonstration 1 (I/O):** Implement and run a basic **LED Blink** application to test digital output control within the emulated environment.
3. **Demonstration 2 (Simulation):** Implement and run a **Simulated Temperature Sensor** application to demonstrate complex logic and output via standard logging.
4. **Documentation:** Document all setup steps and error resolutions  to enable a reproducible, scriptable workflow.
---
## System Information

This environment was set up and tested successfully on **Ubuntu 22.04+**.
| Component | Version/Details | 
| :--- | :--- | 
| **Operating System** | Ubuntu 22.04+ | 
| **ESP-IDF Version** | v5.1 (Recommended Stable) |
| **QEMU Version** | Espressif’s `qemu` fork (`esp-develop` branch) | 
---
## Prerequisites & Setup

### **Prerequisites**
1. **OS Requirement:** Ubuntu 22.04+.
2. **Core Tools:** `git`, `wget`, `flex`, `bison`, `gperf`, `python3`, `cmake`, `ninja-build`, `ccache`.
3. **QEMU Dependencies:** `libsdl2-dev`, `libslirp-dev` (essential for pre-built binaries to resolve shared library errors).

### **Installation Steps**
1.  **Install Core Dependencies:** Update and install the necessary build tools and QEMU runtime dependencies.
    ```bash
    # Core build tools
    sudo apt-get install -y git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
    # QEMU runtime dependencies (fixes shared library errors)
    sudo apt-get install -y libsdl2-dev libslirp-dev
    ```
2.  **Clone ESP-IDF:** Create the project directory and clone the repository recursively.
    ```bash
    mkdir -p ~/esp
    cd ~/esp
    git clone --recursive [https://github.com/espressif/esp-idf.git](https://github.com/espressif/esp-idf.git)
    ```
3.  **Install Toolchain and QEMU:** Navigate to the cloned directory and run the installation script for ESP32.
    ```bash
    cd esp-idf
    ./install.sh esp32
    ```
4.  **Set Environment Variables:** Source the setup script to load environment variables, making `idf.py` available in the current session.
    ```bash
    source ./export.sh
    ```
5.  **Install QEMU Verification Tools:** Re-run this tool installation after fixing shared library dependencies (Step 1) to ensure QEMU is properly verified.
    ```bash
    python3 $IDF_PATH/tools/idf_tools.py install qemu-xtensa qemu-riscv32
    ```
---
## Building & Running in QEMU

The integrated `idf.py` command handles the entire workflow: compiling the firmware, packaging it, launching the QEMU emulator and connecting the terminal to the monitor.

### **Common Commands**
| Command | Purpose |
| :--- | :--- |
| `idf.py set-target esp32` | Configures the project build for the ESP32 target. |
| `idf.py build` | Compiles the firmware. |
| `idf.py qemu monitor` | Runs the compiled firmware in the QEMU emulator. |
| **Exit QEMU:** | Press **`Ctrl+A`** then **`X`**. |
---
## Demo 1: LED Blink

### **Description**
This project simulates blinking an LED connected to **GPIO\_NUM\_2** by toggling the pin level every 1000 milliseconds (1 second). The application logs the state changes ("LED ON", "LED OFF") to the console.

### **Execution**
First, create the project directory and set the target:
```bash
cd ~/esp
idf.py create-project blink_qemu
cd blink_qemu
idf.py set-target esp32
# Modify main/main.c with the correct code (Step 4 in documentation)
idf.py build
idf.py qemu monitor
```
### **Output**
The console log will show the "LED ON" and "LED OFF" messages alternating every second.
{pictureto be added of output - will add pictures in the end}

Demo 1 Implementation Screenshot: ESP32 LED Blink in QEMU
Placeholder: [Screenshot of QEMU Monitor Output showing 'LED ON' and 'LED OFF' messages alternating.]
---
## Demo 2: Simulated Temperature

### **Description**
This project simulates a sensor reading by generating a random floating-point temperature value between **20.0°C and 25.0°C** every 5 seconds. It utilizes standard C library functions and prints the reading to the console with two decimal places.

### **Execution**
First, create the project directory and set the target:
```bash
cd ~/esp
idf.py create-project temp_sim_qemu 
cd temp_sim_qemu
idf.py set-target esp32 
# Modify main/main.c with the corrected simulation code (Step 5 in documentation)
idf.py build 
idf.py qemu monitor
```
### **Output**
The console log will continuously print the simulated temperature readings, formatted to two decimal places.

Demo 2 Implementation Screenshot: Simulated Temperature Reading in QEMU
Placeholder: [Screenshot of QEMU Monitor Output showing continuously printed temperature values.]
---
## Challenges & Learnings

The setup process highlighted the importance of dependencies and strict C syntax, documented in the **Common Issues Encountered and Solutions** section of the guide.

1. **Environment Variables:** Resolved `idf.py: command not found` by explicitly running `source ~/esp/esp-idf/export.sh`.
2. **Tool Dependencies (Python):** Resolved `error: Unable to import the rich module` by installing the missing package: `sudo apt install python3-venv`.
3. **Runtime Dependencies (QEMU):** Resolved missing shared library errors (`libSDL2-2.0.so.0`, `libslirp.so.0`) by installing `libsdl2-dev` and `libslirp-dev`.
4. **C Syntax Errors:** Fixed `error: too few arguments to function 'gpio_set_level'` by correcting missing commas in the function call.
5. **Function Prototypes:** Resolved `error: implicit declaration of function 'generate_simulated_temp'` by adding the required prototype before `app_main`.
6. **QEMU Exit:** Learned the necessary **`Ctrl+A` then `X`** escape sequence to cleanly terminate the QEMU console process.
---
## Reflection — How This Enables Automated Code Evaluation

This QEMU-based emulation setup is highly valuable for automated code evaluation, particularly in a **CI pipeline** or an automated grading system like **Yaksh**. The process can be scripted to first compile the submitted code ('idf.py build'), and then execute the resulting firmware using 'idf.py qemu monitor'. A script can capture and parse the **standard output logs** generated by the running application (e.g., verifying the frequency of LED state changes or checking if simulated temperature values fall within the expected bounds), thereby enabling objective, repeatable, and non-hardware-dependent grading of the implemented firmware logic.

---

## References

1. ESP-IDF Programming Guide
2. QEMU Documentation 
3. ESP32 Technical Reference
---



