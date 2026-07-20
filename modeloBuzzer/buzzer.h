#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h> /*En los .h no hace falta ponerlo, 
                    pero como hay un bool para asegurar*/

void buzzer_init(void);
void buzzer_beep(bool state);

#endif

/*END OF FILE*/