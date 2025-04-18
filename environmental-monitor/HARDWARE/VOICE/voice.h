#ifndef __VOICE_H
#define __VOICE_H

#include "gpio.h"
#include "stm32f1xx_hal.h"

// ������������ʼ������
void VoiceSensor_Init(void);

// ��ȡ���������������źţ�DO�ڣ�
uint8_t VoiceSensor_Get(void);

// ������⺯����ͨ�������������������ź��ж��Ƿ�������������ʾ�� OLED ��Ļ
void VoiceSensor_DetectSound(void);

#endif
