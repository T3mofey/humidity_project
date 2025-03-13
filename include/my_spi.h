#ifndef _MY_SPI_
#define _MY_SPI_

int spi_open(
   char *device,
   unsigned int speed
);

void spi_rw(
   int fd,
   unsigned char *tx_buf,
   int tx_nbytes,
   unsigned char *rx_buf,
   int rx_nbytes
);

void spi_write(
   int fd,
   unsigned char *buf,
   int nbytes
);

void spi_close(
   int fd
);

#endif
