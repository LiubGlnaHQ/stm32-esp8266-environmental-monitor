#ifndef __SGP30_H
#define __SGP30_H

#include "stm32f1xx_hal.h"

// SGP30 I2C 地址
#define SGP30_I2C_ADDRESS  (0x58 << 1)  // 7-bit 地址 0x58，左移 1 位变成 8-bit

// SGP30 命令
#define SGP30_CMD_INIT_AIR_QUALITY  {0x20, 0x03}
#define SGP30_CMD_MEASURE_AIR_QUALITY  {0x20, 0x08}
#define SGP30_CMD_GET_BASELINE  {0x20, 0x15}
#define SGP30_CMD_SET_BASELINE  {0x20, 0x1E}
#define SGP30_CMD_SET_HUMIDITY  {0x20, 0x61}
#define SGP30_CMD_GET_FEATURE_SET  {0x20, 0x2F}
#define SGP30_CMD_MEASURE_TEST  {0x20, 0x32}
#define SGP30_CMD_GET_SERIAL_ID  {0x36, 0x82}

// 结构体定义
typedef struct {
    I2C_HandleTypeDef *i2c;  // I2C 句柄
    uint16_t CO2;
    uint16_t TVOC;
} SGP30_t;

// SGP30 API
void SGP30_Init(SGP30_t *sgp, I2C_HandleTypeDef *hi2c);
uint8_t SGP30_ReadData(SGP30_t *sgp);
void SGP30_SendData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart);

#endif
