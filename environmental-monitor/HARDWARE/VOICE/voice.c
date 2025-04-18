#include "voice.h"
#include "gpio.h"
#include "usart.h"  // 包含 USART 头文件，用于串口通信
#include "oled.h"
#include <stdio.h>


uint8_t VoiceSensor_Get(void)
{
    // 读取 PA11 引脚的电平状态（高或低电平）
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);  // 返回 PA11 引脚的电平值
}


/* 声音检测：如果读取到的信号大于阈值，表示检测到声音 */
void VoiceSensor_DetectSound(void)
{
    uint8_t soundDetected = VoiceSensor_Get();  // 获取数字信号

    if (soundDetected)  // 如果 DO 口为高电平（表示声音检测到）
    {
        // 通过串口1输出“Sound detected!”到终端
        char message[] = "Sound detected!\r\n";
        HAL_UART_Transmit(&huart1, (uint8_t *)message, sizeof(message) - 1, 100);

        // 显示到 OLED 屏幕上
			OLED_ShowString(56, 2, " V:yes", 6);  // 在 OLED 显示"Sound detected!"
    }
    else  // 如果 DO 口为低电平（表示没有声音）
    {
        // 通过串口1输出“No sound detected.”到终端
        char message[] = "No sound detected.\r\n";
        HAL_UART_Transmit(&huart1, (uint8_t *)message, sizeof(message) - 1, 100);

        // 显示到 OLED 屏幕上
			OLED_ShowString(56, 2, " V:noo", 6);  // 在 OLED 显示"No sound detected."
    }
}
