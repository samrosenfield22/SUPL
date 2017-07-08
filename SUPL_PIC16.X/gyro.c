/*
 GYRO.C defines functions to interface with a MPU9250 IMU
 https://store.invensense.com/datasheets/invensense/MPU9250REV1.0.pdf
 
 Written on 3/16/17
 */

#include "gyro.h"

/*
 Name: ()
 Arguments: void
 Return: void
 Description: 
 Additional notes: 
 */
/*unsigned char GYRO_I2C_Init()
{
    unsigned char Address = (0b1101001)<<1; // device type identifier bits
    //char HAB = 0<<3; // Hardware address bit, A2 = 0 (GND)
    unsigned char Read = 1; 
    unsigned char Write = 0;
    
    unsigned char buffer = 0;
    //char MSB_Address = ((EEPROM_AC1_Age>>16) & _2BIT_MASK)<<1;
    //char First_Word_Address = (EEPROM_AC1_Age>>8) & _8BIT_MASK;
    //char Second_Word_Address = EEPROM_AC1_Age & _8BIT_MASK;
    
    
    // Start
    IdleI2C1();
    I2C1CONbits.SEN = 1; // Send start bit
    
    // Check for I2C collisions
    if(I2C1STATbits.BCL)
    {
        //UART4Write("EEPROM_Write_Byte: I2C Bus Collision Resetting Module, Reset\n");
        //LATD &= ~_LED5;
        I2C1CONCLR = 0x8000; // turn module off
        asm("nop");
        I2C1CONSET = 0x8000; // turn module on

        return 0;  
    }
    
    if (writeI2Cbyte(Address | Write)) return 0;   //address + write bit
    if (writeI2Cbyte(0x3C)) return 0;   // Set ACCEL_XOUT_L Register
    
    IdleI2C1();
    I2C1CONbits.RSEN = 1; // Send restart bit
    
    if (writeI2Cbyte(Address | Read)) return 0;   //

    buffer = I2C1RCV;
    
    IdleI2C1();
    StopI2C1();  
    
    return buffer;
}*/

unsigned char GYRO_I2C_Init()
{
    unsigned char data;
    const char *dev_id_addr = 0x00;
    
    readI2C(GYRO_ADDR, &dev_id_addr, 1, &data);
    //note: his code said 0x59, datasheet says 0x68 or 69)
    //pretty sure it's a different imu
    
    //what is this function supposed to do?
    
    return data;
}