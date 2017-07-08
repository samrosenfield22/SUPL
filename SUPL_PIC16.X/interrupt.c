/**/

#include "interrupt.h"

/*
 Name: setupSysTinerrupts()
 Arguments: void
 Return: void
 Description: Sets up and enables system interrupts.
 Additional notes: 
 */
void setupSysInterrupts()
{
    INTCONbits.GIE = 0b1;
}

void interrupt ISR(void)
{
    INTCONbits.GIE = 0b0;
    
    if (TMR0IE && TMR0IF)
    {
        timer0ISR();
    }
    if (RCIE && RCIF)
    {
        uartISR();
    }
    
    INTCONbits.GIE = 0b1;
}

/*
 Name: timer1ISR()
 Arguments: void
 Return: void
 Description: This ISR runs every time the timer1 module overflows.
 It updates the master SYSTEM_TIMER, updates all human-readable time values, and
 sets several event flags if needed.
 Additional notes: 
 */
void timer0ISR()
{
    TMR0IF = 0;
    TMR1 = 0xFDE5;      //timer1 overflows exactly every 50us
    SYSTEM_TIMER++;
    
    if(PWM_ENABLE)
    {
        pwm_interrupt_manager();
    }
    
        
}

/*
 Name: uartISR()
 Arguments: void
 Return: void
 Description: Every time a UART byte is received, this ISR adds it to the buffer, indexes
 the buffer, and checks to see if anything should happen.
 Additional notes: 
 */
void uartISR()
{
    if (RCIF)
    {
        
        *uartptr = RC1REG;
        RCIF = 0;  //clear uart1 rx interrupt flag
        //maybe the flag needs to remain set for a certain amount of time while reading the char?
        
        uartptr++;
        
        //check if we've reached the end of the buffer
        //this should probably be uncommented
        if ((uartptr - uartbuf) >= 64)
        {
            //flush the buffer and reset the pointer
            clearUARTbuffer();
        }
        
        *uartptr = '\0';
    }
}

