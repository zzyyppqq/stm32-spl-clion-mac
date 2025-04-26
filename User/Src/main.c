#include "example.h"
#include "u8g2_example.h"

/**
 * GPIOA：通常用于复用功能（如USART、SPI）或通用输入输出。
 * GPIOC：常用于简单外设控制（如LED、按键），尤其在STM32F103C8T6开发板上，PC13常连接板载LED
 * 特殊引脚限制:
 * GPIOA的PA13/PA14/PA15默认用于SWD调试接口，需重映射才能作为普通GPIO。
 * GPIOC无此类限制，但PC13在低功耗模式下需注意配置
 */
int main(void) {
//    ledON_REG();
//    ledON_SPL();
//    ledON_SPL_OA();// 无效

//    led_ON_OFF_Flash();

//    led_extend_on_pin_all();

//    buzzer_sound();

//    testKey();

//    buzzer_LightSensor();

//    testSensor();
//    testSerial();

    u8g2_test();

}
