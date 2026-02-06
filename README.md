# Accelerometer
# 📦 Raspberry Pi Pico + MPU6050 Accelerometer (Bare Metal)

This project reads real-time **acceleration data** from an **MPU6050** using **bare-metal I2C** (no SDK drivers) on the **Raspberry Pi Pico**, and outputs it over **USB** as a virtual serial device.

---

## 🧰 Hardware Connections

| MPU6050 Pin | Raspberry Pi Pico |
|-------------|-------------------|
| VCC         | 3.3V              |
| GND         | GND               |
| SDA         | GPIO4             |
| SCL         | GPIO5             |

**Pull-up resistors:**  
Use 4.1kΩ between SDA & 3.3V, and between SCL & 3.3V (recommended).

---

## 📄 Features

- 🧠 Bare-metal I2C driver (no SDK I2C or TinyUSB)
- 📡 MPU6050 setup: ±2g, 44Hz DLPF, 125Hz sample rate
- 📤 USB output via `stdio_usb` (`printf()`)
- 💻 Console-friendly real-time output

---

## 🧪 Sample Console Output

When connected via **PuTTY or Serial Monitor (115200 baud)**:


---

## 🛠️ Building the Project

### 🧰 Requirements

- Raspberry Pi Pico SDK installed (e.g. in `.pico-sdk/`)
- ARM GCC toolchain (`arm-none-eabi-gcc`)
- CMake ≥ 3.13 + Ninja
- VSCode or CLI terminal

---

### 🔧 Build Instructions

1. Clone the repo or copy project files
2. Open terminal in the project folder
3. Run:

```bash
mkdir build
cd build
cmake ..
ninja

