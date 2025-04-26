//
// Created by zhangyipeng on 2025/4/16.
//
#include "stm32f10x.h"

uint16_t CountSensor_Count;

void CountSensor_Init(void) {
    // 外围时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //GPIO模式，赋值为上拉模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // LED亮

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    EXTI_InitTypeDef extiInitTypeDef;
    extiInitTypeDef.EXTI_Line = EXTI_Line14;
    extiInitTypeDef.EXTI_LineCmd = ENABLE;
    extiInitTypeDef.EXTI_Mode = EXTI_Mode_Interrupt;
    extiInitTypeDef.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&extiInitTypeDef);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitType;
    NVIC_InitType.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitType.NVIC_IRQChannelPreemptionPriority = ENABLE;
    NVIC_InitType.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitType.NVIC_IRQChannelCmd = 1;
    NVIC_Init(&NVIC_InitType);
}


uint16_t getCountSensor_Count(void) {
    return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line14) == SET) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
            CountSensor_Count++;
        }
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}