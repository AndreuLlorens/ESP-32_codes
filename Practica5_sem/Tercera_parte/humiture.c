#include<stdio.h>

#include"driver/i2c.h"
#include"i2c_bus.h"
#include"sht3x.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"esp_log.h"

#include"humiture.h"

#define I2C_MASTER_SCL_IO GPIO_NUM_10
#define I2C_MASTER_SDA_IO GPIO_NUM_11
#define I2C_MASTER_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 10000

static i2c_bus_handle_t i2c_bus = NULL;
static sht3x_handle_t sht3x = NULL;

void humiture_init(void)
{
    i2c_config_t conf =
    {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_bus = i2c_bus_create(I2C_MASTER_NUM, &conf);
    sht3x = sht3x_create(i2c_bus,SHT3x_ADDR_PIN_SELECT_VSS);

    sht3x_set_measure_mode(sht3x,SHT3x_PER_2_MEDIUM);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

bool humiture_read(float * temperature, float * humity)
{
    static bool medition;
    //ESP_OK Success - ESP_FAIL Fail RETURN
    medition = sht3x_get_humiture(sht3x, temperature, humity);
    if(medition == ESP_OK)// LO MISMO QUE 0
    {
        medition=true;
    }
    else
    {
        printf("ERROR IN MEDITION \n");
        medition=false;
    }
    return(medition);
}