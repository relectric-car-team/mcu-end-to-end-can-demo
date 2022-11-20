/*
 * File:   main.c
 * Author: ratik
 *
 * Created on January 8, 2021, 5:25 PM
 */

#include "mcc_generated_files/mcc.h" 

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    int8_t counter = 0;
    while (1)
    {
        //__delay_ms(100);
        // Writing -> serial bus 
        printf("%d\n", counter);
        counter++;
        // Reading <- serial bus
        
    }
}