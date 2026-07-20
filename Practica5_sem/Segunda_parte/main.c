#include<stdio.h>

#include"driver/i2c.h"
#include"i2c_bus.h"
#include"sht3x.h"

#include"humiture.c"

#define I2C_MASTER_SCL_IO GPIO_NUM_10
#define I2C_MASTER_SDA_IO GPIO_NUM_11
#define I2C_MASTER_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 10000

static i2c_bus_handle_t i2c_bus = NULL;
static sht3x_handle_t sht3x = NULL;



void app_main(void)
{
    humiture_init();

    float Tem, Hum;
    for(;;)
    {
        humiture_read(&Tem, &Hum); //REVISAR COMPILACION
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }


}