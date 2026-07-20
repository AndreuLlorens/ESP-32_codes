//PRIMERO INCLUDES GENERALES
#include<stdio.h>
#include"esp_log.h"
#include"driver/gpio.h"

//INCLUDES ESPECIFICOS
#include"buzzer.h"

//DEFINES
#define GPIO_BUZZER_PIN 10

//VARIABLES GLOBALES


//ESTRUCTURAS


//FUNCIONES
void buzzer_init(void)
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << GPIO_BUZZER_PIN;
    io_conf.mode = GPIO_MODE_OUTPUT; 
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
    gpio_set_drive_capability(GPIO_BUZZER_PIN, GPIO_DRIVE_CAP_3); //40mA
}

void buzzer_beep(bool state)
{
    if(state)
    {
        gpio_set_level(GPIO_BUZZER_PIN, 1);
    }
    else
    {
        gpio_set_level(GPIO_BUZZER_PIN, 0);
    }
}
/*END OF FILE*/
