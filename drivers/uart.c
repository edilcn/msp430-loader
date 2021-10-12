/*
 * uart.c
 *
 *  Created on: 17 de set de 2021
 *      Author: Miguel Boing
 *      Modifications: Edilberto Costa Neto
 */

#include <drivers/uart.h>
#include <hal/driverlib.h>
#include <stdio.h>

uint8_t const data_length = 4;
uint8_t RXdata[data_length]; // RX buffer
uint8_t *buffer_pointer;

// UART Data Transmition
void uartSendData(uint8_t *dados)
{
    uint8_t counter = 0;
    uint8_t temp1;
//    while (counter != data_length){
//        temp1 = *dados++;
        temp1 = *dados;
        counter++;
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, temp1);
//    }
}

// UART Data Reception
void uartReceiveData(uint8_t data)
{
    data = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
}


// UART Setup
void uartInitialize(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P2,
    GPIO_PIN0 + GPIO_PIN1,
    GPIO_PRIMARY_MODULE_FUNCTION
    );

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    // Configure UART to Baud Rate = 9600, No parity bit, one stop bit
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 6;
    param.firstModReg = 8;
    param.secondModReg = 0x20;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = 1;
    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
            return;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    __enable_interrupt();
}
