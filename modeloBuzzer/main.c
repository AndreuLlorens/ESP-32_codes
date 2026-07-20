#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "buzzer.h"

#define BUZZER_MANAGER_TASK_PRIORITY 2
#define ALARM_TASK_PRIORITY 2

static TaskHandle_t buzzer_manager_task_handle = NULL;
static TaskHandle_t alarm_task_handle = NULL;

static portMUX_TYPE alarm_count_access = portMUX_INITIALIZER_UNLOCKED;

static volatile uint32_t alarm_count = 0;
static void buzzer_manager_task(void * pvParameters);
static void alarm_task(void * pvParameters);

void app_main()
{
    buzzer_init();
    
    xTaskCreate(buzzer_manager_task, "buzzer_manager_task",
    2048, NULL, BUZZER_MANAGER_TASK_PRIORITY, &buzzer_manager_task_handle);

    xTaskCreate(alarm_task, "alarm_task", 2048, NULL,
    ALARM_TASK_PRIORITY, &alarm_task_handle);
    for(;;)
    {
        printf("HOLA DESDE EL MAIN \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


static void buzzer_manager_task(void * pvParameters)
{
    uint32_t alarm_count_tmp;
    for(;;)
    {
        buzzer_beep(false);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        buzzer_beep(true);
        taskENTER_CRITICAL(&alarm_count_access);
        alarm_count_tmp = alarm_count;
        taskEXIT_CRITICAL(&alarm_count_access);
        vTaskDelay ( (1000 + (alarm_count_tmp * 10)) / portTICK_PERIOD_MS);
    }
   vTaskDelete(NULL);
}

static void alarm_task(void * pvParameters)
{
    for(;;)
    {
    taskENTER_CRITICAL(&alarm_count_access);
    alarm_count++;
    taskEXIT_CRITICAL(&alarm_count_access);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}