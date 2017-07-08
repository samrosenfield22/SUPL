/*
 UART.C defines functions for accessing the EUSART modules in the PIC MCU
 They are implemented in higher-level functions, such as the bluetooth library.
 
 Written on 3/16/17
 */

#include "uart.h"

//local definition of global variables
char uartbuf[65];
char *uartptr = NULL;


/*
 Name: setupUART()
 Arguments: unsigned int baud (baud rate)
 Return: void
 Description: initializes the UART1 module with the given baud rate. Also enables
 UART1 interrupts (such as receive interrupts), and clears the buffer string where
 incoming bytes are stored.
 This function must be called before any of the other UART1 functions are used.
 Additional notes: 
 */
void setupUART(unsigned int baud)
{
    
    
    unsigned long brg;
    
    BRGH = 0;
    brg = (OSC_FREQ>>6) / baud; --brg;
    SPBRG = brg;
    
    BAUDCONbits.BRG16 = 0;
    TXSTAbits.SYNC = 0;     //asynchronous mode
    RCSTAbits.CREN = 1;     //enables receiver
    RCSTAbits.SPEN = 1;     //enables serial port
    TXSTAbits.TXEN = 1;     //transmit enable (must happen after SPEN is set)
    
    RCIF = 0;               //clear UART receive flag
    RCIE = 1;               //
}

/*
 Name: sendUARTbyte()
 Arguments: unsigned char byte (data to be transmitted)
 Return: void
 Description: Waits for the last byte to be sent, then sends the current byte.
 Delays for 100 microseconds after loading the byte.
 Additional notes: 
 */
void sendUARTbyte(unsigned char byte)
{
    while(!TRMT); //wait for last transmission to finish
    TXREG = byte;
    delayus(UART_DELAY);
}

/*
 Name: clearUART1buffer()
 Arguments: void
 Return: void
 Description: Clears the entirety of the UART receive buffer (replaces it with 0s)
 and moves the pointer to the start of the buffer.
 Additional notes: 
 */
void clearUARTbuffer()
{
    //reset the pointer
    uartptr = uartbuf;
    
    //*uart1ptr = '\0';     //this will be more efficient (as long as it works)
    memset(uartbuf, '\0', 65);
}

/*char readUART1byte()
{
    unsigned int timestamp = SYSTEM_TIMER;
    
    //while(U1STAbits.URXDA == 0);    //wait while receive buffer is empty
    while(1)
    {
        if (U1STAbits.URXDA == 1) return (char)U1RXREG;
        if (SYSTEM_TIMER - timestamp > (UART_RC_TIMEOUT*20)) return 0;
    }
    
}
*/

/*
 Name: sendUARTstring()
 Arguments: const char *string (pointer to the string to be transmitted)
 Return: void
 Description: Indexes through a string of bytes and transmits each one.
 This will continue until a null character ('\0') is encountered, so the argument string
 to this function MUST be null-terminated!
 Additional notes: 
 */
void sendUARTstring(const char *string)
{
    char *pt;
    
    for(pt=string; *pt; pt++) sendUARTbyte(*pt);
}




