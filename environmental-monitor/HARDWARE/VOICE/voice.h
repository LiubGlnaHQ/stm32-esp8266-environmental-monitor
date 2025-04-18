#ifndef __VOICE_H
#define __VOICE_H

#include "gpio.h"
#include "stm32f1xx_hal.h"

// 声音传感器初始化函数
void VoiceSensor_Init(void);

// 获取声音传感器数字信号（DO口）
uint8_t VoiceSensor_Get(void);

// 声音检测函数：通过声音传感器的数字信号判断是否有声音，并显示到 OLED 屏幕
void VoiceSensor_DetectSound(void);

#endif
