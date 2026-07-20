#include"led.h"
#include<stdio.h>
#include"esp_log.h"
#include"driver/gpio.h"

static const char * TAG = "Funcion"; 

void led_init(void)
{

    ESP_LOGI(TAG, "SE HAN INICIALIZADO LAS FUNCIONES DEL LED"); 
    gpio_config_t io_conf = {}; 
    io_conf.pin_bit_mask = 1ULL << GPIO_NUM_18;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE; 
    gpio_config(&io_conf);
    gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_3);
    // SI ESCRIBES CAP 3 son 40mA 
    // Si escribes Cap 2 son menos mA


    //printf(" Se ha llamado a la funcion led_init() \n");
}

void led_on(void)
{
    ESP_LOGI(TAG, "SE HA ENCENDIDO EL LED");
    gpio_set_level(GPIO_NUM_18, 1);


    //printf("Se ha llamado a la funcion led_on() \n");
}

void led_off(void)
{
    ESP_LOGI(TAG, "SE HA APAGADO EL LED");
    gpio_set_level(GPIO_NUM_18, 0);

    //printf("Se ha llamado a la funcion led_off() \n");
}