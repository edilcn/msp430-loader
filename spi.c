/*
 * spi.c
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */
#include "spi.h"
//#define target 1

void spi_setup()
{
#ifdef target
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
#else
    BIT_SET(P1SEL0, (BIT4 | BIT6 | BIT7 ));
    BIT_CLEAR(P1SEL1, (BIT4 | BIT6 | BIT7 ));
    /*BIT_CLEAR(P1SEL0, BIT5 );
    BIT_SET(P1SEL1, BIT5 );
    BIT_SET(P4SEL0, (BIT2 | BIT3));
    BIT_CLEAR(P4SEL1, (BIT2 | BIT3));*/


    UCB0CTLW0 = UCSWRST;                      // **Put state machine in reset**
    UCB0CTLW0 |= UCMST | UCSYNC | UCCKPH | UCMSB; // 3-pin, 8-bit SPI master
                                              // Clock polarity high, MSB
    UCB0CTLW0 |= UCSSEL__SMCLK;               // SM 1MHz
    UCB0BR0 = 0x02;                           // /2
    UCB0BR1 = 0;                              //
    UCB0CTLW1 = 0;                            // No modulation
    UCB0CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
#endif
}

void spi_write_byte(uint8_t byte)
{
#ifdef target
    while(!(UCA1IFG & UCTXIFG)); //wait_for_buffer_empty
    UCA1TXBUF = byte;
    while(!(UCA1IFG & UCRXIFG)); //wait_for_data_sent
#else
    while(!(UCB0IFG & UCTXIFG)); //wait_for_buffer_empty
    UCB0TXBUF = byte;
    while(!(UCB0IFG & UCRXIFG)); //wait_for_data_sent
#endif
}

uint8_t spi_read_byte()
{
#ifdef target
    while(!(UCA1IFG & UCTXIFG)); //wait_for_buffer_empty
    UCA1TXBUF = 0;
    while(!(UCA1IFG & UCRXIFG)); //wait_for_data_sent
    return UCA1RXBUF;
#else
    while(!(UCB0IFG & UCTXIFG)); //wait_for_buffer_empty
    UCB0TXBUF = 0;
    while(!(UCB0IFG & UCRXIFG)); //wait_for_data_sent
    return UCB0RXBUF;
#endif
}


