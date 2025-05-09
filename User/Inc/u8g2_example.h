//
// Created by zhangyipeng on 2025/4/26.
//
#include "u8x8.h"
#include "u8g2.h"


#define SCL_Pin GPIO_Pin_8
#define SDA_Pin GPIO_Pin_9
#define IIC_GPIO_Port GPIOB

void IIC_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SCL_Pin | SDA_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_GPIO_Port, &GPIO_InitStructure);
}


uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch (msg) {
        case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
            __NOP();
            break;
        case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            for (uint16_t n = 0; n < 320; n++) {
                __NOP();
            }
            break;
        case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
            Delay_ms(1);
            break;
        case U8X8_MSG_DELAY_I2C: // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            Delay_us(5);
            break;                    // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
        case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
            if (arg_int == 1) {
                GPIO_SetBits(IIC_GPIO_Port, SCL_Pin);
            } else if (arg_int == 0) {
                GPIO_ResetBits(IIC_GPIO_Port, SCL_Pin);
            }
            break;                    // arg_int=1: Input dir with pullup high for I2C clock pin
        case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
            if (arg_int == 1) {
                GPIO_SetBits(IIC_GPIO_Port, SDA_Pin);
            } else if (arg_int == 0) {
                GPIO_ResetBits(IIC_GPIO_Port, SDA_Pin);
            }
            break;                    // arg_int=1: Input dir with pullup high for I2C data pin
        case U8X8_MSG_GPIO_MENU_SELECT:
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_NEXT:
            u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_PREV:
            u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_HOME:
            u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
            break;
        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}


void u8g2Init(u8g2_t *u8g2) {
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_gpio_and_delay);  // 初始化 u8g2 结构体
    u8g2_InitDisplay(u8g2); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
    u8g2_SetPowerSave(u8g2, 0); // 打开显示器
    u8g2_ClearBuffer(u8g2);
}

void draw(u8g2_t *u8g2) {
    u8g2_SetFontMode(u8g2, 1); /*字体模式选择*/
    u8g2_SetFontDirection(u8g2, 0); /*字体方向选择*/
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf); /*字库选择*/
    u8g2_DrawStr(u8g2, 0, 20, "U");

    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(u8g2, 21, 8, "8");

    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 51, 30, "g");
    u8g2_DrawStr(u8g2, 67, 30, "\xb2");

    u8g2_DrawHLine(u8g2, 2, 35, 47);
    u8g2_DrawHLine(u8g2, 3, 36, 47);
    u8g2_DrawVLine(u8g2, 45, 32, 12);
    u8g2_DrawVLine(u8g2, 46, 33, 12);

    u8g2_SetFont(u8g2, u8g2_font_4x6_tr);
    u8g2_DrawStr(u8g2, 1, 54, "github.com/olikraus/u8g2");
}


/**
 * GPIOA：通常用于复用功能（如USART、SPI）或通用输入输出。
 * GPIOC：常用于简单外设控制（如LED、按键），尤其在STM32F103C8T6开发板上，PC13常连接板载LED
 * 特殊引脚限制:
 * GPIOA的PA13/PA14/PA15默认用于SWD调试接口，需重映射才能作为普通GPIO。
 * GPIOC无此类限制，但PC13在低功耗模式下需注意配置
 */
int u8g2_test(void) {
    IIC_Init();
    u8g2_t u8g2;
    u8g2Init(&u8g2);

    while (1) {
        u8g2_FirstPage(&u8g2);
        do {
            draw(&u8g2);
        } while (u8g2_NextPage(&u8g2));
    }

}
