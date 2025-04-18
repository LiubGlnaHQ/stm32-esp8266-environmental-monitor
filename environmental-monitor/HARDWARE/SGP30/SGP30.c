#include "sgp30.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>

// 内部函数: 发送 I2C 数据
static HAL_StatusTypeDef SGP30_Write(SGP30_t *sgp, const uint8_t *cmd, uint8_t len) {
    return HAL_I2C_Master_Transmit(sgp->i2c, SGP30_I2C_ADDRESS, (uint8_t *)cmd, len, 100);
}

// 内部函数: 读取 I2C 数据
static HAL_StatusTypeDef SGP30_Read(SGP30_t *sgp, const uint8_t *cmd, uint8_t cmd_len, uint8_t *data, uint8_t data_len) {
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(sgp->i2c, SGP30_I2C_ADDRESS, (uint8_t *)cmd, cmd_len, 100);
    if (ret != HAL_OK) return ret;

    HAL_Delay(12);  // 等待数据准备
    return HAL_I2C_Master_Receive(sgp->i2c, SGP30_I2C_ADDRESS, data, data_len, 100);
}

// 初始化 SGP30
void SGP30_Init(SGP30_t *sgp, I2C_HandleTypeDef *hi2c) {
    sgp->i2c = hi2c;
    sgp->CO2 = 0;
    sgp->TVOC = 0;

    const uint8_t *cmd = SGP30_CMD_INIT_AIR_QUALITY;

    if (SGP30_Write(sgp, cmd, 2) == HAL_OK) {
        HAL_Delay(10);
    }
}

// 读取 CO2 和 TVOC
uint8_t SGP30_ReadData(SGP30_t *sgp) {
    const uint8_t *cmd = SGP30_CMD_MEASURE_AIR_QUALITY;
    uint8_t data[6] = {0};

    if (SGP30_Read(sgp, cmd, 2, data, 6) == HAL_OK) {
        sgp->CO2 = (data[0] << 8) | data[1];
        sgp->TVOC = (data[3] << 8) | data[4];
        return 0;
    }

    return 1;
}

// 通过串口输出结果
void SGP30_SendData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "CO2: %d ppm, TVOC: %d ppb\r\n", sgp->CO2, sgp->TVOC);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), 100);
}

// 通过串口输出结果并在OLED上显示
void SGP30_OLED_ShowData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart) {
    char buffer[64];
    
    // 串口输出
    snprintf(buffer, sizeof(buffer), "CO2: %d ppm, TVOC: %d ppb\r\n", sgp->CO2, sgp->TVOC);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), 100);
    
    // OLED 显示 CO2 和 TVOC
    char CO2String[32];
    char TVOCString[32];
    
    snprintf(CO2String, sizeof(CO2String), "CO2: %d ppm", sgp->CO2);
    snprintf(TVOCString, sizeof(TVOCString), "TVOC: %d ppb", sgp->TVOC);
    
    
    // 显示 CO2 和 TVOC 数据
    OLED_ShowString(0, 4, CO2String, 6);   // 显示 CO2 数据
    OLED_ShowString(0, 6, TVOCString, 6);  // 显示 TVOC 数据
}
