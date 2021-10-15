#include <msp430.h>
#include <stdint.h>
#include "flash_memory.h"
#include <stdbool.h>
#include <drivers/uart.h>


/**
 * main.c
 * Pinout
 * MEM  <-> MSP
 * 1 (CE)   1.4     10.0
 * 2 (SO)   4.3     5.5
 * 3 (WP)   2.7
 * 4 (GND)
 * 5 (SI)   4.2     5.4
 * 6 (CLK)  1.5     5.6
 * 7 (HOLD) 2.6
 * 8 (VCC)
 */

#define ERASE_CHIP 0

#define buffer_size 255

uint32_t current_address = 0;
uint32_t bytePosition = 0;
volatile uint8_t RX_Buffer[buffer_size] = {0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE};
#define target 1

// Size of Bitstream
#define BITFILE_SIZE    40704
#ifdef target
#define pageSize        65535
#else
#define pageSize        255
#endif

#pragma PERSISTENT(protect)
volatile unsigned char protect = 0;


volatile uint8_t *data = RX_Buffer;
volatile uint8_t status = 0;
volatile uint8_t status2 = 0;

volatile unsigned char b = 0x12;

uint8_t buffer = 0;

bool doMemWrite = false;
bool newData = false;

uint32_t address_0, address_1, address_2;

void uartInitialize(void);
void jtagSetup();
void gpioSetup();

int main(void)
{

//    uint8_t bloco = 0;
    uint32_t i = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

#ifdef target
    //ENABLE MEMORY CHIP SELECT
    P5DIR |= BIT7;
    P5OUT |= BIT7;
    __delay_cycles(1000);
    P5OUT &= ~BIT7;
#else
    P2DIR |= BIT4;
    P2OUT |= BIT4;
    __delay_cycles(1000);
    P2OUT &= ~BIT4;
#endif
    FRCTL0 = FRCTLPW | NWAITS_1;
    uartInitialize();
//     __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled



    spi_setup();

    jtagSetup();
    gpioSetup();

    memory_setup();

    volatile uint8_t id[5];
    memory_id((uint8_t*) id);

#ifndef ERASE_CHIP
    memory_chip_erase();
#endif



    // Change to UART Buffer size - Read chunks of memory in debug mode
    uint8_t data2[1024] = {0x00};
    memory_read(0, data2, 1024);
    memory_read(1024, data2, 1024);
    memory_read(2048, data2, 1024);
    ////////////////////////////////////////////////////////////////////

    protect = 1;
    while(1)
    {
        // If you want to fill the memory with some data, comment this line below
        ////////////////////////////////////////////////////////////////////
        uartReceiveData(buffer);
        ///////////////////////////////////////////////////////////////////

            if (bytePosition > buffer_size){
                doMemWrite = true;
            } else {
                RX_Buffer[bytePosition] = buffer;
                bytePosition++;
            }
            if (doMemWrite){

                bytePosition = 0;
                data = RX_Buffer;
                memory_page_program(current_address, data, 256);
                current_address = current_address + 256;
                doMemWrite = false;
            }
    }

    return 0;
}


//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector = USCI_A0_VECTOR
//__interrupt void USCI_A0_ISR(void)
//#elif defined(__GNUC__)
//void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
//#else
//#error Compiler not supported!
//#endif
//{
//  switch(__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
//  {
//    case USCI_NONE: break;
//    case USCI_UART_UCRXIFG:
//      b = UCA0RXBUF;
//      UCA0TXBUF = UCA0RXBUF;
//      newData = true;
//      __no_operation();
//      break;
//    case USCI_UART_UCTXIFG: break;
//    case USCI_UART_UCSTTIFG: break;
//    case USCI_UART_UCTXCPTIFG: break;
//  }
//}


//#if !load_memory
//    if(protect == 0)
//    {
//        address_2 = 0;
//        for(address_0 = 0; address_0 < 10; address_0++)
//        {
//            data = RX_Buffer; //add a breakpoint at this line
//            for(address_1 = 0; address_1 < BITFILE_SIZE; address_1 = address_1 + 256)
//            {
//                memory_page_program(address_2, data, 256);
//                address_2 = address_2 + 256;
//                data = data + 256;
//            }
//        }
//    }
//#endif

void gpioSetup(void){


    // Reset procedure
//    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P10, GPIO_PIN0);

    // FPGA MODE 0
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);
    // FPGA MODE 1
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
    // FPGA MODE 2
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);

    // uc_MUX_SEL -> Gives access to MSP430
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);

    // uc_MUX_OE
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);

//    __delay_cycles(10000);

    //FPGA_RST_HARD
//    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P10, GPIO_PIN0);

}

void jtagSetup(){
    // JTAG CONFIGURATION MODE

    // Reset procedure
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P10, GPIO_PIN0);

    // FPGA MODE 0
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN5);
    // FPGA MODE 1
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
    // FPGA MODE 2
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);

    // uc_MUX_SEL
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);

    // uc_MUX_OE
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);

    __delay_cycles(100);

    //FPGA_RST_SOFT
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN0);
    //FPGA_RST_APP
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P7, GPIO_PIN0);
    //uC_RST_APP
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P7, GPIO_PIN1);
    //FPGA_RST_HARD
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P10, GPIO_PIN0);
}
