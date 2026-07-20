#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "boton.h"

static volatile uint32_t boton_presionado = 0;

/*typedef struct
{
    uint32_t contador_presionado;
}boton_t;
boton_t boton; Recordar inicializar la variable de la estructura
llamada boton.contador_presionado = 0;
*/


/*SI SE USA ESTRUCTURA ENVIAS TODAS LAS VARIABLES DE LA ESTRUCTURAS CUANDO HACES*/
/*(xQueueReceive(boton_queue, &boton.contador_presionado, 0) == pdPASS) EN ESTE CASO ENVIARIAS solo la static volatile*/

static QueueHandle_t boton_queue = NULL;

static void boton_contador(void * pvParameters);

/*RECIBIR*/
void app_main(void)
{
    boton_inicializar();

    boton_queue = xQueueCreate(10, sizeof(uint32_t)); //CREO LA COLA, la primera varible se puede usar #define Queue_size 10
    //boton_queue = xQueueCreate(10, sizeof(boton_t)); //CREO LA COLA


    xTaskCreate(boton_contador, "boton_contador", 2048, NULL, 5, NULL);
    uint32_t contador_recibido_tmp;
    for(;;)
    {
        /*Recibira las varibles de la cola*/
        if (boton_queue != NULL) 
        { //Si existe la cola 
        //no quiero que cuando entre 1 dato inmediatamente se reciba, cuando la cola llegua a  5 datos o más de 5    
        
        /*Si yo quiero ir imprimendo
        también los valores que hay en la cola
        uint32_t valor;
        if (xQueuePeek(cola_boton, &valor, pdMS_TO_TICKS(1000)) == pdPASS)
        {
            ESP_LOGI("COLA", "Valor (sin borrar): %" PRIu32, valor);
        }
        */

        
        
            if(uxQueueMessagesWaiting(boton_queue) >= 5) //Si hay 5 o más mensajes en la cola
                {
                    if(xQueueReceive(boton_queue, &contador_recibido_tmp /*&boton.contador_presionado*/, 0) == pdPASS)
                    {
                        printf("Valor extraido: %ld\n", contador_recibido_tmp); 
                    }
                    else
                    {
                        printf("ERROR AL RECIBIR LA VARIABLE DE LA COLA\n");
                    }
                }
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
/*ENVIAR*/
static void boton_contador(void * pvParameters)
{
    for(;;)
    {
        if (boton_leer()) {
            boton_presionado++;

            if (boton_queue != NULL) { //Si existe la cola 
                if(xQueueSend(boton_queue, &boton_presionado /*boton.contador_presionado*/, 0) != pdPASS)
                {
                    printf("ERROR AL ENVIAR LA VARIABLE A LA COLA\n");
                }
                else
                {
                    printf("Se ha enviado el valor a la cola: %ld\n", boton_presionado);
                }
            }
            
            
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Espera 100 ms antes de verificar nuevamente
    }
}