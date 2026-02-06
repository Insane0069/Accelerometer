#include "i2c.h"

#define I2C_BASE            0x40044000
#define I2C_TAR             (I2C_BASE + 0x04)
#define I2C_FS_SCL_HCNT     (I2C_BASE + 0x1c)
#define I2C_FS_SCL_LCNT     (I2C_BASE + 0x20)
#define I2C_STATUS          (I2C_BASE + 0x70) 
#define I2C_DATA_CMD        (I2C_BASE + 0x10)

#define IO_BANK0_BASE       0x40014000


#define HW_REG32(addr) (*(volatile uint32_t*)(addr))

#define SCL_PIN 5
#define SDA_PIN 4

void i2c_init(){
    //GPIO SETUP
    HW_REG32(IO_BANK0_BASE + 0x024) = 3;
    HW_REG32(IO_BANK0_BASE + 0x02c) = 3;
    
    //DISABLE I2C   
    HW_REG32(I2C_BASE + 0x6c) = 0 ;

    //SDA FREQ SETUP
    HW_REG32(I2C_BASE + 0x00)  = 0x63;
    HW_REG32(I2C_FS_SCL_HCNT)  = 113;
    HW_REG32(I2C_FS_SCL_LCNT)  = 200;
    
    //TARGET 
    HW_REG32(I2C_TAR) = 0x68;
    
    //ENABLE I2C
    HW_REG32(I2C_BASE + 0x6c)  = 1;
   
}


void i2c_write(uint8_t reg , uint8_t val){
    //TX FIFO FULL?
    
    while(!(HW_REG32(I2C_STATUS) & (1<<1)));
    HW_REG32(I2C_DATA_CMD) = reg;
    
    //TX FIFO FULL?
    while(!(HW_REG32(I2C_STATUS) & (1<<1)));
    HW_REG32(I2C_DATA_CMD) = val; 
}

void i2_read(uint8_t reg_addr , uint8_t *buf , uint8_t len ){

    while(!(HW_REG32(I2C_STATUS) & (1<<1)));
    HW_REG32(I2C_DATA_CMD) = reg_addr ;

    for(uint8_t i = 0; i < len ; i++){
        while(!(HW_REG32(I2C_STATUS) & (1<<1)));
        HW_REG32(I2C_DATA_CMD) = (1<<8);
    }

    for(uint8_t i = 0 ; i < len ; i++){
        while(!(HW_REG32(I2C_STATUS)&(1<<3)));
        buf[i] = HW_REG32(I2C_DATA_CMD) & 0XFF ;
    }

}