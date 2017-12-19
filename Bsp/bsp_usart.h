/**
  ******************************************************************************
  * @�ļ���     �� bsp_usart.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� USART�ײ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_USART_H
#define _BSP_USART_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>


/* �������� ------------------------------------------------------------------*/
void USART_Initializes(void);
void USART1_SendByte(uint8_t Data);
void USART1_SendNByte(uint8_t *pData, uint16_t Length);


#endif /* _BSP_USART_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
