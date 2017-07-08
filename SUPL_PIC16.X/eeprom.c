/*
 EEPROM.C defines functions to interface with a AT24CM02 EEPROM IC.
 
 Written on 3/16/17
 */

#include "eeprom.h"


/*
 Name: writeEEPROMbyte()
 Arguments: unsigned long start_address (memory address the byte is written to),
 unsigned char *data (pointer to the byte to be written)
 Return: unsigned char (1 if the write was successful)
 Description: Attempts to write a byte to EEPROM at the given address
 Additional notes: for more information see
 
 http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8828E-SEEPROM-AT24CM02-Datasheet.pdf
 page 8
 */
unsigned char writeEEPROMbyte(char ID, unsigned long start_address, unsigned char *data)
{
    
    //split the address into 3 sections
    char MSB_address = (start_address>>16) & 0b11;
    char First_Word_Address = (start_address>>8) & 0xFF;
    char Second_Word_Address = start_address & 0xFF;
    
    char datastr[3];
    
    //char address = (DIB|HAB|MSB_Address)>>1;
    char address;
    
    //set up the i2c slave address
    if(ID==0) address = EEPROM0_ADDR;
    else if(ID==1) address = EEPROM1_ADDR;
    else return 1;
    address |= MSB_address;
    
    //set up the string to be written
    datastr[0] = First_Word_Address;
    datastr[1] = Second_Word_Address;
    datastr[2] = *data;
    
    //write to device
    writeI2Cstring(datastr, 3, address);
    
    
    // Allow memory to be written
    // Write Cycle Time (tWR)
    delayms(10);
    
    return 0;
}

/*
 Name: readEEPROMbyte()
 Arguments: unsigned long start_address (memory address to read from),
 unsigned char *data (pointer to the char where the read byte will be stored)
 Return: unsigned char (1 if the read failed -- change this!!!!)
 Description: Attempts to read a byte from the EEPROM at the given address.
 Additional notes: 
 */
unsigned char readEEPROMbyte(char ID, unsigned long start_address, unsigned char *data)
{
    
    //split the address into 3 sections
    char MSB_address = (start_address>>16) & 0b11;
    char First_Word_Address = (start_address>>8) & 0xFF;
    char Second_Word_Address = start_address & 0xFF;
    
    char datastr[2];
    
    //char address = (DIB|HAB|MSB_Address)>>1;
    char address;
    
    //set up the i2c slave address
    if(ID==0) address = EEPROM0_ADDR;
    else if(ID==1) address = EEPROM1_ADDR;
    else return 1;
    address |= MSB_address;
    
    //set up the string with the location to be read
    datastr[0] = First_Word_Address;
    datastr[1] = Second_Word_Address;
    
    //read from the specified location
    readI2C(address, datastr, 2, &data);
    
    // Allow memory to be read
    delayms(10);
    
    return 0;
}

/*
 Name: writeEEPROMstring()
 Arguments: unsigned long start_address (memory address the string should be written to),
 unsigned char *data (pointer to the string being written)
 Return: char (1 if write was successful, 0 if failed)
 Description: Attempts to write a string to the EEPROM at the given address.
 Additional notes: 
 */
char writeEEPROMstring(char ID, unsigned long start_address, unsigned char *data)
{
    //check if the string will fit
    
    //write the string
    unsigned char *pt = data;
    while(*pt) 
    {
        if (!writeEEPROMbyte(ID, start_address, pt)) return 0;
    }
    
    return 1;
}


