#include<stdio.h>
#include<stdbool.h>
#include"esp_log.h"
#include"driver/gpio.h"

#include"boton.h"

#define GPIO_BOTON 11

void boton_inicializar(void)
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL <<  GPIO_BOTON;
    io_conf.mode = GPIO_MODE_INPUT; 
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
}

bool boton_leer(void)
{
    if(gpio_get_level(GPIO_BOTON) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
