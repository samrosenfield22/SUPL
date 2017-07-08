/*
 I2C.H contains function declarations, constants and external variables for I2C.C
 
 Written on 3/16/17
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> 
//#include <plib.h>
#include "system.h"
    
#define I2C_FREQ (100000)
#define I2C_DELAY (50)
    
///////////////////////////////////////////////
void setupI2C(void);
char writeI2Cstring(char *, unsigned char, char);
unsigned char readI2C(unsigned char, unsigned char *, unsigned char, unsigned char *);
void scanI2C(void);

void i2cStart(void);
void i2cRestart(void);
void i2cStop(void);
unsigned char i2cWrite(unsigned char);
void i2cNack(void);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

