#ifndef I2C_H
#define I2C_H


#include <stdint.h>

void i2c_init();
void i2c_write(uint8_t reg , uint8_t val);
void i2_read(uint8_t reg_addr , uint8_t *buf , uint8_t len );

#endif
