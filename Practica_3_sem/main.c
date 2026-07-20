/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include"led.c"


void delay(__uint32_t ret);


void app_main(void)
{
    led_init();

    for(;;)
    {
        led_on();
        delay(50);
        led_off();
        delay(50);
    }

}

void delay(__uint32_t ret)
{
    while(ret--)
    {
        for(volatile __uint32_t i=0; i<100000UL; i++){};
    }
}
