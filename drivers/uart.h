/*
 * uart.h
 *
 *  Created on: 17 de set de 2021
 *      Author: edilc
 */

#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#include <hal/driverlib.h>

void uartSendData(uint8_t *dados);
void uartReceiveData(uint8_t data);
void uartInitialize(void);

#endif /* DRIVERS_UART_H_ */
