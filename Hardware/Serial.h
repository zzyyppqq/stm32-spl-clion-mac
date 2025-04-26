//
// Created by zhangyipeng on 2025/4/17.
//

#ifndef STM32_SPL_CLION_MAC_SERIAL_H
#define STM32_SPL_CLION_MAC_SERIAL_H

#include <stdio.h>


extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

void Serial_SendPacket(void);


#endif //STM32_SPL_CLION_MAC_SERIAL_H
