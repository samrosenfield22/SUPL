/*
 PWM.H contains function declarations, constants and external variables for PWM.C
 
 Written on 3/16/17
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>
#include "system.h"

//function declarations
void setupPWM(void);
bool addPWMchannel(unsigned char, unsigned char, unsigned char);
bool removePWMchannel(unsigned char, unsigned char);
void pwm_interrupt_manager(void);

//externally defined global variables
extern bool PWM_ENABLE;
extern unsigned char duty[5][8];
extern bool duty_en[5][8];

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

