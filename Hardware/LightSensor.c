//
// Created by zhangyipeng on 2025/4/15.
//

#include "stm32f10x.h"
#include "LightSensor.h"

void LightSensor_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //开启GPIOC的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_13;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // LED亮

}

uint8_t LightSensor_Get(void) {
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}