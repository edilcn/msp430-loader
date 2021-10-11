/*
 * spi.c
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */
#include "spi.h"

void spi_setup()
{
//    BIT_SET(P5SEL0, (BIT4 | BIT5 | BIT6 | BIT7));
//    BIT_CLEAR(P5SEL1, (BIT4 | BIT5 | BIT6 | BIT7));
    BIT_SET(P5SEL0, (BIT4 | BIT5 | BIT6 ));
    BIT_CLEAR(P5SEL1, (BIT4 | BIT5 | BIT6 ));
    /*BIT_CLEAR(P1SEL0, BIT5 );
    BIT_SET(P1SEL1, BIT5 );
    BIT_SET(P4SEL0, (BIT2 | BIT3));
    BIT_CLEAR(P4SEL1, (BIT2 | BIT3));*/


    UCA1CTLW0 = UCSWRST;                      // **Put state machine in reset**
    UCA1CTLW0 |= UCMST | UCSYNC | UCCKPH | UCMSB; // 3-pin, 8-bit SPI master
                                              // Clock polarity high, MSB
    UCA1CTLW0 |= UCSSEL__SMCLK;               // SM 1MHz
    UCA1BR0 = 0x02;                           // /2
    UCA1BR1 = 0;                              //
    UCA1MCTLW = 0;                            // No modulation
    UCA1CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
}

void spi_write_byte(uint8_t byte)
{
    while(!(UCA1IFG & UCTXIFG)); //wait_for_buffer_empty
    UCA1TXBUF = byte;
    while(!(UCA1IFG & UCRXIFG)); //wait_for_data_sent
}

uint8_t spi_read_byte()
{
    while(!(UCA1IFG & UCTXIFG)); //wait_for_buffer_empty
    UCA1TXBUF = 0;
    while(!(UCA1IFG & UCRXIFG)); //wait_for_data_sent
    return UCA1RXBUF;
}


