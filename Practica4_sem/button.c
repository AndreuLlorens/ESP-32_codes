#include<stdlib.h>
#include<stdio.h>

#include"button.h"

#define GPIN_BUTTON GPIO_NUM_1

void button_init(void)
{
    gpio_config_t io_conf = {};

    io_conf.pin_bit_mask = 1ULL << GPIN_BUTTON;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE; //WARNING PULL-UP ON
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

button_state_t button_read(void)
{
    button_state_t lectura = gpio_get_level(GPIN_BUTTON);
    return lectura;
}


