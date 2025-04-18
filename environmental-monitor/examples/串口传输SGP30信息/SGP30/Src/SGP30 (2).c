#include "sgp30.h"
#include <stdio.h>
#include <string.h>

// **内部函数**: 发送 I2C 数据
static uint8_t SGP30_Write(SGP30_t *sgp, uint8_t *cmd, uint8_t len) {
    return HAL_I2C_Master_Transmit(sgp->i2c, SGP30_I2C_ADDRESS, cmd, len, 100);
}

// **内部函数**: 读取 I2C 数据
static uint8_t SGP30_Read(SGP30_t *sgp, uint8_t *cmd, uint8_t cmd_len, uint8_t *data, uint8_t data_len) {
    if (HAL_I2C_Master_Transmit(sgp->i2c, SGP30_I2C_ADDRESS, cmd, cmd_len, 100) != HAL_OK)
        return 1;
    HAL_Delay(10);  // SGP30 需要短暂延时
    return HAL_I2C_Master_Receive(sgp->i2c, SGP30_I2C_ADDRESS, data, data_len, 100);
}

// **初始化 SGP30**
void SGP30_Init(SGP30_t *sgp, I2C_HandleTypeDef *hi2c) {
    sgp->i2c = hi2c;
    sgp->CO2 = 0;
    sgp->TVOC = 0;

    uint8_t cmd[] = SGP30_CMD_INIT_AIR_QUALITY;
    SGP30_Write(sgp, cmd, 2);
    HAL_Delay(100);
}

// **读取 CO2 和 TVOC 数据**
uint8_t SGP30_ReadData(SGP30_t *sgp) {
    uint8_t cmd[] = SGP30_CMD_MEASURE_AIR_QUALITY;
    uint8_t data[6];

    if (SGP30_Read(sgp, cmd, 2, data, 6) == 0) {
        sgp->CO2 = (data[0] << 8) | data[1];
        sgp->TVOC = (data[3] << 8) | data[4];
        return 0;
    }
    return 1;
}

// **通过串口发送数据**
void SGP30_SendData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart) {
    char buffer[64];
    sprintf(buffer, "CO2: %d ppm, TVOC: %d ppb\r\n", sgp->CO2, sgp->TVOC);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), 100);
}
