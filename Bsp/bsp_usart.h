/**
  ******************************************************************************
  * @文件名     ： bsp_usart.h
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2017年12月19日
  * @摘要       ： USART底层头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _BSP_USART_H
#define _BSP_USART_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>


/* 函数申明 ------------------------------------------------------------------*/
void USART_Initializes(void);
void USART1_SendByte(uint8_t Data);
void USART1_SendNByte(uint8_t *pData, uint16_t Length);


#endif /* _BSP_USART_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
