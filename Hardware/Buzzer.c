//
// Created by zhangyipeng on 2025/4/15.
//

#include "LED.h"
#include "stm32f10x.h"

void Buzzer_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //开启GPIOC的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_12;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // LED亮

    GPIO_SetBits(GPIOB, GPIO_Pin_12); // LED灭
}

void Buzzer_ON(void) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_OFF(void) {
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Turn(void) {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0) {
        Buzzer_ON();
    } else {
        Buzzer_OFF();
    }
}