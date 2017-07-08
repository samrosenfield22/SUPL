/*
 GYRO.H contains function declarations, constants and external variables for GYRO.C
 
 Written on 3/16/17
 */

#ifndef GYRO_H
#define	GYRO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> 
//#include <plib.h>
#include "system.h"
#include "i2c.h"
    
#define GYRO_ADDR 0x69
    
unsigned char GYRO_I2C_Init(void);


#ifdef	__cplusplus
}
#endif

#endif	/* GYRO_H */

