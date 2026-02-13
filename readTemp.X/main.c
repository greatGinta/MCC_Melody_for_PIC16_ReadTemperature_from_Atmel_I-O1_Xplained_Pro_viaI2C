 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
? [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

#define deviceAddr  0x4F
#define tempReg     0

uint16_t readTemp();

int main(void)
{
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable(); 
    INTERRUPT_PeripheralInterruptEnable(); 


    while(1)
    {
        uint16_t temp = readTemp();
        if(temp == 0xFFFF){
            printf("I2C Error\r\n");
        } else {
            printf("Temp: %.2f\r\n", (float)temp/256);
        }
        __delay_ms(1000);
    }    
}

uint16_t readTemp(){
    uint8_t reg = tempReg;
    uint8_t rxBuf[2];
    i2c_host_error_t err = I2C1_ErrorGet();
    
    while(I2C1_IsBusy());
    
    if(!I2C1_WriteRead(deviceAddr, &reg, 1, rxBuf, 2)){
        printf("I2C Write Read Error\r\n");
        return 0xFFFF;
    }
    
    while(I2C1_IsBusy());
    
    if(err != I2C_ERROR_NONE){
        printf("Error Occurred: %d\r\n", err);
    }
    
    uint16_t rawTemp = (rxBuf[0] << 8) | rxBuf[1];
    
    return rawTemp;
}