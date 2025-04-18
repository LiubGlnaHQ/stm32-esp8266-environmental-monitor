#include "voice.h"
#include "adc.h"  // 包含 CubeMX 生成的 ADC 头文件

extern ADC_HandleTypeDef hadc1;  // 声明 ADC 句柄

// 初始化声音传感器（数字信号）
void VoiceSensor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// 读取 PA11 的数字信号（高低电平）
uint8_t VoiceSensor_Get(void)
{
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
}

// 读取声音传感器的模拟值（ADC）
uint32_t VoiceSensor_ReadADC(void)
{
    uint32_t adcValue = 0;
    
    HAL_ADC_Start(&hadc1);  // 开始 ADC 转换
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    {
        adcValue = HAL_ADC_GetValue(&hadc1);  // 获取 ADC 值
    }
    HAL_ADC_Stop(&hadc1);  // 停止 ADC 转换

    return adcValue;
}

uint32_t Read_ADC_Average(ADC_HandleTypeDef* hadc, uint8_t sampleCount) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < sampleCount; i++) {
        HAL_ADC_Start(hadc);
        HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
        sum += HAL_ADC_GetValue(hadc);
        HAL_ADC_Stop(hadc);
        HAL_Delay(5); // 适当增加采样间隔
    }
    return sum / sampleCount;  // 计算平均值
}

