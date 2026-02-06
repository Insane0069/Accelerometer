#include <stdio.h>
#include <stdint.h>
#include "i2c.h"
#include "pico/stdio.h"

// MPU6050 register addresses
#define MPU6050_ADDR        0x68
#define PWR_MGMT_1          0x6B
#define ACCEL_CONFIG        0x1C
#define SMPLRT_DIV          0x19
#define CONFIG              0x1A
#define ACCEL_XOUT_H        0x3B

#define ACCEL_SENS_2G       16384.0f  // LSB/g

// Optional delay
void delay(volatile uint32_t count) {
    while (count--) __asm volatile ("nop");
}

// MPU6050 INIT (inline, not separate file)
void mpu6050_init() {
    i2c_write(PWR_MGMT_1, 0x00);     // Wake up device
    i2c_write(ACCEL_CONFIG, 0x00);   // Set ±2g range
    i2c_write(SMPLRT_DIV, 0x07);     // Sample rate divider
    i2c_write(CONFIG, 0x03);         // DLPF config (44Hz)
}

// Reads 6 bytes of accel data, converts to g
void mpu6050_read_accel(float *ax, float *ay, float *az) {
    uint8_t raw[6];
    int16_t raw_ax, raw_ay, raw_az;

    i2_read(ACCEL_XOUT_H, raw, 6);

    raw_ax = (int16_t)((raw[0] << 8) | raw[1]);
    raw_ay = (int16_t)((raw[2] << 8) | raw[3]);
    raw_az = (int16_t)((raw[4] << 8) | raw[5]);

    *ax = raw_ax / ACCEL_SENS_2G;
    *ay = raw_ay / ACCEL_SENS_2G;
    *az = raw_az / ACCEL_SENS_2G;
}

int main() {
    stdio_init_all();
    //sleep_ms(2000);     // USB for console output
    i2c_init();          // Your I2C driver
    mpu6050_init();      // Wake up and configure MPU6050

    float ax, ay, az;
    printf("Accelerometer/n");
    while (1) {
        
        mpu6050_read_accel(&ax, &ay, &az);
        printf("Accel: X=%.2fg, Y=%.2fg, Z=%.2fg\n", ax, ay, az);
        delay(1000000);  // Crude delay ~100ms
    }

    return 0;
}
