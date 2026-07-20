#include<stdio.h>
#include"esp_log.h"
#include"driver/gpio.h"

#include "relay.h"

#define GPIO_RELAY_PIN 11

void relay_init(void)
{
     gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << GPIO_RELAY_PIN;
    io_conf.mode = GPIO_MODE_OUTPUT; 
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
    gpio_set_drive_capability(GPIO_RELAY_PIN, GPIO_DRIVE_CAP_3); //40mA
}

void relay_set(void)
{
    gpio_set_level(GPIO_RELAY_PIN, 1);
}

void relay_reset(void)
{
    gpio_set_level(GPIO_RELAY_PIN, 0);
}

/*END OF FILE*/