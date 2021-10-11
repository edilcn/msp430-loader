/*
 * flash_memory.h
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */

#ifndef FLASH_MEMORY_H_
#define FLASH_MEMORY_H_

#include "hal.h"
#include "misc.h"
#include "spi.h"

/* Instructions */

/*          Command             Value     Description               Addr Data   */
#define MEMORY_COMMAND_WRSR     0x01     /* Write Status Register     0   1     */
#define MEMORY_COMMAND_PP       0x02     /* Page Program              3   1-256 */
#define MEMORY_COMMAND_READ     0x03     /* Read Data Bytes           3   >=1   */
#define MEMORY_COMMAND_WRDI     0x04     /* Write Disable             0   0     */
#define MEMORY_COMMAND_RDSR     0x05     /* Read Status Register      0   >=1   */
#define MEMORY_COMMAND_WREN     0x06     /* Write Enable              0   0     */
#define MEMORY_COMMAND_SER      0x20     /* Sector Erase              3   0     */
#define MEMORY_COMMAND_BER32    0x52     /* 32K Block Erase           3   0     */
#define MEMORY_COMMAND_RDID     0x9f     /* Read Identification       0   1-3   */
#define MEMORY_COMMAND_BER64    0xD8     /* 64K Block Erase           3   0     */
#define MEMORY_COMMAND_CER      0xC7     /* Chip Erase                0   0     */

#define MEMORY_STATUS_WIP       BIT0     /* Bit 0: Write in progress bit */
#define MEMORY_STATUS_WEL       BIT1     /* Bit 1: Write enable latch bit */

void memory_setup();
void memory_enable();
void memory_disable();
void memory_write_enable();
void memory_write_disable();
uint8_t memory_status();
void memory_id(uint8_t *id);
void memory_page_program(uint32_t address, uint8_t *data, uint16_t length);
void memory_read(uint32_t address, uint8_t *data, uint32_t length);
void memory_sector_erase(uint32_t address);
void memory_block_32k_erase(uint32_t address);
void memory_chip_erase();

#endif /* FLASH_MEMORY_H_ */
