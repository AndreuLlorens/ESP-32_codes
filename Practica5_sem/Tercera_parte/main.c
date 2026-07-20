#include<stdio.h>

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"esp_log.h"

#include"humiture.c"

#define HUMITURE_READ_TASK_INTERVAL 3000 // READ EVERY 3 SECONDS
#define HUMITURE_READ_TASK_PRIORITY 10

static TaskHandle_t humiture_read_task_handle = NULL;

static void humiture_read_task(void * pvParameters);





void app_main(void)
{
    humiture_init();

    xTaskCreate(humiture_read_task,"humitrue_read_task",2048,
    NULL,HUMITURE_READ_TASK_PRIORITY, &humiture_read_task_handle);

    for(;;)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void humiture_read_task(void * pvParameters)
{
    float tem_val, hum_val;
    for(;;)
    {
        if(humiture_read(&tem_val, &hum_val) == false)
        {
            tem_val = 0.0f;
            hum_val = 0.0f;
        }
        ESP_LOGI("HUMITURE_TASK", "T = %.2f  RH = %.2f ", tem_val, hum_val);
        vTaskDelay(HUMITURE_READ_TASK_INTERVAL / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

