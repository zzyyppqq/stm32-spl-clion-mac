//
// Created by zhangyipeng on 2025/4/15.
//

#ifndef __LIGHTSENSOR_H
#define __LIGHTSENSOR_H

#include "stm32f10x.h"

void LightSensor_Init(void);

uint8_t LightSensor_Get(void);

#endif
