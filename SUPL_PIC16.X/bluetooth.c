/*
 BLUETOOTH.C defines wrappers for functions defined in UART.C.
 These are used to interface with a HM-11 (https://www.seeedstudio.com/Bluetooth-V4.0-HM-11-BLE-Module-p-1803.html)
 bluetooth BLE module.
 
 Written on 3/16/17
 */

#include "bluetooth.h"

/*
 Name: configureBTModule()
 Arguments: void
 Return: void
 Description: configures a HM-11 BLE module.
 If the NEW_BT_MODULE parameter (in bluetooth.h) is set to 1,
 this function will set default configurations, such as the correct baud rate and
 master/slave mode, on the module
 Additional notes: 
 */
void configureBTModule()
{
    #if (NEW_BT_MODULE == 1)
        //change the baud rate from 115200 (default) to 9600, and reset the BT module
        setupUART(115200);                  //if the baud rate is already 9600, this won't change anything, which is fine
        sendUARTstring("AT+BAUD0\0");     //send BT module's baud rate to setting 0, which is 9600 bits/s
        delayms(10);
        resetBT();
        
        //restart UART with 9600 baud
        setupUART(9600);                    //re-initialize UART with new baud rate
        //sendUARTstring("AT+ROLE1\0");     //master mode
        sendUARTstring("AT+ROLE0\0");     //slave mode
        delayms(10);
        
        //change the name, and reset the module again
        sendUARTstring("AT+NAMESWGBluetooth\0");
        delayms(10);
        resetBT();
    #else
        //(re)start UART with 9600 baud
        setupUART(9600);                    //re-initialize UART with new baud rate
        //sendUARTstring("AT+ROLE1\0");     //master mode
        sendUARTstring("AT+ROLE0\0");     //slave mode
    
        delayms(500);
    #endif
    
    
}

/*
 Name: verifyBT()
 Arguments: void
 Return: char (1 if the HM-11 module successfully echoed, 0 otherwise)
 Description: Sends "AT" to the bluetooth module, and checks its response after 100 ms.
 If the module responds with "OK", it is properly connected and configured.
 Additional notes: 
 */
char verifyBT()
{
    clearUARTbuffer();     //in case the last response(s) are still stored
    
    sendUARTstring("AT\0");
    delayms(100);
    
    if (strcmp(uartbuf, "OK") == 0)
    {
        clearUARTbuffer();
        return 1;
    }
    else {return 0;}
}

//this function will *probably* be removed, since the hm-11 ble acts as a slave device in
//the connection process
char connectBT()
{
    const char conn_str[19] = "AT+CON209148A85478\0";     //mac address of my laptop's BT module
    
    clearUARTbuffer();
    sendUARTstring(conn_str);
    delayms(5000);
    
    //if (strcmp(uartbuf, "OK+CONN") == 0)
    //{
    //    return uartbuf[7];
    //}
    //else
    //{
    //    return 0;
    //}
    return 'A';
    
}

/*
 Name: resetBT()
 Arguments: void
 Return: void
 Description: resets the bluetooth module, waits for a second to reboot.
 Additional notes: 
 */
void resetBT()
{
    sendUARTstring("AT+RESET\0");
    delayms(1000);
}