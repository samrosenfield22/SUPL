/*
 INTERRUPT.H contains function declarations, constants and external variables for INTERRUPT.C
 
 Written on 3/16/17
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include "system.h"
#include "uart.h"
#include "pwm.h"

void setupSysInterrupts(void);
void timer0ISR(void);
void uartISR(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

