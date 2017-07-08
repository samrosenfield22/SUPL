/*
 RTC.C defines functions to interface with a _____ real time clock.
 
 Written on 3/16/17
 */

#include "rtc.h"

/*
 Name: ()
 Arguments: void
 Return: void
 Description: 
 Additional notes: 
 */
char RTC_Vbatt_Enable()
{
    const char Vbatt_enable_str[] = {0x03, 0x08};
    //0x03: select RTC weekday and VBAT EN register
    //0x08: Set bit 3 HIGH - turn on VBat Input Enabled
    
    writeI2Cstring(Vbatt_enable_str, 2, RTC_ADDR);
    
    return 0;
}

/*
 Name: ()
 Arguments: void
 Return: void
 Description: 
 Additional notes: 
 */
// This function:
// Send I2C data to RTC module to setup for timekeeping application
//starts a 1 second period square wave, supposedly
char RTC_INT3_Init()
{
    const char RTC_Int_init_str[] = {0x07, 0x40};
    //0x07: ?
    //0x40: set bit 6 to output 1 sec square-wave
    
    writeI2Cstring(RTC_Int_init_str, 2, RTC_ADDR);
    
    return 0;
}

/*
 Name: ()
 Arguments: void
 Return: void
 Description: 
 Additional notes: 
 */
char RTC_Start()
{
    const char RTC_start_str[] = {0x00, 0x80};
    //0x00: select RTC seconds register
    //0x80: set bit 7 high, turn on oscillator
    
    writeI2Cstring(RTC_start_str, 2, RTC_ADDR);
    
    return 0;
}

/*
 Name: ()
 Arguments: void
 Return: void
 Description: 
 Additional notes: 
 */
char RTC_Read_Stat()
{
    const char seconds_reg = 0x03;
    char status;    //is that what we're reading?
    
    readI2C(RTC_ADDR, &seconds_reg, 1, &status);
    
    
    //if (writeI2Cbyte(0xFF)) return 1;   // Set bit 7 HIGH - turn on oscillator
    
    //if(buffer&0b00100000) LATD |=_LED9;
    
    return 0;
}

