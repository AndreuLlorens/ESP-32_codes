#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "switch.h"

#define SWITCH_POLL_TASK_PRIORITY 2

static  TaskHandle_t switch_poll_task_handle = NULL;

static portMUX_TYPE switch_count_access = portMUX_INITIALIZER_UNLOCKED;

static volatile uint32_t switch_state_open_count = 0;
static volatile uint32_t switch_state_closed_count = 0;

static void switch_poll_task(void * pvParameters);

void app_main(void)
{
    printf("INICIO DEL MAIN");
    switch_init();
    uint32_t open_cnt, closed_cnt;
    float percentaje;


    xTaskCreate(switch_poll_task, "switch_poll_task", 2048,
    NULL, SWITCH_POLL_TASK_PRIORITY, &switch_poll_task_handle);

    for(;;)
    {
        taskENTER_CRITICAL(&switch_count_access);
        open_cnt = switch_state_open_count;
        closed_cnt = switch_state_closed_count;
        taskEXIT_CRITICAL(&switch_count_access);
        percentaje= ((double)(closed_cnt) / (double)(closed_cnt+open_cnt)) * 100.0f;
        printf("Open %lu , Closed %lu \n", open_cnt, closed_cnt);
        printf("Porcentaje %.2f\n", percentaje);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


static void switch_poll_task(void * pvParameters)
{
    for(;;)
    {

        taskENTER_CRITICAL(&switch_count_access);
        if(switch_open())
        {
            switch_state_open_count++;
        }
        else
        {
            switch_state_closed_count++;
        }
        taskEXIT_CRITICAL(&switch_count_access);

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
/*END OF FILE*/