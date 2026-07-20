#include <stdio.h>
#include<stdlib.h>
#include"boutton.c"


void delay(__uint32_t ret);


void app_main(void)
{
    printf("SE ESTA CONFIGURANDO EL BOTON \n");
    boutton_init(void);

    for(;;)
    {
        //LECTURA DEL BOTON
        button_state_t lectura = button_read();
        if( lectura == BUTTON_STATE_PRESSED)
        {
            printf("BOTON PRESIONADO \n");
        }
        else
        {
            printf("BOTON LIBERADO \n");
        }
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
