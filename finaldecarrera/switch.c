#include<stdio.h>
#include<stdbool.h>
#include"esp_log.h"
#include"driver/gpio.h"

#include "switch.h"

#define GPIO_SWITCH_PIN 11

void switch_init(void)
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << GPIO_SWITCH_PIN;
    io_conf.mode = GPIO_MODE_INPUT; 
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
}

bool switch_open(void)
{
    if(gpio_get_level(GPIO_SWITCH_PIN) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*End of file*/