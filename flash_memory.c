/*
 * flash_memory.c
 *
 *  Created on: 30 de abr de 2018
 *      Author: elder
 */

#include "flash_memory.h"

void memory_setup()
{
    BIT_SET(MEMORY_CE_OUT, MEMORY_CE_PIN);
    BIT_SET(MEMORY_CE_DIR, MEMORY_CE_PIN);
/*
    BIT_SET(MEMORY_WP_DIR, MEMORY_WP_PIN);
    BIT_SET(MEMORY_WP_OUT, MEMORY_WP_PIN);

    BIT_SET(MEMORY_HOLD_DIR, MEMORY_HOLD_PIN);
    BIT_SET(MEMORY_HOLD_OUT, MEMORY_HOLD_PIN);*/
}

void memory_enable()
{
    BIT_CLEAR(MEMORY_CE_OUT, MEMORY_CE_PIN);
    __delay_cycles(10);
}
void memory_disable()
{
    BIT_SET(MEMORY_CE_OUT, MEMORY_CE_PIN);
    __delay_cycles(10);
}

void memory_write_enable()
{
    memory_enable();
    spi_write_byte(MEMORY_COMMAND_WREN);
    memory_disable();
}

void memory_write_disable()
{
    memory_enable();
    spi_write_byte(MEMORY_COMMAND_WRDI);
    memory_disable();
}

uint8_t memory_status()
{
    volatile uint8_t status;

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_RDSR);
    spi_read_byte();
    status = spi_read_byte();

    memory_disable();

    return status;
}

void memory_id(uint8_t *id)
{
    memory_enable();

    spi_write_byte(MEMORY_COMMAND_RDID);
    spi_read_byte();
    id[0] = spi_read_byte();
    id[1] = spi_read_byte();
    id[2] = spi_read_byte();

    memory_disable();
}

void memory_page_program(uint32_t address, uint8_t *data, uint16_t length)
{
    uint16_t i;

    if((memory_status() & MEMORY_STATUS_WEL) == 0)
    {
        memory_write_enable();
    }

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_PP);
    spi_write_byte(address>>16 & 0xFF);
    spi_write_byte(address>>8  & 0xFF);
    spi_write_byte(address     & 0xFF);

//    for(i = 0; i < length; i++)
//    {
//        spi_write_byte(data[i]);
//    }
    for(i = 0; i < length; i = i+4)
    {
        spi_write_byte(data[i+3]);
        spi_write_byte(data[i+2]);
        spi_write_byte(data[i+1]);
        spi_write_byte(data[i]);
    }

    memory_disable();

    while(memory_status() & MEMORY_STATUS_WIP);
}

void memory_read(uint32_t address, uint8_t *data, uint32_t length)
{
    uint32_t i;

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_READ);
    spi_write_byte(address>>16 & 0xFF);
    spi_write_byte(address>>8  & 0xFF);
    spi_write_byte(address     & 0xFF);

    spi_read_byte();
    for(i = 0; i < length; i++)
    {
        data[i] = spi_read_byte();
    }

    memory_disable();
}

void memory_sector_erase(uint32_t address)
{
//    if((memory_status() & MEMORY_STATUS_WEL) == 0)
//    {
        memory_write_enable();
//    }

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_SER);
    spi_write_byte(address>>16 & 0xFF);
    spi_write_byte(address>>8  & 0xFF);
    spi_write_byte(address     & 0xFF);

    memory_disable();

    while(memory_status() & MEMORY_STATUS_WIP);
}

void memory_block_32k_erase(uint32_t address)
{
//    if((memory_status() & MEMORY_STATUS_WEL) == 0)
//    {
        memory_write_enable();
//    }

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_BER32);
    spi_write_byte(address>>16 & 0xFF);
    spi_write_byte(address>>8  & 0xFF);
    spi_write_byte(address     & 0xFF);

    memory_disable();

    while(memory_status() & MEMORY_STATUS_WIP);
}

void memory_chip_erase()
{
//    if((memory_status() & MEMORY_STATUS_WEL) == 0)
//    {
        memory_write_enable();
//    }

    memory_enable();

    spi_write_byte(MEMORY_COMMAND_CER);

    memory_disable();

    while(memory_status() & MEMORY_STATUS_WIP);
}
