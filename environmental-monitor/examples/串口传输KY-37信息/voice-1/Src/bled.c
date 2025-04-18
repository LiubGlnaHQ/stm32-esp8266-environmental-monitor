#include "bled.h"

// ��ʼ�� PC13 Ϊ���������HAL ��ʽ��
void BLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ʹ�� GPIOC ʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // ���� PC13 Ϊ�������
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // �������
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // ����ģʽ
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // ��ʼ״̬���ر� LED��PC13 �øߣ�
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

// LED ����PC13 �õͣ�
void BLED1_ON(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

// LED ��PC13 �øߣ�
void BLED1_OFF(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

// LED ��ת
void BLED1_Turn(void)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
