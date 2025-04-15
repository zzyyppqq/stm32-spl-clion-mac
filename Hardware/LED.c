//
// Created by zhangyipeng on 2025/4/15.
//

#include "LED.h"
#include "stm32f10x.h"

void LED_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //开启GPIOC的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1 | GPIO_Pin_2;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // LED亮

    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); // LED灭
}

void LED1_ON(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED1_OFF(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED1_Turn(void) {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
        LED1_OFF();
    } else {
        LED1_ON();
    }
}

void LED2_ON(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2_OFF(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED2_Turn(void) {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0) {
        LED2_OFF();
    } else {
        LED2_ON();
    }
}