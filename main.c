#include <msp430.h>
#include <stdint.h>
#include "flash_memory.h"


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

#define WRITE_SEG_AND_CRC   0
#define load_memory 0

#define BITFILE_SIZE    40704
#pragma PERSISTENT(protect)
volatile unsigned char protect = 0;

#pragma PERSISTENT(FRAM_write)
volatile uint8_t FRAM_write[BITFILE_SIZE+256] = {0xFF};
volatile uint8_t *data = FRAM_write;
volatile uint8_t status = 0;
volatile uint8_t status2 = 0;

//#pragma PERSISTENT(FRAM_write2)
//volatile uint8_t FRAM_write2[1000] = {0xFF};
volatile unsigned char cmd[] = {0x00,0xEB,0x90,0x33,0xFE,0x00,0x07,0x00,0x00,0x30,0xAA,0x43,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x78,0x33,0xFF,0x00,0x09,0x00,0x82,0x00,0x52,0xC8,0xBF,0xE4,0x00,0x00,
                                0x00,0x00,0x4A,0x03,0xFF,0x00,0x11,0xC8,0xC0,0x10,0x8C,0x01,0xC0,0x00,0x00,0x03,
                                0x00,0x00,0x2E,0x1D,0x0F,0x9C,0x07,0x00,0x00,0x00,0x6C,0xC5,0xC5,0xC5,0xC5,0xC5,
                                0xC5,0xC5,0x79};
volatile unsigned char a = sizeof(cmd);
volatile unsigned char b = 0x12;


int main(void)
{
    uint32_t adress_0, adress_1, adress_2;
    uint8_t bloco = 0;
    uint32_t i = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
#if !load_memory
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Configure GPIO
    P2SEL0 |= BIT0 | BIT1;                    // USCI_A0 UART operation
    P2SEL1 &= ~(BIT0 | BIT1);
#endif
    //RESET FPGA
    P3DIR |= BIT3;
    P3OUT &= ~BIT3;

    //on led mcu
    P8DIR |= BIT1;
    P8OUT |= BIT1;

    __delay_cycles(4 * 1000000);

    //ENABLE MEMORY CHIP SELECT
    P10DIR |= BIT0;
    P10OUT |= BIT0;
    __delay_cycles(1000);
    P10OUT &= ~BIT0;

    //MUX SEL ->FPGA
    P9DIR |= BIT6;
#if load_memory
    P9OUT &= ~BIT6; // mcu
#else
    P9OUT |= BIT6;  //fpga
#endif

    //RESET FPGA
    P3DIR |= BIT3;
    P3OUT &= ~BIT3;
    __delay_cycles(1 * 1000000);
    P3OUT |= BIT3;  //POWER ON FPGA (SET 1 TO RESET)
#if load_memory
#else

    do{
        status2 = P3IN & (BIT4 | BIT5);
    }while(status2 != 32);
#endif

    //RESET UTMC APLICATION
    P6DIR |= BIT4;
    P6OUT |= BIT4;
    __delay_cycles(1 * 1000000);
    P6OUT &= ~BIT4;
    __delay_cycles(1 * 1000000);
    P6OUT |= BIT4;

#if !load_memory
    // Startup clock system with max DCO setting ~8MHz
     CSCTL0_H = CSKEY >> 8;                    // Unlock clock registers
     CSCTL1 = DCOFSEL_4 | DCORSEL;             // Set DCO to 8MHz
     CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
     CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
     CSCTL0_H = 0;                             // Lock CS registers

     // Configure USCI_A0 for UART mode
     UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
     UCA0CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
     // Baud Rate calculation
     // 8000000/(16*9600) = 52.083
     // Fractional portion = 0.083
     // User's Guide Table 21-4: UCBRSx = 0x04
     // UCBRFx = int ( (52.083-52)*16) = 1
     UCA0BR0 = 8;                             // 8000000/16/9600
     UCA0BR1 = 0x00;
     UCA0MCTLW |= UCOS16 | UCBRF_10 | 0xF700;
     UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
     UCA0IE |= UCRXIE | UCTXIE;                         // Enable USCI_A0 RX interrupt

     __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled
#endif

//    __delay_cycles(20 * 1000000);

//    P9DIR |= BIT2;
//    P9OUT |= BIT2;  //lachup

//    while(1)
//    {
//        i++;
//    }
    bloco = i;
//    memset(FRAM_write, 0xFF, BITFILE_SIZE+256);

#if load_memory
    spi_setup();
    memory_setup();

    volatile uint8_t id[3];
    memory_id((uint8_t*) id);


    if(protect == 00)
    {
        memory_chip_erase();
    }
#endif
#if WRITE_SEG_AND_CRC
    memory_chip_erase();
#endif

#if load_memory
    if(protect == 0)
    {
        adress_2 = 0;
        for(adress_0 = 0; adress_0 < 10; adress_0++)
        {
            data = FRAM_write; //add a breakpoint at this line
            for(adress_1 = 0; adress_1 < BITFILE_SIZE; adress_1 = adress_1 + 256)
            {
                memory_page_program(adress_2, data, 256);
                adress_2 = adress_2 + 256;
                data = data + 256;
            }
        }
    }
#endif


#if WRITE_SEG_AND_CRC
    for(address = 0; address < 32824; address = address + 256)
    {
        memory_page_program(address, data, 256);
        data = data + 256;
    }

    for(address = 1572864; address < 1572864+746; address = address + 256)
    {
        memory_page_program(address, crc, 256);
        crc = crc + 256;
    }
#endif

#if load_memory
    uint8_t data2[1024];
    memory_read(0, data2, 1000);
    memory_read(1000, data2, 1000);
    memory_read(1572864, data2, 1000);
#endif

    protect = 1;
    while(1)
    {
        __no_operation();
        __delay_cycles(1 * 1000000);
        P8OUT ^= BIT1;
        i++;
#if !load_memory
        __delay_cycles(1 * 15000000);
//        P6IN;
//        PCIN_H;
        status = P6IN & BIT5;
        status2 = P3IN & (BIT4 | BIT5);
        //telecommand
        if(a >= sizeof(cmd))
        {
            a = 1;
            UCA0TXBUF = cmd[0];
        }
        //lachup
//        if(i > 20)
//        {
//            P9DIR |= BIT2;
//            P9OUT |= BIT2;  //lachup
//        }
#endif
    }

    return 0;
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      b = UCA0RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG:
        if(a < sizeof(cmd))
        {
            UCA0TXBUF = cmd[a++];
        }
        break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
  }
}
