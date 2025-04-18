#include "bled.h"

// 初始化 PC13 为推挽输出（HAL 方式）
void BLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能 GPIOC 时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // 配置 PC13 为推挽输出
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 初始状态，关闭 LED（PC13 置高）
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

// LED 亮（PC13 置低）
void BLED1_ON(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

// LED 灭（PC13 置高）
void BLED1_OFF(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

// LED 翻转
void BLED1_Turn(void)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
