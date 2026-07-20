#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "float_switch.h"

#define FLOAT_SWITCH_TASK_PRIORITY 2 
#define ALARM_CHECK_TASK_PRIORITY 2

static TaskHandle_t float_switch_handle = NULL;
static TaskHandle_t alarm_check_handle = NULL;

static portMUX_TYPE float_switch_access = portMUX_INITIALIZER_UNLOCKED;

static volatile uint32_t tank_empty_count = 0;

static void float_switch_poll_task(void * pvParameters);
static void alarm_check_task(void * pvParameters);

void app_main(void)
{
    float_switch_init();
    
    xTaskCreate(float_switch_poll_task, "float_switch_poll_task",
    2048, NULL, FLOAT_SWITCH_TASK_PRIORITY, &float_switch_handle);
    
    xTaskCreate(alarm_check_task, "alarm_check_task", 2048,
        NULL, ALARM_CHECK_TASK_PRIORITY, &alarm_check_handle);
    
    for(;;)
    {
        printf("HOLA DESDE EL MAIN;");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}


static void float_switch_poll_task(void * pvParameters)
{
    for(;;)
    {
        portENTER_CRITICAL(&float_switch_access);
        if(!float_switch_closed())
        {
            tank_empty_count++; //SI ES UN 0 EL DEPOSITO ESTA VACIO Y CUENTO EL TIEMPO QUE ESTA VACIO
        }
        else
        {
            tank_empty_count = 0;
        }
        portEXIT_CRITICAL(&float_switch_access);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

static void alarm_check_task(void * pvParameters)
{
    uint32_t tmp_tank_empty_count;
    for(;;)
    {
        portENTER_CRITICAL(&float_switch_access);
        tmp_tank_empty_count = tank_empty_count;
        portEXIT_CRITICAL(&float_switch_access);
        if(tmp_tank_empty_count >= 5)
        {
            printf("ALARMA %ld segundos \n", (tmp_tank_empty_count * 200) / 1000);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
}