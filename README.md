# Accelerometer
# Pico Accelerometer Project (MPU6050 + Raspberry Pi Pico)

This project reads **acceleration data** from an MPU6050 over **bare-metal I2C** using a **Raspberry Pi Pico**, and prints the live readings over USB using `printf()`.

> ✔️ Bare-metal I2C driver  
> ✔️ MPU6050 configured in ±2g mode  
> ✔️ USB `printf()` output to PuTTY / serial monitor  
> ✔️ Written in C with Raspberry Pi Pico SDK

---

## 🧰 Hardware

| Module        | Connection           |
|---------------|----------------------|
| MPU6050 VCC   | Pico **3.3V**        |
| MPU6050 GND   | Pico **GND**         |
| MPU6050 SDA   | Pico GPIO **4**      |
| MPU6050 SCL   | Pico GPIO **5**      |
| 2× 4.1kΩ Pullups | SDA & SCL to 3.3V |

---

## 🛠 Build Instructions

```bash
git clone https://github.com/yourusername/pico-mpu6050-accel.git
cd pico-mpu6050-accel
mkdir build && cd build
cmake ..
ninja
