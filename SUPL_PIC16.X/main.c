/*

 
 All code is written to run on a PIC16LF1719 microcontroller. This device
 should be powered from a 3.3V supply.
 
 Written by Sam Rosenfield
 on 3/21/2017
 
 */



#include <xc.h>

#include "system.h"
#include "uart.h"
//#include "bluetooth.h"



void main(void)
{
    
    //set up all core and peripheral modules
    INTCONbits.GIE = 0b0;   //disable interrupts while initializing
                    //interrupts are re-enabled in setupSysInterrupts()
    setupGPIO();
    setupTimer1();
    setupPWM();
    setupADC();
    setupUART(9600);
    setupSPI();
    setupI2C();
    setupSysInterrupts();
    
    //sendUARTstring("henlo\n");
    //initialize devices
    /*
    //bt
     //gyro
     //etc
    */
    
    //main loop
    while(1)
    {
        //your code here
    }
    
    
}

