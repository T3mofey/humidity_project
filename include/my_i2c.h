#ifndef _MY_I2C_
#define _MY_I2C_

int i2c_open(
   char *device,
   int addr
);

unsigned char i2c_read_reg8(
    int fd,
    unsigned char addr
);

void i2c_write_reg8(
    int fd,
    unsigned char addr,
    unsigned char value
);

void i2c_read(
    int fd,
    unsigned char *buf,
    int nbytes
);

void i2c_write(
    int fd,
    unsigned char *buf,
    int nbytes
);

void i2c_close(
   int fd
);

#endif

