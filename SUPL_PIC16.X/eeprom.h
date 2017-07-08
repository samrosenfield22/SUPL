/*
 EEPROM.H contains function declarations, constants and external variables for EEPROM.C
 
 Written on 3/16/17
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h> 
//#include <plib.h>
#include "system.h"
#include "i2c.h"

#define EEPROM0_ADDR 0x50
#define EEPROM1_ADDR 0x54
        
    
//void EEPROM_Startup_Delay(void);
unsigned char writeEEPROMbyte(char, unsigned long, unsigned char *);
unsigned char readEEPROMbyte(char, unsigned long, unsigned char *);
char writeEEPROMstring(char, unsigned long, unsigned char *);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

