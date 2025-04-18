#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define CAL_PPM 20  // 校准环境中的ppm
#define RL			10		// RL阻值
static float R0; // 元器件在纯净空气中的阻值

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
u16 Get_Light(u8 times);
u16 Get_air(u8 times);

#endif 
