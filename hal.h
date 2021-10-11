/*
 * hal.h
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */

#ifndef HAL_H_
#define HAL_H_

#include <msp430.h>

//#define MEMORY_CE_DIR       P5DIR
//#define MEMORY_CE_OUT       P5OUT
//#define MEMORY_CE_PIN       BIT7
#define MEMORY_CE_DIR       P10DIR
#define MEMORY_CE_OUT       P10OUT
#define MEMORY_CE_PIN       BIT0

/*
#define MEMORY_CE_DIR       P1DIR
#define MEMORY_CE_OUT       P1OUT
#define MEMORY_CE_PIN       BIT4

#define MEMORY_HOLD_DIR     P2DIR
#define MEMORY_HOLD_OUT     P2OUT
#define MEMORY_HOLD_PIN     BIT6

#define MEMORY_WP_DIR       P2DIR
#define MEMORY_WP_OUT       P2OUT
#define MEMORY_WP_PIN       BIT7*/


#endif /* HAL_H_ */
