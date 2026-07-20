#include<stdio.h>
#include<stdbool.h>
#include"esp_log.h"
#include"driver/gpio.h"

#include"float_switch.h"

#define GPIO_FLOAT_SWITCH_PIN 10

void float_switch_init(void)
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << GPIO_FLOAT_SWITCH_PIN;
    io_conf.mode = GPIO_MODE_INPUT; 
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
}

bool float_switch_closed(void)
{
    if(gpio_get_level(GPIO_FLOAT_SWITCH_PIN) == 1)
    {
        return true; //FULL
    }
    else
    {
        return false; //EMPTY
    }
}
/*END OF FILE*/