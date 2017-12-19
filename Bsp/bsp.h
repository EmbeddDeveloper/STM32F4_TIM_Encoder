/**
  ******************************************************************************
  * @�ļ���     �� bsp.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� BSP�ײ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f4xx.h"


/* �궨�� --------------------------------------------------------------------*/
#define LED_PIN                   GPIO_Pin_1
#define LED_GPIO_PORT             GPIOA
#define LED_GPIO_CLK              RCC_AHB1Periph_GPIOA

/* LED���� */
#define LED_ON()                  GPIO_SetBits(LED_GPIO_PORT, LED_PIN)
#define LED_OFF()                 GPIO_ResetBits(LED_GPIO_PORT, LED_PIN)
#define LED_TOGGLE()              GPIO_ToggleBits(LED_GPIO_PORT, LED_PIN)


/* �������� ------------------------------------------------------------------*/
void BSP_Initializes(void);


#endif /* _BSP_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
