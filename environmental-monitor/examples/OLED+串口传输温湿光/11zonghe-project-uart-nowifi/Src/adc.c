/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc3;

/* ADC3 init function */
void MX_ADC3_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config 
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* ADC3 clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();
  
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**ADC3 GPIO Configuration    
    PF8     ------> ADC3_IN6 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* ADC3 interrupt Init */
    HAL_NVIC_SetPriority(ADC3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC3_IRQn);
  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();
  
    /**ADC3 GPIO Configuration    
    PF8     ------> ADC3_IN6 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_8);

    /* ADC3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC3_IRQn);
  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
} 

/*********************************************/
uint16_t Get_Adc3(uint8_t ch)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    
    // ����ͨ��
    sConfig.Channel = ch;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;  // ����ԭʼ�����������ʱ��
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
        Error_Handler(); // �������ʧ�ܣ����������
    }

    // ����ADCת��
    if (HAL_ADC_Start(&hadc3) != HAL_OK)
    {
        Error_Handler(); // �������ʧ�ܣ����������
    }

    // �ȴ�ת�����
    if (HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler(); // ����ȴ�ʧ�ܣ����������
    }

    // ��ȡת��ֵ
    uint16_t adc_value = HAL_ADC_GetValue(&hadc3);

    // ֹͣADC
    HAL_ADC_Stop(&hadc3);

    return adc_value;
}
/*********************************************/


/*********************************************/
uint8_t Lsenes_Get_Val(void)
{
    uint32_t temp_val = 0;
    uint8_t t;

    for (t = 0; t < 10; t++)
    {
        temp_val += Get_Adc3(ADC_CHANNEL_6); // ��ȡADCֵ
        HAL_Delay(5); // ��ʱ5ms
    }

    temp_val /= 10; // ��ƽ��ֵ

    if (temp_val > 4000)
        temp_val = 4000; // �������ֵ

    return (uint8_t)(100 - (temp_val / 40)); // ���ش�����ֵ
}

/*********************************************/






/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
