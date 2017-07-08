/*
 I2C.C defines functions for accessing the MSSP module in the PIC MCU.
 They are implemented in higher-level functions, such as the EEPROM library.
 
 Written on 3/16/17
 */

#include "i2c.h"

void setupI2C()
{
    
    unsigned short brg;
    
    SSP1CON1bits.SSPEN = 0b0;   //disable mssp while configuring
    
    //set mssp clock
    brg = OSC_FREQ / I2C_FREQ;
    brg = (brg>>2) - 1;
    SSP1ADD = brg;
    
    SSP1CON1bits.SSPM = 0b1000;     //mssp in i2c master mode, clock = FOSC / (4*(SSP1ADD+1))
    
    //SSP1IE = 0b1;
    SSP1CON1bits.SSPEN = 0b1;   //enable mssp
}

char writeI2Cstring(char *string, unsigned char len, char addr)
{
    unsigned char i;
    char *data = string;
    
    i2cStart();
    
    if (i2cWrite(addr<<1)) return 1;
    
    for(i=0; i<len; ++i)
    {
        if (i2cWrite(*data)) return 1;
        
        data++;
    }
    
    i2cStop();
    
    return 0;
}


unsigned char readI2C(unsigned char addr, unsigned char *reg_addrs, unsigned char len, unsigned char *data)
{
    
    
    if (writeI2Cstring(reg_addrs, len, addr)) return 1;
    
    i2cRestart();
    if (i2cWrite((addr<<1) + 1)) return 1;
    
    
    //enable receive mode
    // RCEN clears after 8th bit of master receive data byte
    delayus(I2C_DELAY);
    SSP1CON2bits.RCEN = 1;           //enable receive mode
    
    delayus(I2C_DELAY);
    while(!SSP1STATbits.BF);        //wait until receive is complete
    *data = SSP1BUF;                //read data from I2C buffer
    
    i2cNack();
    
    i2cStop();
    delayms(5);
    
    return 0;
}


void scanI2C()
{
    unsigned char i;
    
    for (i=1; i<128; ++i)
    {
        i2cStart();
        
        if (i2cWrite(i<<1) == 0)    //slave device at given address ACK'd
        {
            asm("nop");     //set a breakpoint here
        }
        
        i2cStop();
    }
}


//////////////////////////////// LOW-LEVEL I2C FUNCTIONS ///////////////////
void i2cStart()
{
    delayus(I2C_DELAY);
    SSP1CON2bits.SEN = 1;                        // Send the start bit 
}

void i2cRestart()
{
    delayus(I2C_DELAY);
    SSP1CON2bits.RSEN = 1;                        // Send the start bit 
}

void i2cStop()
{
    delayus(I2C_DELAY);
    SSP1CON2bits.PEN = 1;                        // Send the start bit 
}

unsigned char i2cWrite(unsigned char byte)
{
    delayus(I2C_DELAY);
    SSP1BUF = byte;
    
    delayus(I2C_DELAY);
    if (WCOL) {return 1;}
    return (SSP1CON2bits.ACKSTAT);
}

void i2cNack()
{
    SSP1CON2bits.ACKDT = 1; // Set NACK bit
    SSP1CON2bits.ACKEN = 1; // Send NACK bit
}