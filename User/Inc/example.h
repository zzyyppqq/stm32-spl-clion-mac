//
// Created by zhangyipeng on 2025/4/16.
//

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Encoder.h"
#include "Serial.h"

void ledON_REG() {
    //   修改寄存器亮灯
    RCC->APB2ENR = 0x00000010;
    GPIOC->CRH = 0x00300000;
    GPIOC->ODR = 0x00000000;

    while (1) {}
}

// // 两个代码片段控制的是不同GPIO端口（GPIOC vs GPIOA）和不同引脚（Pin 0 vs Pin 13）
// GPIOC Pin13：开发板通常默认将LED连接至GPIOC Pin13（如STM32F103C8T6的板载LED）
void ledON_SPL() {
    // GPIOC -> Pin13
    // GPIOA -> Pin0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    //开启GPIOA的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);                    //将赋值后的构体变量传递给GPIO_Init函数
//    GPIO_SetBits(GPIOC, GPIO_Pin_13); // 高电平（灯灭）
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);// 低电平（灯亮）
    //函数内部会自动根据结构体的参数配置相应寄存器
    while (1) {}
}

// 不亮
void ledON_SPL_OA() {
    // GPIOA -> Pin0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //开启GPIOA的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    //将赋值后的构体变量传递给GPIO_Init函数
//    GPIO_SetBits(GPIOC, GPIO_Pin_0); // 高电平（灯灭）
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);// 低电平（灯亮）
    //函数内部会自动根据结构体的参数配置相应寄存器
    while (1) {}
}

// 灯亮灭闪烁
void led_ON_OFF_Flash() {

    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    //开启GPIOC的时钟
    //使用各个外设前必须开启时钟，否则对外设的操作无效

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz

    GPIO_Init(GPIOC, &GPIO_InitStructure);                    //将赋值后的构体变量传递给GPIO_Init函数
    //函数内部会自动根据结构体的参数配置相应寄存器
    //实现GPIOA的初始化

    /*主循环，循环体内的代码会一直循环执行*/
    while (1) {
        /*设置PA0引脚的高低电平，实现LED闪烁，下面展示3种方法*/

        /*方法1：GPIO_ResetBits设置低电平，GPIO_SetBits设置高电平*/
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);                    //将PA0引脚设置为低电平
        Delay_ms(500);                                        //延时500ms
        GPIO_SetBits(GPIOC, GPIO_Pin_13);                    //将PA0引脚设置为高电平
        Delay_ms(500);                                        //延时500ms

        /*方法2：GPIO_WriteBit设置低/高电平，由Bit_RESET/Bit_SET指定*/
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);        //将PA0引脚设置为低电平
        Delay_ms(500);                                        //延时500ms
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);            //将PA0引脚设置为高电平
        Delay_ms(500);                                        //延时500ms

        /*方法3：GPIO_WriteBit设置低/高电平，由数据0/1指定，数据需要强转为BitAction类型*/
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction) 0);        //将PA0引脚设置为低电平
        Delay_ms(500);                                        //延时500ms
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction) 1);        //将PA0引脚设置为高电平
        Delay_ms(500);                                        //延时500ms
    }
}


void led_extend_on_pin_all() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //开启GPIOC的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    while (1) {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        Delay_ms(500);
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        Delay_ms(500);

//        GPIO_Write(GPIOA, ~0x0001);	//0000 0000 0000 0001
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0002);	//0000 0000 0000 0010
//        Delay_ms(100);                                        //延时500ms
    }
}

/**
 * 蜂鸣器响
 */
void buzzer_sound() {

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //开启GPIOC的时钟
    GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                //GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //GPIO速度，赋值为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    while (1) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(100);
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(100);
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(100);
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(700);
    }
}

uint8_t KeyNum;
void testKey() {

    LED_Init();
    Key_Init();
    while (1) {
        KeyNum = Key_GetNum();
        if (KeyNum == 1) {
            LED1_Turn();
        }
        if (KeyNum == 2) {
            LED2_Turn();
        }
    }
}

void buzzer_LightSensor() {
    Buzzer_Init();
    LED_Init();
    LightSensor_Init();
    while (1){
        if (LightSensor_Get() == 1) {
            Buzzer_ON();
            LED1_ON();
        } else {
            Buzzer_OFF();
            LED1_OFF();
        }
    }
}

void testOLED() {
    OLED_Init();

    OLED_ShowChar(1, 1, 'B');
    OLED_ShowString(1, 3, "ZYP");
    OLED_ShowString(1, 7, "HelloWorld");
    OLED_ShowNum(2, 1, 12345, 5);
    OLED_ShowSignedNum(2, 7, -66, 2);
    OLED_ShowHexNum(3, 1, 0xAA55, 4);
    OLED_ShowBinNum(4, 1, 0xAA55, 16);

//    OLED_Clear();
}

int16_t count;
void testSensor() {
    OLED_Init();
    CountSensor_Init();

    Encoder_Init();
    OLED_ShowString(1, 1, "Count:");

    while (1) {
        count += Encoder_Get();
        OLED_ShowNum(1, 7, count, 5);
//        OLED_ShowNum(1, 7, getCountSensor_Count(), 5);
    }

}


uint8_t RxData;

void testSerial() {
    OLED_Init();
    Serial_Init();
    OLED_ShowString(1, 1, "RxData:");

    Serial_Init();

    while (1)
    {
        Delay_ms(1000);
        uint8_t result = Serial_GetRxFlag() == 1;
//        Serial_SendString("Serial_GetRxFlag: ");
//        Serial_SendByte(result);
        if (result)
        {
            RxData = Serial_GetRxData();
            Serial_SendString("RxData:");
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1, 8, RxData, 2);
//            OLED_ShowString(1, 8, RxData);
        }
    }

}


#endif
