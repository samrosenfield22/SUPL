/*
 SYSTEM.H contains function declarations, constants and external variables for SYSTEM.C
 
 Written on 3/16/17
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif


    
#include <xc.h>
#include <stdbool.h>
#include "pwm.h"
    
    
#define OSC_FREQ (12000000)
#define SYS_FREQ (OSC_FREQ*2)     //24x mul, 12x div (as set in config.c)
#define PBCLK_FREQ (SYS_FREQ/1)    //divide by FPBDIV
                                //see http://www.microchip.com/forums/m578703.aspx
    
#define USEC_PER_TICK (50)
#define INTERVALS_PER_MSEC (1000 / USEC_PER_TICK)
#define INTERVALS_PER_SEC (1000000 / USEC_PER_TICK)


    
//****************************************   function prototypes   ****************************************
void setupGPIO(void);
void setupTimer1(void);
void delayms(unsigned short);
void delayus(unsigned short);

//****************************************   external variables   ****************************************
extern unsigned long SYSTEM_TIMER;



#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

