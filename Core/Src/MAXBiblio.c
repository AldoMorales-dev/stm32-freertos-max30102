/*
 * MAXBiblio.c
 *
 *  Created on: 17 oct 2026
 *      Author: ALD
 */
#include "stm32l4xx_hal.h"
#include <stdint.h>
extern I2C_HandleTypeDef hi2c1;
uint8_t dummy3;

HAL_StatusTypeDef Escribir ( uint16_t MemAddress, uint8_t valor)
{
	return HAL_I2C_Mem_Write(&hi2c1, 0x57<<1, MemAddress, I2C_MEMADD_SIZE_8BIT, &valor, 1, 3000);//no lleva repeated start, poque no necesita
}


HAL_StatusTypeDef Leer (uint16_t MemAddress, uint8_t *valor)//debe ser un punero, porque si es una variable normal quien llame a Leer no vera los cambios
{
	return HAL_I2C_Mem_Read(&hi2c1, 0X57<<1, MemAddress, I2C_MEMADD_SIZE_8BIT, valor, 1, 3000);//ya lleva incluido repeated start
}

void Inicializar()
{
	Escribir((uint16_t)0x09, (uint8_t)0x40);//Reset: 0x40 = bit RESET de MODE_CONFIG (0x09) */
	Leer((uint16_t)0x01, &dummy3);//banderas de interrupción 1 (lectura limpia)
	Leer((uint16_t)0x00, &dummy3);

	Escribir((uint16_t)0x08, (uint8_t)0x1f);// FIFO Configuration 0x08 0b000 0 f = 0x0f
	//0b000 no average //0b   0 FIFO is not updated until FIFO_DATA is read or the WRITE/READ pointer positions are changed. // 0b     f EMPTY DATA SAMPLES IN FIFO WHEN INTERRUPT IS ISSUED=15
	Escribir((uint16_t)0x09, (uint8_t)0x03);//Mode Configuration 0b00xxx011 puede ser 0x43 = 0b01000011 Reset activo y modo spo2
	Escribir((uint16_t)0x0A, (uint8_t)0b00000111);//SpO2 Configuration 0b00000111 = 0x07

	Escribir((uint16_t)0x0C, (uint8_t)0x3F);//12.6mA RED
	Escribir((uint16_t)0x0D, (uint8_t)0x3F);//12.6mA IR

	Escribir((uint16_t)0x11, (uint8_t)0x00);//MultiLed no se usa entonces 0
	Escribir((uint16_t)0x12, (uint8_t)0x00);

	Escribir((uint16_t)0x04, (uint8_t)0x00);//FIFO_WR_PTR en 0 por ercomendacion de estado conocido
	Escribir((uint16_t)0x05, (uint8_t)0x00);//OVF_COUNTER
	Escribir((uint16_t)0x06, (uint8_t)0x00);//FIFO_RD_PTR


}

HAL_StatusTypeDef Leer_FIFO (uint16_t MemAddress, uint8_t *valor)//debe ser un punero, porque si es una variable normal quien llame a Leer no vera los cambios
{
	return HAL_I2C_Mem_Read(&hi2c1, 0X57<<1, MemAddress, I2C_MEMADD_SIZE_8BIT, valor, 6, 3000);//ya lleva incluido repeated start
}
