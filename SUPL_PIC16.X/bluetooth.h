/*
 BLUETOOTH.H contains function declarations, constants and external variables for BLUETOOTH.C
 
 Written on 3/16/17
 */

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <string.h>
#include "uart.h"
    
#define NEW_BT_MODULE (0)
    
void configureBTModule(void);
char verifyBT(void);
char connectBT(void);
void resetBT(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BLUETOOTH_H */

