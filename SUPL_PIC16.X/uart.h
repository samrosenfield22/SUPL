/*
 UART.H contains function declarations, constants and external variables for UART.C
 
 Written on 3/16/17
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <string.h>     //for memset
#include "system.h"
    
#define UART_DELAY (100)        //us between bytes
//#define UART_RC_TIMEOUT (10)    //timeout in ms
    
//function prototypes
void setupUART(unsigned int);
void sendUARTbyte(unsigned char);
void clearUARTbuffer(void);
//void sendUART1string(const char *, const unsigned char);
void sendUARTstring(const char *);


//external variables
extern char uartbuf[65];
extern char *uartptr;

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

