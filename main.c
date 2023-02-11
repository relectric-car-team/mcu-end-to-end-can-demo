/*
 * File:   main.c
 * Author: ratik
 *
 * Created on January 8, 2021, 5:25 PM
 */

#include "mcc_generated_files/mcc.h" 
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"
#define CAN_TX_BUFF  "TEMPERATURE SENSOR ON"

/*
                         Main application
 */
//void main(void)
//{
//    // Initialize the device
//    SYSTEM_Initialize();
//
//    // Enable the Global Interrupts
//    //INTERRUPT_GlobalInterruptEnable();
//
//    // Disable the Global Interrupts
//    //INTERRUPT_GlobalInterruptDisable();
//    int8_t counter = 0;
//    while (1)
//    {
//        //__delay_ms(100);
//        // Writing -> serial bus 
//        printf("%d\n", counter);
//        counter++;
//        // Reading <- serial bus
//        
//    }
//}

void main(void) 
{
    CAN_MSG_OBJ msg;
    uint8_t data[32] = CAN_TX_BUFF;

    SYSTEM_Initialize();
    printf("1\r\n");
    
    // Set the mode to configure the CAN1; Explicit at the moment: move to Initialize later;
    CAN1_OperationModeSet(CAN_CONFIGURATION_MODE);
    
    // Checks if the mode is set to configure
    if(CAN_CONFIGURATION_MODE == CAN1_OperationModeGet())
    {
        printf("2\r\n");
        // Change the mode to set to can normal 2.0
        if(CAN_OP_MODE_REQUEST_SUCCESS == CAN1_OperationModeSet(CAN_NORMAL_2_0_MODE))
        {
            printf("3\r\n");
            
            // Configure the format of the message
            msg.msgId = 0x1FFFF;
            msg.field.formatType = CAN_FD_FORMAT;
            msg.field.brs = CAN_NON_BRS_MODE;
            msg.field.frameType = CAN_FRAME_DATA;
            msg.field.idType = CAN_FRAME_EXT;
            msg.field.dlc = DLC_32;
            msg.data = data;

            // Check if the channel is available for transmission
            while(CAN_TX_FIFO_AVAILABLE == (CAN1_TransmitFIFOStatusGet(CAN1_TX_TXQ) & CAN_TX_FIFO_AVAILABLE))
            {
                printf("4\r\n");
                // Transmits the data to the determined channel
                CAN1_Transmit(CAN1_TX_TXQ, &msg);
                __delay_ms(1000);
            }
        }
    }
}