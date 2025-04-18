#ifndef __VOICE_H
#define __VOICE_H

#include "stm32f1xx_hal.h"

void VoiceSensor_Init(void);
uint8_t VoiceSensor_Get(void);
uint32_t VoiceSensor_ReadADC(void);  // 新增 ADC 读取函数
uint32_t Read_ADC_Average(ADC_HandleTypeDef* hadc, uint8_t sampleCount);
#endif
