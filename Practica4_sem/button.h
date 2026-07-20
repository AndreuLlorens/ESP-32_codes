#ifndef BUTTON_H
#define BUTTON_H

#include<stdlib.h>
#include<stdio.h>
#include"driver/gpio.h"

typedef enum
{
    BUTTON_STATE_RELEASED = 0,
    BUTTON_STATE_PRESSED = 1
} button_state_t;

void button_init(void);
button_state_t button_read(void);


#endif