/*
 I2C.C defines functions for initializing and accessing core system modules and
 functionality, such as the I/O, timer, and the interrupt controller. It also
 defines global variables externally declared in SYSTEM.H.
 
 Written on 3/16/17
 */

#include "system.h"

//local definition of global variables
unsigned long SYSTEM_TIMER = 0;


/*
 Name: setupGPIO()
 Arguments: void
 Return: void
 Description: Sets up all I/O pin directions, states, mappings, etc.
 Additional notes: 
 */
void setupGPIO()
{
    //read all ports to clear
    PORTA; PORTB; PORTC; PORTD; PORTE;
    
    //disable open drain
    ODCONA = 0x00; ODCONB = 0x00; ODCONC = 0x00; ODCOND = 0x00; ODCONE = 0x00;
    
    //set all pins as digital I/O
    ANSELA = 0x00; ANSELB = 0x00; ANSELC = 0x00; ANSELD = 0x00; ANSELE = 0x00;
    
    
    //set pin directions
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    //set weak pull-ups
    WPUA = 0x00; WPUB = 0x00; WPUC = 0x00; WPUD = 0x00; WPUE = 0x00;
    
    
    //pin mapping for UART1/2
    /*RPC7R = 0b0001;     //map RPC7, which is pin RC7, to UART1 TX
    U1RXR = 0b0101;     //map UART1 RX to RPC6, which is pin RC6
    RPC4R = 0b0010;     //map RPC4, which is pin RC4, to UART2 TX
    U2RXR = 0b0110;     //map UART2 RX to RPC8, which is pin RC8
    */
    //pin mapping for I2C
    
}

/*
 Name: setupTimer1()
 Arguments: void
 Return: void
 Description: Sets up the TMR1 module, which is used to generate system timer interrupts.
 Additional notes: 
 */
void setupTimer1()
{
    //set up/enable timer1
    T1CONbits.TMR1ON = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS = 0b00;
    //256x prescale
    
    //set up timer1 interrupt
    TMR0IF = 0;     //clear timer 1 interrupt flag
    TMR0IE = 1;     //enable timer 1 interrupt
}


/*
 Name: delayms()
 Arguments: unsigned short ms (number of milliseconds to delay by)
 Return: void
 Description: Pauses execution for the given number of milliseconds.
 Additional notes: 
 */
//delays by ms milliseconds
void delayms(unsigned short ms)
{
    unsigned short i;
    unsigned long timestamp;
    
    for(i=0; i<ms; ++i)
    {
        timestamp = SYSTEM_TIMER;
        while((SYSTEM_TIMER - timestamp) < INTERVALS_PER_MSEC);
    }
    
}

/*
 Name: delayus()
 Arguments: unsigned short us (number of microseconds to delay by)
 Return: void
 Description: Pauses execution for the given number of microseconds.
 Note that this function only has a resolution of 50us.
 Additional notes: Function may be removed.
 */
void delayus(unsigned short us)
{
    unsigned int timestamp;
    
    timestamp = SYSTEM_TIMER;
    while((SYSTEM_TIMER - timestamp) < (us/50));
}


