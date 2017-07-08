/*
 RTC.H contains function declarations, constants and external variables for RTC.C
 
 Written on 3/16/17
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h> 
#include "system.h"
#include "i2c.h"

#define RTC_ADDR 0x6F
    
char RTC_Vbatt_Enable(void);
char RTC_INT3_Init(void);
char RTC_Start(void);
char RTC_Read_Stat(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

