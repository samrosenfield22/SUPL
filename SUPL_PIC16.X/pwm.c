/*
 PWM.C defines functions for generating psuedo-pulse width modulation (PWM) signals.
 This implementation is driven by the timer0 interrupt.
 
 Note that these functions have not been tested on hardware yet.
 
 Written on 3/16/17
 */

#include <xc.h>

#include "pwm.h"

bool PWM_ENABLE = 0;
unsigned char duty[5][8];
bool duty_en[5][8];

/*
 Name: setupPWM()
 Arguments: void
 Return: void
 Description: Enables pseudo-pulse width modulation
 Additional notes: interrupts must be enabled with setupSysInterrupts()
 */
void setupPWM()
{
    //clear all duty cycles and enables
    memset(duty, 0, sizeof(duty));
    memset(duty_en, false, sizeof(duty_en));
    
    //set global enable flag
    PWM_ENABLE = 1;
}

/*
 Name: addPWMchannel()
 Arguments: unsigned char port (0 for PORTA, 1 for PORTB, etc.),
 unsigned char pin (pin number on selected port),
 unsigned char dutycycle (8-bit PWM duty cycle)
 Return: bool (true if the PWM channel was added, false if an illegal channel was requested)
 Description: generates an 8-bit PWM waveform on the given pin
 Additional notes: the appropriate TRIS bit must be cleared first
 */
bool addPWMchannel(unsigned char port, unsigned char pin, unsigned char dutycycle)
{
    if((port>5) || (pin>8)) return false;
    
    duty[port][pin] = dutycycle;
    duty_en[port][pin] = true;
    
    return true;
}

/*
 Name: removePWMchannel()
 Arguments: unsigned char port (0 for PORTA, 1 for PORTB, etc.),
 unsigned char pin (pin number on selected port)
 Return: bool (true if the PWM channel was added, false if an illegal channel was requested)
 Description: removes a PWM signal on the given pin, if there is one
 Additional notes: 
 */
bool removePWMchannel(unsigned char port, unsigned char pin)
{
    if((port>5) || (pin>8)) return false;
    
    duty[port][pin] = 0;
    duty_en[port][pin] = false;
    
    return true;
}

/*
 Name: pwm_interrupt_manager()
 Arguments: void
 Return: void
 Description: toggles all PWM-enabled pin states by comparing their assigned duty cycle
 values to the value of the PWM counter
 Additional notes: does the LAT indexing method work? This needs to be tested.
 */
void pwm_interrupt_manager()
{
    static unsigned char cnt = 0;
    char i, j;
    
    char *ports[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
    
    for(i=0; i<5; ++i)                      //index through ports
    {
        for(j=0; j<8; ++j)                  //index through port pins
        {
            if (duty_en[i][j] == true)
            {
                if (duty[i][j] > cnt) *(ports[i]) |= (1<<i);
                else *(ports[i]) &= ~(1<<i);
            }
        }
    }
    /*
    for(i=0; i<8; ++i)                      //PORT A
    {
        if (duty_en[0][i] == true)
        {
            if (duty[0][i] > cnt) LATA |= (1<<i);
            else LATA &= ~(1<<i);
        }   
    }
    */
    
    
    cnt++;
}