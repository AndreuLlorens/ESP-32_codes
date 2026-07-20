#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include"relay.h"

#define HEATER_CONTROL_TASK_PRIORITY 2

static TaskHandle_t heater_control_task_handle = NULL;

volatile float heater_on_cycle = 100.0f;
static portMUX_TYPE heater_spinlock = portMUX_INITIALIZER_UNLOCKED;

static void heater_control_task(void * pvParameters);


void app_main(void)
{
    relay_init();
    xTaskCreate(
        heater_control_task,
        "heater_control_task",
        2048,
        NULL,
        HEATER_CONTROL_TASK_PRIORITY,
        &heater_control_task_handle);
    for(;;)
    {
        vTaskDelay(300 / portTICK_PERIOD_MS);
        taskENTER_CRITICAL(&heater_spinlock);
        heater_on_cycle -= 0.3F;
        if(heater_on_cycle < 0.0f)
        {
            heater_on_cycle = 100.0f;
        }
        taskEXIT_CRITICAL(&heater_spinlock);
    }
}

static void heater_control_task(void * pvParameters)
{
    float tmp_cycle;
    uint32_t time_on_ms;
    for(;;)
    {
        taskENTER_CRITICAL(&heater_spinlock);
        tmp_cycle = heater_on_cycle;
        taskEXIT_CRITICAL(&heater_spinlock);
        time_on_ms = 2000 * (tmp_cycle / 100.0f);
        relay_set();
        vTaskDelay(time_on_ms / portTICK_PERIOD_MS);
        relay_reset();
        vTaskDelay((2000-time_on_ms) / portTICK_PERIOD_MS);
    }
}