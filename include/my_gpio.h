#ifndef _MY_GPIO_
#define _MY_GPIO_

void gpio_open(
   int line,
   const char *direction,
   const char *edge
);

void gpio_set_direction(
   int line,
   const char *direction
);

char gpio_read(
    int line
);

char gpio_poll(
    int line,
    int timeout
);

void gpio_write(
    int line,
    char value
);

void gpio_close(
    int line
);

#endif

