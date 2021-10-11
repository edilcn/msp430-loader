/*
 * misc.h
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */

#ifndef MISC_H_
#define MISC_H_

#include "stdint.h"

#define BIT_TOGGLE(REG, BIT)            (REG ^= BIT)        /**< macro that toggles a bit in a register */
#define BIT_SET(REG, BIT)               (REG |= BIT)        /**< macro that set a bit in a register */
#define BIT_CLEAR(REG, BIT)             (REG &= ~BIT)       /**< macro that clear a bit in a register */
#define BIT_READ(REG, BIT)              ((REG & BIT) != 0)  /**< macro that read a bit in a register */
/**< macro that put the BIT_VALUE in the BIT position of the REG address */
#define BIT_PUT(REG, BIT, BIT_VALUE)    ((BIT_VALUE & 1) == 1) ? BIT_SET(REG, BIT) : BIT_CLEAR(REG, BIT)

#endif /* MISC_H_ */
