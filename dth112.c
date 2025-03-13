#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <my_gpio.h>

/* Номер линии GPIO, к которой подключен Data контакт датчика */
#define DATA 5

/* Максимальное число итераций обращений к линии */
#define _MAX_ 20000

/* Вспомогательная функция, которая возвращает текущее время в 
   наносекундах */
long long get_time(){
   /* Структура с информацией о текущем времени */
   struct timespec tspec;

   /* Запрашиваем текущее время */
   clock_gettime(CLOCK_REALTIME, &tspec);

   return tspec.tv_sec * 1000000000LL + tspec.tv_nsec;
}

/* Вспомогательная функция, позволяющая точно выдерживать временные
   задержки (вместо usleep). */
void udelay(long long ns){
    long long start_time = get_time();
    long long end_time;

    do {
        end_time = get_time();
    } while(end_time - start_time < ns);
}

void get_data()
{
    int data[5] = {0, 0, 0, 0, 0};
    long long t;
    struct timespec tspec;
    char c;
    int i;
    int k;


    /* Формируем зарос к датчику */
    gpio_open(DATA, "out", "none");

    gpio_write(DATA, 0);

    /* Притягиваем DATA к 0 на 18 мс (18000000 нс) */
    udelay(18000000LL);

    /* Притягиваем DATA к 1 на 30 мкс (30000 нс) */
    gpio_write(DATA, 1);
    udelay(30000LL);

    /* Меняем направление работы шины для приема данных от датчика */
    gpio_set_direction(DATA, "in");

    for(k = 0; k < _MAX_ && gpio_read(DATA) == 0; k++);
    for(k = 0; k < _MAX_ && gpio_read(DATA) == 1; k++);

    for(i = 0; i < 40; i++){
        for(k = 0; k < _MAX_ && gpio_read(DATA) == 0; k++);
        t = get_time();
        for(k = 0; k < _MAX_ && gpio_read(DATA) == 1; k++);
        t = get_time() - t;

        if(60000LL < t && t < 800000LL){
            /* Если время импульса между 60 и 80 мкс (то есть ~70 мкс), 
               то считаем, что это единица.*/
            data[i / 8] |= (1 << (7 - (i % 8)));
        }else if(t < 10000LL || 80000LL < t){

           gpio_close(DATA);

           return ;
        }
    }

    /* Проверяем корректность данных */
    if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)){
        printf("H = %d.%d %% T = %d.%d *C \n",
        data[0], data[1], data[2], data[3]);
    }else{

        gpio_close(DATA);

        return ;
    }

    gpio_close(DATA);

}
int main()
{

    for (int i=0;i<200;i++)
    {
        get_data();
        sleep(10);
    }

}

