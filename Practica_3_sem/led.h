#ifndef led_h
#define led_h
//PIN PARA HACER UNA DIGITAL OUTPUT
#define GPIO_LED GPIO_NUM_18 


void led_init(void);
void led_on(void);
void led_off(void);

#endif